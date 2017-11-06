#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "osal.h"
#include "ui.h"

typedef enum _EventType {
	EVT_NOP = 0,
	EVT_MOUSE_UP,
	EVT_MOUSE_MOVE,
	EVT_MOUSE_DOWN,
} EventType;

struct touch_event {
	int x;
	int y;
	EventType type;
};

struct tp_ctx {
	int fd;
	int width;
	int height;
	int pressed;
};

int get_display_size(int* width, int* height)
{
	int fb_fd;
	struct fb_fix_screeninfo fix;
	struct fb_var_screeninfo var;

	fb_fd = open("/dev/fb", O_RDWR);
	if (fb_fd < 0) {
		return -1;
	}

	if (ioctl(fb_fd, FBIOGET_FSCREENINFO, &fix) < 0) {
		close(fb_fd);
		return -1;
	}
	if (ioctl(fb_fd, FBIOGET_VSCREENINFO, &var) < 0) {
		close(fb_fd);
		return -1;
	}

	*width = var.xres;
	*height = var.yres;

	return 0;
}

/* 实际应用中一般需要将触摸点上报到消息队列， demo中仅仅是进行旋转计算并打印出旋转前后的坐标信息 */
/*In practical application, it is necessary to report the touch point to the message queue ,
and demo only rotates, calculates and prints the coordinate information of before and after rotation*/

int queue_event_auto_rotate(struct tp_ctx* thiz, struct touch_event* event)
{
	int rotate = 0;
	char rotate_val[64] = {0};
	int screen_x, screen_y;

	/*display ("touch LCD(%d, %d), type(%d)\n", event->x, event->y, event->type);*/

	OsRegGetValue("ro.fac.lcd.rotate", rotate_val);
	rotate = atoi(rotate_val);
	switch (rotate) {
		case 90:
		{
			screen_x = event->y;
			screen_y = thiz->width - event->x;
			break;
		}
		case 180:
		{
			screen_x = thiz->width - event->x;
			screen_y = thiz->height - event->y;
			break;
		}
		case 270:
		{
			screen_x = thiz->height - event->y;
			screen_y = event->x;
			break;
		}
		default:break;
	}
	/*display ("touch screen(%d, %d), type(%d)\n", screen_x, screen_y, event->type);*/

	return 0;
}

int read_tp(struct tp_ctx* thiz)
{
	int ret;
	/*int x, y;*/
	struct input_event ievent;
  struct touch_event event;

	ret = read(thiz->fd, &ievent, sizeof(ievent));
	if (ret != sizeof(ievent)) {
		/*display ("read from '/dev/tp' failed(ret=%d, errno=%d)\n", ret, errno);*/
		return -1;
	}

	switch (ievent.type) {
		case EV_KEY:
			if (ievent.code == BTN_TOUCH) {
				event.type = ievent.value ? EVT_MOUSE_DOWN : EVT_MOUSE_UP;
			}
			break;
		/* 绝对坐标报点，我们的系统中均采用这种方式报点 */
		/*Absolute coordinate points, which are used in our system*/
		case EV_ABS:
			switch (ievent.code) {
				case ABS_X:
					event.x = ievent.value;
					break;
				case ABS_Y:
					event.y = ievent.value;
					break;
				default: break;
			}
			if (event.type == EVT_NOP) {
				event.type = EVT_MOUSE_MOVE;
			}
			break;
		/* 相对坐标报点，当前我们的系统中未使用这种方式 */
		/*Relative coordinate points are not used in our system*/
		case EV_REL:
			switch (ievent.code) {
				case REL_X:
					event.x = ievent.value;
					break;
				case REL_Y:
					event.y = ievent.value;
					break;
				default: break;
			}
			if (event.type == EVT_NOP) {
				event.type = EVT_MOUSE_MOVE;
			}
			break;
			/* 收到EV_SYN，说明收到了一个完整的报点事件 */
			/*Receive EV_SYN，note that a complete report point event has been received*/
		case EV_SYN:
			queue_event_auto_rotate(thiz, &event);
			event.type = EVT_NOP;
			break;
	}

	return 0;
}

static int compare_timeval(struct timeval *a, struct timeval *b)
{
  if (a->tv_sec > b->tv_sec)
    return 1;
  else if (a->tv_sec < b->tv_sec)
    return -1;
  else if (a->tv_usec > b->tv_usec)
    return 1;
  else if (a->tv_usec < b->tv_usec)
    return -1;
  return 0;
}

int fd = -1; //open("/dev/tp", O_RDONLY);

int test_touch_screen(long timeout, int *x, int *y)
{
	static struct tp_ctx tp_ctx;
	int ret, fd;
	int width, height;
	fd_set fdset;
	fd_set err_fdset;

  struct timeval tv1, tv2;

	/* 获取屏幕的宽度和高度， 与tp无关，计算屏幕旋转时需要 */
	/*Get the width and height of the screen, it's needed when calculating the screen rotation and nothing to do with tp*/
	ret = get_display_size(&width, &height);
	if (ret < 0) {
		return -1;
	}
	tp_ctx.width = width;
	tp_ctx.height = height;

	if (fd < 0) {
    fd = open("/dev/tp", O_RDONLY);
	}
  if (fd < 0) return fd;
	tp_ctx.fd = fd;

  gettimeofday(&tv1, NULL);
  add_ms_to_timeval(&tv1, timeout, &tv1);

	while (1) {
		FD_ZERO(&fdset);
		FD_ZERO(&err_fdset);
		FD_SET(fd, &fdset);
		FD_SET(fd, &err_fdset);
		ret = select(fd + 1, &fdset, NULL, &err_fdset, NULL);

		if (ret < 0) {
      return ret;
		} else if (ret == 0) {
      if (timeout != 0) {
        gettimeofday(&tv2, NULL);
        if (compare_timeval(&tv2, &tv1) == 1) return 0;
      }

			continue;
		} else {
			if (FD_ISSET(fd, &fdset)) {
        if (read_tp(&tp_ctx)) {
        } else {
        }
			}
			else if (FD_ISSET(fd, &err_fdset)) {
				return -1;
			}
		}
	}

	return 1;
}