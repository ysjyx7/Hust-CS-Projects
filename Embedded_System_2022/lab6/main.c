#include <stdio.h>
#include <time.h>
#include "../common/common.h"

#define COLOR_BACKGROUND	FB_COLOR(0xff,0xff,0xff)
#define COLOR_BUTTON	FB_COLOR(0x00,0x00,0x00)

#define TIME_X	(SCREEN_WIDTH-160)
#define TIME_Y	0
#define TIME_W	100
#define TIME_H	30
#define COLOR_TEXT			FB_COLOR(0x0,0x0,0x0)
#define BLACK FB_COLOR(0,0,0)

#define BUTTON_BEGIN 10
#define BUTTON_H 60
#define BUTTON_W 60
#define THIN 5
#define NORMAL 10
#define THICK 15
#define COLOR_CENTER SCREEN_WIDTH-50
#define COLOR_RADIUS 30

static int before[10][3];

static uint id = 0;
static uint colorlist[] = {FB_COLOR(0xff, 0, 0), 
						 FB_COLOR(0, 0xff, 0),
						 FB_COLOR(0xff, 0xff, 0),
						 FB_COLOR(0, 0xff, 0xff),
						 FB_COLOR(0, 0, 0xff),
						 FB_COLOR(0xfe, 0xff, 0),
						 FB_COLOR(0x60, 0xf, 0xfc)};


int msg[7];


