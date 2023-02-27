#include "common.h"
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <linux/kd.h>
#include <linux/vt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>

static int LCD_FB_FD;
static int *LCD_FB_BUF = NULL;
static int DRAW_BUF[SCREEN_WIDTH*SCREEN_HEIGHT];

static struct area {
	int x1, x2, y1, y2;
} update_area = {0,0,0,0};

#define AREA_SET_EMPTY(pa) do {\
	(pa)->x1 = SCREEN_WIDTH;\
	(pa)->x2 = 0;\
	(pa)->y1 = SCREEN_HEIGHT;\
	(pa)->y2 = 0;\
} while(0)

void fb_init(char *dev)
{
	int fd;
	struct fb_fix_screeninfo fb_fix;
	struct fb_var_screeninfo fb_var;

	if(LCD_FB_BUF != NULL) return; /*already done*/

	//进入终端图形模式
	fd = open("/dev/tty0",O_RDWR,0);
	ioctl(fd, KDSETMODE, KD_GRAPHICS);
	close(fd);

	//First: Open the device
	if((fd = open(dev, O_RDWR)) < 0){
		printf("Unable to open framebuffer %s, errno = %d\n", dev, errno);
		return;
	}
	if(ioctl(fd, FBIOGET_FSCREENINFO, &fb_fix) < 0){
		printf("Unable to FBIOGET_FSCREENINFO %s\n", dev);
		return;
	}
	if(ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0){
		printf("Unable to FBIOGET_VSCREENINFO %s\n", dev);
		return;
	}

	printf("framebuffer info: bits_per_pixel=%u,size=(%d,%d),virtual_pos_size=(%d,%d)(%d,%d),line_length=%u,smem_len=%u\n",
		fb_var.bits_per_pixel, fb_var.xres, fb_var.yres, fb_var.xoffset, fb_var.yoffset,
		fb_var.xres_virtual, fb_var.yres_virtual, fb_fix.line_length, fb_fix.smem_len);

	//Second: mmap
	void *addr = mmap(NULL, fb_fix.smem_len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(addr == (void *)-1){
		printf("failed to mmap memory for framebuffer.\n");
		return;
	}

	if((fb_var.xoffset != 0) ||(fb_var.yoffset != 0))
	{
		fb_var.xoffset = 0;
		fb_var.yoffset = 0;
		if(ioctl(fd, FBIOPAN_DISPLAY, &fb_var) < 0) {
			printf("FBIOPAN_DISPLAY framebuffer failed\n");
		}
	}

	LCD_FB_FD = fd;
	LCD_FB_BUF = addr;

	//set empty
	AREA_SET_EMPTY(&update_area);
	return;
}

static void _copy_area(int *dst, int *src, struct area *pa)
{
	int x, y, w, h;
	x = pa->x1; w = pa->x2-x;
	y = pa->y1; h = pa->y2-y;
	src += y*SCREEN_WIDTH + x;
	dst += y*SCREEN_WIDTH + x;
	while(h-- > 0){
		memcpy(dst, src, w*4);
		src += SCREEN_WIDTH;
		dst += SCREEN_WIDTH;
	}
}

static int _check_area(struct area *pa)
{
	if(pa->x2 == 0) return 0; //is empty

	if(pa->x1 < 0) pa->x1 = 0;
	if(pa->x2 > SCREEN_WIDTH) pa->x2 = SCREEN_WIDTH;
	if(pa->y1 < 0) pa->y1 = 0;
	if(pa->y2 > SCREEN_HEIGHT) pa->y2 = SCREEN_HEIGHT;

	if((pa->x2 > pa->x1) && (pa->y2 > pa->y1))
		return 1; //no empty

	//set empty
	AREA_SET_EMPTY(pa);
	return 0;
}

void fb_update(void)
{
	if(_check_area(&update_area) == 0) return; //is empty
	_copy_area(LCD_FB_BUF, DRAW_BUF, &update_area);
	AREA_SET_EMPTY(&update_area); //set empty
	return;
}

/*======================================================================*/

static void * _begin_draw(int x, int y, int w, int h)
{
	int x2 = x+w;
	int y2 = y+h;
	if(update_area.x1 > x) update_area.x1 = x;
	if(update_area.y1 > y) update_area.y1 = y;
	if(update_area.x2 < x2) update_area.x2 = x2;
	if(update_area.y2 < y2) update_area.y2 = y2;
	return DRAW_BUF;
}

void fb_draw_pixel(int x, int y, int color)
{
	if(x<0 || y<0 || x>=SCREEN_WIDTH || y>=SCREEN_HEIGHT) return;
	int *buf = _begin_draw(x,y,1,1);
/*---------------------------------------------------*/
	*(buf + y*SCREEN_WIDTH + x) = color;
/*---------------------------------------------------*/
	return;
}

void fb_draw_rect(int x, int y, int w, int h, int color)
{
	if(x < 0) { w += x; x = 0;}
	if(x+w > SCREEN_WIDTH) { w = SCREEN_WIDTH-x;}
	if(y < 0) { h += y; y = 0;}
	if(y+h >SCREEN_HEIGHT) { h = SCREEN_HEIGHT-y;}
	if(w<=0 || h<=0) return;
	int *buf = _begin_draw(x,y,w,h);
/*---------------------------------------------------*/
	//printf("you need implement fb_draw_rect()\n"); exit(0);
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
		//	*(buf+(i+y)*SCREEN_WIDTH+j+x)=color;
			fb_draw_pixel(x+j,i+y,color);
		}
	}
