#include <stdio.h>
#include <time.h>
#include "../common/common.h"

#define COLOR_BACKGROUND	FB_COLOR(0xff,0xff,0xff)
#define COLOR_BUTTON	FB_COLOR(0x00,0x00,0x00)
// #define COLOR_BACKGROUND	FB_COLOR(0x00,0x00,0x0)

#define btnx 100
#define btny 100
#define btnr 80
#define btnw 80
#define btnh 80


static int overlap(x, y)
{
	if(x>btnx-btnw && x < btnx+btnw && y>btny-btnw&&y<btnh+btny)
		return 1;
	return 0;
}

static int berore[10][3] = {
{9, 0, 0},
{9, 0, 0},
{9, 0, 0},
{9, 0, 0},
{9, 0, 0},
{9, 0, 0},
{9, 0, 0},
{9, 0, 0},
{9, 0, 0},
{9, 0, 0}
}; // 手指id,上一个的动作,x,y

static void cls()
{
	fb_draw_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,COLOR_BACKGROUND); // 最亮，全白
	// fb_draw_rect(btnx, btny, btnw, btnh, COLOR_BUTTON);
	draw_circle(btnx, btnw, btnr, COLOR_BUTTON);
	memset(berore, 0, sizeof(int) * 30);
	
}

static uint id = 0;
static uint colorlist[] = {FB_COLOR(0xff, 0, 0), 
						 FB_COLOR(0, 0xff, 0),
						 FB_COLOR(0xff, 0xff, 0),
						 FB_COLOR(0, 0xff, 0xff),
						 FB_COLOR(0, 0, 0xff),
						 FB_COLOR(0xfe, 0xff, 0),
						 FB_COLOR(0x60, 0xf, 0xfc)};

static clock_t clk=0;

static int touch_fd;
static void touch_event_cb(int fd)
{
	int type,x,y,finger;

	type = touch_read(fd, &x,&y,&finger);
	switch(type){
	case TOUCH_PRESS:
	 	if(overlap(x, y))
			cls();
		berore[finger][0] == TOUCH_PRESS;
		printf("TOUCH_PRESS：x=%d,y=%d,finger=%d\n",x,y,finger);
		break;
	case TOUCH_MOVE:
		draw_circle(x, y, 20, colorlist[finger]);
		clock_t _clk = clock();
		if ((double)(_clk - clk) / CLOCKS_PER_SEC > 0.2)
		{
			printf("%f\n", (double)(_clk - clk) / CLOCKS_PER_SEC);
			memset(berore, 0, sizeof(int) * 30);
			clk = _clk;
		}
		if (berore[finger][0] == TOUCH_MOVE)
		{
			fb_draw_line_circle(berore[finger][1], berore[finger][2], x, y, 20, colorlist[finger]);
		}
		berore[finger][0] = TOUCH_MOVE;
		berore[finger][1] = x;
		berore[finger][1] = x; berore[finger][2] = y;

		// printf("TOUCH_MOVE：x=%d,y=%d,finger=%d\n",x,y,finger);
		break;
	case TOUCH_RELEASE:
		berore[finger][0] == TOUCH_RELEASE;
		memset(berore, 0, sizeof(int) * 30);
		printf("TOUCH_RELEASE：x=%d,y=%d,finger=%d\n",x,y,finger);
		break;
	case TOUCH_ERROR:
		berore[finger][0] == TOUCH_ERROR;
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



int main(int argc, char *argv[])
{
	coloropt=colorlist[0];
	memset(before,0,sizeof(before));
	fb_init("/dev/fb0");
	fb_draw_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,COLOR_BACKGROUND);
	fb_update();

	//打开多点触摸设备文件, 返回文件fd
	touch_fd = touch_init("/dev/input/event2");
	//添加任务, 当touch_fd文件可读时, 会自动调用touch_event_cb函数
	task_add_file(touch_fd, touch_event_cb);
	
	task_loop(); //进入任务循环
	return 0;
}