static int touch_fd;
static int bluetooth_fd;
static int coloropt;
static int thickopt = NORMAL;
static int touch_fd;
static int mod;
static int isButton(int x,int y)
{
	if((x<=100&&y<=240)||(x>=180&&x<=470&&y<=60)||(x>=COLOR_CENTER-COLOR_RADIUS-20))
		return 1;
	return 0;
}
static void touch_event_cb(int fd)
{
	int type,x,y,finger;

	type = touch_read(fd, &x,&y,&finger);
	switch(type){
	case TOUCH_PRESS:
		msg[0]=TOUCH_PRESS;
		msg[1]=finger;
		msg[2]=x;
		msg[3]=y;
		msg[4]=mod;
		msg[5]=coloropt;
		msg[6]=thickopt;
		myRead_nonblock(bluetooth_fd,msg,sizeof(msg));
		if(x<=BUTTON_W+BUTTON_BEGIN && y<=BUTTON_H+10)
		{
			fb_draw_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,FB_COLOR(255,255,255));
			//fb_draw_rect(0,0,BUTTON_W,BUTTON_H,FB_COLOR(0,0,0));//清除键
			//fb_draw_text(10,10,"CLEAR",25,FB_COLOR(255,255,255));
 			fb_image *img;
 			img = fb_read_png_image("./Refresh.png");
 			fb_draw_image(BUTTON_BEGIN,10,img,0);
 			fb_update();
 			fb_free_image(img);

			//fb_draw_rect(0,BUTTON_H,BUTTON_W,BUTTON_H,FB_COLOR(30,30,30));//橡皮擦
			//fb_draw_text(10,10,"ERASE",25,FB_COLOR(255,255,255));
 			img = fb_read_png_image("./eraser.png");
 			fb_draw_image(BUTTON_BEGIN,80,img,0);
 			fb_update();
 			fb_free_image(img);

 			img = fb_read_png_image("./pen.png");
 			fb_draw_image(BUTTON_BEGIN,150,img,0);
 			fb_update();
 			fb_free_image(img);


			//fb_draw_rect(0,2*BUTTON_H,BUTTON_W,BUTTON_H,FB_COLOR(155,155,155));//正常写字
			//fb_draw_text(10,10,"NORMAL",25,FB_COLOR(255,255,255));

			//fb_draw_rect(100,0,BUTTON_W,BUTTON_H,FB_COLOR(0xff,0,0));//细
			fb_draw_line_circle(200,30,250,30,THIN,BLACK);
			fb_draw_line_circle(280,30,330,30,NORMAL,BLACK);
			fb_draw_line_circle(380,30,430,30,THICK,BLACK);
			//fb_draw_rect(150,0,BUTTON_W,BUTTON_H,FB_COLOR(0,0xff,0));//中等
			//fb_draw_rect(200,0,BUTTON_W,BUTTON_H,FB_COLOR(0,0,0xff));//粗

			//fb_draw_rect(SCREEN_WIDTH-BUTTON_W,0,BUTTON_W,BUTTON_H,colorlist[0]);
			draw_circle(COLOR_CENTER,30,COLOR_RADIUS,colorlist[0]);
			draw_circle(COLOR_CENTER,110,COLOR_RADIUS,colorlist[1]);
			draw_circle(COLOR_CENTER,190,COLOR_RADIUS,colorlist[2]);
			draw_circle(COLOR_CENTER,270,COLOR_RADIUS,colorlist[3]);
			draw_circle(COLOR_CENTER,350,COLOR_RADIUS,colorlist[4]);
			draw_circle(COLOR_CENTER,430,COLOR_RADIUS,colorlist[5]);
			draw_circle(COLOR_CENTER,510,COLOR_RADIUS,colorlist[6]);
			//fb_draw_rect(SCREEN_WIDTH-BUTTON_W,BUTTON_H,BUTTON_W,BUTTON_H,colorlist[1]);
			// fb_draw_rect(SCREEN_WIDTH-BUTTON_W,2*BUTTON_H,BUTTON_W,BUTTON_H,colorlist[2]);
			// fb_draw_rect(SCREEN_WIDTH-BUTTON_W,3*BUTTON_H,BUTTON_W,BUTTON_H,colorlist[3]);
			// fb_draw_rect(SCREEN_WIDTH-BUTTON_W,4*BUTTON_H,BUTTON_W,BUTTON_H,colorlist[4]);
			// fb_draw_rect(SCREEN_WIDTH-BUTTON_W,5*BUTTON_H,BUTTON_W,BUTTON_H,colorlist[5]);
			// fb_draw_rect(SCREEN_WIDTH-BUTTON_W,6*BUTTON_H,BUTTON_W,BUTTON_H,colorlist[6]);
			fb_update();
			break;
		}
		if(x<=BUTTON_W+BUTTON_BEGIN&&y>BUTTON_H+10&&y<=2*BUTTON_H+20){
			mod=1;
			fb_update();
			break;
		}
		if(x<=BUTTON_W+BUTTON_BEGIN&&y>2*BUTTON_H+20&&y<=3*BUTTON_H+30){
			mod=0;                               
			fb_update();
			break;
		}
		if(x>=200&&x<=250&&y<30){
			thickopt=THIN;
			break;
		}else if(x>=280&&x<=330&&y<30){
			thickopt=NORMAL;
			break;
		}else if(x>=380&&x<=430&&y<30){
			thickopt=THICK;
			break;
		}
		if(x>=COLOR_CENTER-COLOR_RADIUS&&x<=COLOR_CENTER+COLOR_RADIUS&&y>=30-COLOR_RADIUS&&y<=30+COLOR_RADIUS)
		{
			coloropt=colorlist[0];
			break;
		}
		else if(x>=COLOR_CENTER-COLOR_RADIUS&&x<=COLOR_CENTER+COLOR_RADIUS&&y>=110-COLOR_RADIUS&&y<=110+COLOR_RADIUS)
		{
			coloropt=colorlist[1];
			break;
		}
		else if(x>=COLOR_CENTER-COLOR_RADIUS&&x<=COLOR_CENTER+COLOR_RADIUS&&y>=190-COLOR_RADIUS&&y<=190+COLOR_RADIUS)
		{
			coloropt=colorlist[2];
			break;
		}

	else if(x>=COLOR_CENTER-COLOR_RADIUS&&x<=COLOR_CENTER+COLOR_RADIUS&&y>=270-COLOR_RADIUS&&y<=270+COLOR_RADIUS)
		{
			coloropt=colorlist[3];
			break;
		}
		else if(x>=COLOR_CENTER-COLOR_RADIUS&&x<=COLOR_CENTER+COLOR_RADIUS&&y>=350-COLOR_RADIUS&&y<=350+COLOR_RADIUS)
		{
			coloropt=colorlist[4];
			break;
		}
		else if(x>=COLOR_CENTER-COLOR_RADIUS&&x<=COLOR_CENTER+COLOR_RADIUS&&y>=430-COLOR_RADIUS&&y<=430+COLOR_RADIUS)
		{
			coloropt=colorlist[5];
			break;
		}
		else if(x>=COLOR_CENTER-COLOR_RADIUS&&x<=COLOR_CENTER+COLOR_RADIUS&&y>=510-COLOR_RADIUS&&y<=510+COLOR_RADIUS)
		{
			coloropt=colorlist[6];
			break;
		}
		msg[4]=mod;
		msg[5]=coloropt;
		msg[6]=thickopt;
		myRead_nonblock(bluetooth_fd,msg,sizeof(msg));
		before[finger][0] == TOUCH_PRESS;
		printf("TOUCH_PRESS：x=%d,y=%d,finger=%d\n",x,y,finger);
		break;
	case TOUCH_MOVE:
		int color=coloropt;
		msg[0]=TOUCH_MOVE;
		msg[1]=finger;
		msg[2]=x;
		msg[3]=y;
		msg[4]=mod;
		msg[5]=coloropt;
		msg[6]=thickopt;
		myRead_nonblock(bluetooth_fd,msg,sizeof(msg));
		if(mod){
			color=FB_COLOR(255,255,255);
		}
		if(!isButton(x,y))
		{
			draw_circle(x, y, thickopt, color);
			if (before[finger][0] == TOUCH_MOVE)
			{
				fb_draw_line_circle(before[finger][1], before[finger][2], x, y, thickopt, color);
			}
		}
		before[finger][0] = TOUCH_MOVE;
		before[finger][1] = x;
		before[finger][2] = y;
		break;
	case TOUCH_RELEASE:
		before[finger][0] == TOUCH_RELEASE;
		memset(before, 0, sizeof(int) * 30);
		printf("TOUCH_RELEASE：x=%d,y=%d,finger=%d\n",x,y,finger);
		break;
	case TOUCH_ERROR:
		before[finger][0] == TOUCH_ERROR;
		printf("close touch fd\n");
		close(fd);
		task_delete_file(fd);
		break;
	default:
		return;
	}
	fb_update();
	return;
}