/*---------------------------------------------------*/
	return;
}

void fb_draw_line(int x1, int y1, int x2, int y2, int color)
{
/*---------------------------------------------------*/
//	printf("you need implement fb_draw_line()\n"); exit(0);
//	int *buf=_begin_draw(x1,y1,1,1);
//	int dx=abs(x1-x0)
	
	int dx, dy, length, i;
	float xincre,yincre,x,y;
	if(x1<0 || x2<0 || y1<0 || y2<0) return;
	dx = x1-x2>0 ? x1-x2 : x2-x1;
	dy = y1-y2>0 ? y1-y2 : y2-y1;
	length = dx>dy ? dx : dy;
	xincre=(float)(x1-x2)/(float)length;
	yincre=(float)(y1-y2)/(float)length;
	x = x2;
	y = y2;
	for(i=1;i<=length;i++){
		fb_draw_pixel((int)x,(int)y,color);
		x+=xincre;
		y+=yincre;
	}
	/*---------------------------------------------------*/
	return;
}

void fb_draw_image(int x, int y, fb_image *image, int color)
{
	if(image == NULL) return;

	int ix = 0; //image x
	int iy = 0; //image y
	int w = image->pixel_w; //draw width
	int h = image->pixel_h; //draw height

	if(x<0) {w+=x; ix-=x; x=0;}
	if(y<0) {h+=y; iy-=y; y=0;}
	
	if(x+w > SCREEN_WIDTH) {
		w = SCREEN_WIDTH - x;
	}
	if(y+h > SCREEN_HEIGHT) {
		h = SCREEN_HEIGHT - y;
	}
	if((w <= 0)||(h <= 0)) return;

	int *buf = _begin_draw(x,y,w,h);
/*---------------------------------------------------------------*/
	char *dst = (char *)(buf + y*SCREEN_WIDTH + x);
	char *src; //不同的图像颜色格式定位不同
/*---------------------------------------------------------------*/

	int alpha;
	int ww;


	if(image->color_type == FB_COLOR_RGB_8880) /*lab3: jpg*/
	{
		// printf("you need implement fb_draw_image() FB_COLOR_RGB_8880\n"); exit(0);
		const uint* img = image->content;
		for(int row = 0;row<h;row++)
		{
			memcpy(_begin_draw(x, row + y, 1, 1) + (row + y) * SCREEN_WIDTH * 4, img + row * w, w * sizeof(int));
		}
		return;
	}
	else if(image->color_type == FB_COLOR_RGBA_8888) /*lab3: png*/
	{
		for(int row = 0;row<h;row++)
		{
			for(int col = 0;col<w;col++)
			{
				const int *img = image->content;
				const char* addr = &img[row * w + col];
				const char* addr0 = (int*)dst + (row)*SCREEN_WIDTH + col;
				char alpha = addr[3];
				char b = (addr[0] * alpha  + addr0[0] * (255 - alpha)) / 255;
				char g = (addr[1] * alpha  + addr0[1] * (255 - alpha)) / 255;
				char r = (addr[2] * alpha  + addr0[2] * (255 - alpha)) / 255;
				int in = 0xff000000;
				char* inptr = &in;
				inptr[0] = b;
				inptr[1] = g;
				inptr[2] = r;
				fb_draw_pixel(col + x, row + y, in);
			}
		}
		return;
	}
	else if(image->color_type == FB_COLOR_ALPHA_8) /*lab3: font*/
	{
		// printf("you need implement fb_draw_image() FB_COLOR_ALPHA_8\n"); exit(0);
		for(int row = 0;row<h;row++)
		{
			for(int col = 0;col<w;col++)
			{
				const char* addr1 = &image->content[row * w + col];
				const char * addr = &color;
				const char* addr0 = (int*)dst + (row)*SCREEN_WIDTH + col;
				char alpha = addr1[0];
				char b = (addr[0] * alpha + addr0[0] * (255 - alpha)) / 255;
				char g = (addr[1] * alpha + addr0[1] * (255 - alpha)) / 255;
				char r = (addr[2] * alpha + addr0[2] * (255 - alpha)) / 255;
				int in = 0xff000000;
				char* inptr = &in;
				inptr[0] = b;
				inptr[1] = g;
				inptr[2] = r;
				fb_draw_pixel(col + x, row + y, in);
			}
		}

		return;
	}
/*---------------------------------------------------------------*/
	return;
}

void fb_draw_border(int x, int y, int w, int h, int color)
{
	if(w<=0 || h<=0) return;
	fb_draw_rect(x, y, w, 1, color);
	if(h > 1) {
		fb_draw_rect(x, y+h-1, w, 1, color);
		fb_draw_rect(x, y+1, 1, h-2, color);
		if(w > 1) fb_draw_rect(x+w-1, y+1, 1, h-2, color);
	}
}

/** draw a text string **/
void fb_draw_text(int x, int y, char *text, int font_size, int color)
{
	fb_image *img;
	fb_font_info info;
	int i=0;
	int len = strlen(text);
	while(i < len)
	{
		img = fb_read_font_image(text+i, font_size, &info);
		if(img == NULL) break;
		fb_draw_image(x+info.left, y-info.top, img, color);
		fb_free_image(img);

		x += info.advance_x;
		i += info.bytes;
	}
	return;
}


void draw_circle_8(int xc, int yc, int x, int y, int color)
{
    fb_draw_pixel(xc + x, yc + y, color);
    fb_draw_pixel(xc - x, yc + y, color);
    fb_draw_pixel(xc + x, yc - y, color);
    fb_draw_pixel(xc - x, yc - y, color);
    fb_draw_pixel(xc + y, yc + x, color);
    fb_draw_pixel(xc - y, yc + x, color);
    fb_draw_pixel(xc + y, yc - x, color);
    fb_draw_pixel(xc - y, yc - x, color);
}
 

void draw_circle(int xc, int yc, int r, unsigned long c)
{
	int x = 0, y = r, yi, d;
	d = 3 - 2 * r;

	while (x <= y)
	{
		for (yi = x; yi <= y; yi++)
			draw_circle_8(xc, yc, x, yi, c);

		if (d < 0)
		{
			d = d + 4 * x + 6;
		}
		else
		{
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}

void fb_draw_line_circle(int x0, int y0, int x1, int y1, int r, int color)
{
/*---------------------------------------------------*/
	// Bresenham
	int *buf = _begin_draw(x1, y1, 1, 1);
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;

    while ( x0 != x1 || y0 != y1) {
		draw_circle(x0, y0, r, color);
		int e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 <  dy) { err += dx; y0 += sy; }
    }
/*---------------------------------------------------*/
	return;
}