static void bluetooth_tty_event_cb(int fd){
    char buf[128];
	int *p=buf;
	int n=myRead_nonblock(fd,buf,sizeof(buf));
	if(n <= 0) {
		printf("close bluetooth tty fd\n");
		//task_delete_file(fd);
		//close(fd);
		exit(0);
		return;
	}

	int x=p[1],y=p[2],finger=p[3];
	int m=p[4];
	int copt=p[5];
	int topt=p[6];

	switch(p[0]){
		case TOUCH_PRESS:
			if(x<=BUTTON_W+BUTTON_BEGIN && y<=BUTTON_H+10)
		{
			fb_draw_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,FB_COLOR(255,255,255));
			//fb_draw_rect(0,0,BUTTON_W,BUTTON_H,FB_COLOR(0,0,0));//清除键
			//fb_draw_text(10,10,"CLEAR",25,FB_COLOR(255,255,255));
 			fb_image *img;
 			img = fb_read_png_image("./Refresh.png");
 			fb_draw_image(BUTTON_BEGIN,10,img,0);
 			fb_update();
 			fb_free_image(img);

			//fb_draw_rect(0,BUTTON_H,BUTTON_W,BUTTON_H,FB_COLOR(30,30,30));//橡皮擦
			//fb_draw_text(10,10,"ERASE",25,FB_COLOR(255,255,255));
 			img = fb_read_png_image("./eraser.png");
 			fb_draw_image(BUTTON_BEGIN,80,img,0);
 			fb_update();
 			fb_free_image(img);

 			img = fb_read_png_image("./pen.png");
 			fb_draw_image(BUTTON_BEGIN,150,img,0);
 			fb_update();
 			fb_free_image(img);


			//fb_draw_rect(0,2*BUTTON_H,BUTTON_W,BUTTON_H,FB_COLOR(155,155,155));//正常写字
			//fb_draw_text(10,10,"NORMAL",25,FB_COLOR(255,255,255));

			//fb_draw_rect(100,0,BUTTON_W,BUTTON_H,FB_COLOR(0xff,0,0));//细
			fb_draw_line_circle(200,30,250,30,THIN,BLACK);
			fb_draw_line_circle(280,30,330,30,NORMAL,BLACK);
			fb_draw_line_circle(380,30,430,30,THICK,BLACK);
			//fb_draw_rect(150,0,BUTTON_W,BUTTON_H,FB_COLOR(0,0xff,0));//中等
			//fb_draw_rect(200,0,BUTTON_W,BUTTON_H,FB_COLOR(0,0,0xff));//粗

			//fb_draw_rect(SCREEN_WIDTH-BUTTON_W,0,BUTTON_W,BUTTON_H,colorlist[0]);
			draw_circle(COLOR_CENTER,30,COLOR_RADIUS,colorlist[0]);
			draw_circle(COLOR_CENTER,110,COLOR_RADIUS,colorlist[1]);
			draw_circle(COLOR_CENTER,190,COLOR_RADIUS,colorlist[2]);
			draw_circle(COLOR_CENTER,270,COLOR_RADIUS,colorlist[3]);
			draw_circle(COLOR_CENTER,350,COLOR_RADIUS,colorlist[4]);
			draw_circle(COLOR_CENTER,430,COLOR_RADIUS,colorlist[5]);
			draw_circle(COLOR_CENTER,510,COLOR_RADIUS,colorlist[6]);
			//fb_draw_rect(SCREEN_WIDTH-BUTTON_W,BUTTON_H,BUTTON_W,BUTTON_H,colorlist[1]);
			// fb_draw_rect(SCREEN_WIDTH-BUTTON_W,2*BUTTON_H,BUTTON_W,BUTTON_H,colorlist[2]);
			// fb_draw_rect(SCREEN_WIDTH-BUTTON_W,3*BUTTON_H,BUTTON_W,BUTTON_H,colorlist[3]);
			// fb_draw_rect(SCREEN_WIDTH-BUTTON_W,4*BUTTON_H,BUTTON_W,BUTTON_H,colorlist[4]);
			// fb_draw_rect(SCREEN_WIDTH-BUTTON_W,5*BUTTON_H,BUTTON_W,BUTTON_H,colorlist[5]);
			// fb_draw_rect(SCREEN_WIDTH-BUTTON_W,6*BUTTON_H,BUTTON_W,BUTTON_H,colorlist[6]);
			fb_update();
			break;
		}
		if(x<=BUTTON_W+BUTTON_BEGIN&&y>BUTTON_H+10&&y<=2*BUTTON_H+20){
			m=1;
			fb_update();
			break;
		}
		if(x<=BUTTON_W+BUTTON_BEGIN&&y>2*BUTTON_H+20&&y<=3*BUTTON_H+30){
			m=0;                               
			fb_update();
			break;
		}
		if(x>=200&&x<=250&&y<30){
			topt=THIN;
			break;
		}else if(x>=280&&x<=330&&y<30){
			topt=NORMAL;
			break;
		}else if(x>=380&&x<=430&&y<30){
			topt=THICK;
			break;
		}
if(x>=COLOR_CENTER-COLOR_RADIUS&&x<=COLOR_CENTER+COLOR_RADIUS&&y>=30-COLOR_RADIUS&&y<=30+COLOR_RADIUS
		)
		{
			copt=colorlist[0];
			break;
		}
		else if(x>=COLOR_CENTER-COLOR_RADIUS&&x<=COLOR_CENTER+COLOR_RADIUS&&y>=110-COLOR_RADIUS&&y<=110+COLOR_RADIUS)
		{
			copt=colorlist[1];
			break;
		}
		else if(x>=COLOR_CENTER-COLOR_RADIUS&&x<=COLOR_CENTER+COLOR_RADIUS&&y>=190-COLOR_RADIUS&&y<=190+COLOR_RADIUS)
		{
			copt=colorlist[2];
			break;
		}

	else if(x>=COLOR_CENTER-COLOR_RADIUS&&x<=COLOR_CENTER+COLOR_RADIUS&&y>=270-COLOR_RADIUS&&y<=270+COLOR_RADIUS)
		{
			copt=colorlist[3];
			break;
		}
		else if(x>=COLOR_CENTER-COLOR_RADIUS&&x<=COLOR_CENTER+COLOR_RADIUS&&y>=350-COLOR_RADIUS&&y<=350+COLOR_RADIUS)
		{
			copt=colorlist[4];
			break;
		}
		else if(x>=COLOR_CENTER-COLOR_RADIUS&&x<=COLOR_CENTER+COLOR_RADIUS&&y>=430-COLOR_RADIUS&&y<=430+COLOR_RADIUS)
		{
			copt=colorlist[5];
			break;
		}
		else if(x>=COLOR_CENTER-COLOR_RADIUS&&x<=COLOR_CENTER+COLOR_RADIUS&&y>=510-COLOR_RADIUS&&y<=510+COLOR_RADIUS)
		{
			copt=colorlist[6];
			break;
		}
		before[finger][0] == TOUCH_PRESS;
		before[finger][1]=x;
		before[finger][2]=y;
		printf("TOUCH_PRESS：x=%d,y=%d,finger=%d\n",x,y,finger);
			break;
		case TOUCH_MOVE:
			if(m){
			copt=FB_COLOR(255,255,255);
			}
			if(!isButton(x,y))
			{
				draw_circle(x, y, topt, copt);
				if (before[finger][0] == TOUCH_MOVE)
				{
					fb_draw_line_circle(before[finger][1], before[finger][2], x, y, topt, copt);
				}
			}
			before[finger][0] = TOUCH_MOVE;
			before[finger][1] = x;
			before[finger][2] = y;
			fb_update();
			break;
	}
	return;
}
static int bluetooth_tty_init(const char *dev)
{
	int fd = open(dev, O_RDWR|O_NOCTTY|O_NONBLOCK); /*非阻塞模式*/
	if(fd < 0){
		printf("bluetooth_tty_init open %s error(%d): %s\n", dev, errno, strerror(errno));
		return -1;
	}
	return fd;
}

static int st=0;
static void timer_cb(int period) /*该函数0.5秒执行一次*/
{
	char buf[100];
	sprintf(buf, "%d", st++);
	fb_draw_rect(TIME_X, TIME_Y, TIME_W, TIME_H, COLOR_BACKGROUND);
	fb_draw_border(TIME_X, TIME_Y, TIME_W, TIME_H, COLOR_TEXT);
	fb_draw_text(TIME_X+2, TIME_Y+20, buf, 24, COLOR_TEXT);
	fb_update();
	return;
}

int main(int argc, char *argv[])
{
	memset(before,0,sizeof(before));
	fb_init("/dev/fb0");
	font_init("./font.ttc");
	fb_draw_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,COLOR_BACKGROUND);
	fb_update();

	//打开多点触摸设备文件, 返回文件fd
	touch_fd = touch_init("/dev/input/event2");
	//添加任务, 当touch_fd文件可读时, 会自动调用touch_event_cb函数
	task_add_file(touch_fd, touch_event_cb);

	bluetooth_fd = bluetooth_tty_init("/dev/rfcomm0");
	if(bluetooth_fd == -1) return 0;
	task_add_file(bluetooth_fd, bluetooth_tty_event_cb);

	task_add_timer(500, timer_cb); /*增加0.5秒的定时器*/
	
	task_loop(); //进入任务循环
	return 0;
}
