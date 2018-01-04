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

int queue_event_auto_rotate(struct tp_ctx* thiz, struct touch_event *event, int *x, int *y)
{
  int rotate = 0;
  char rotate_val[64] = {0};

  OsRegGetValue("ro.fac.lcd.rotate", rotate_val);
  rotate = atoi(rotate_val);
  switch (rotate) {
    case 90:
      {
        *x = event->y;
        *y = thiz->width - event->x;
        break;
      }
    case 180:
      {
        *x = thiz->width - event->x;
        *y = thiz->height - event->y;
        break;
      }
    case 270:
      {
        *x = thiz->height - event->y;
        *y = event->x;
        break;
      }
    default:break;
  }

  return 0;
}

int read_tp(struct tp_ctx* thiz, struct touch_event *event, int *x, int *y)
{
  int ret;
  struct input_event ievent;

  ret = read(thiz->fd, &ievent, sizeof(ievent));
  if (ret != sizeof(ievent)) {
    /*display ("read from '/dev/tp' failed(ret=%d, errno=%d)\n", ret, errno);*/
    return -1;
  }

  switch (ievent.type) {
    case EV_KEY:
      if (ievent.code == BTN_TOUCH) {
        event->type = ievent.value ? EVT_MOUSE_DOWN : EVT_MOUSE_UP;
      }
      break;
      /* 绝对坐标报点，我们的系统中均采用这种方式报点 */
      /*Absolute coordinate points, which are used in our system*/
    case EV_ABS:
      switch (ievent.code) {
        case ABS_X:
          event->x = ievent.value;
          break;
        case ABS_Y:
          event->y = ievent.value;
          break;
        default: break;
      }
      if (event->type == EVT_NOP) {
        event->type = EVT_MOUSE_MOVE;
      }
      break;
      /* 相对坐标报点，当前我们的系统中未使用这种方式 */
      /*Relative coordinate points are not used in our system*/
    case EV_REL:
      switch (ievent.code) {
        case REL_X:
          event->x = ievent.value;
          break;
        case REL_Y:
          event->y = ievent.value;
          break;
        default: break;
      }
      if (event->type == EVT_NOP) {
        event->type = EVT_MOUSE_MOVE;
      }
      break;
      /* 相对坐标报点，当前我们的系统中未使用这种方式 */
      /*Relative coordinate points are not used in our system*/
    case EV_SYN:
      queue_event_auto_rotate(thiz, event, x, y);
      event->type = EVT_NOP;
      break;
  }

  return 0;
}

/* Adds 'interval_ms' to timeval 'a' and store in 'result'
   - 'interval_ms' is in milliseconds */
static void add_ms_to_timeval(struct timeval *a, unsigned long interval_ms, struct timeval *result) {
  result->tv_sec = a->tv_sec + (interval_ms / 1000);
  result->tv_usec = a->tv_usec + ((interval_ms % 1000) * 1000);
  if (result->tv_usec > 1000000) {
    result->tv_usec -= 1000000;
    result->tv_sec++;
  }
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

int fd_ts = -1;

int GetTouchScreen(long timeout, int *x, int *y, int clear)
{
  int width, height, ret;
  struct timeval tv1, tv2, tv3;
  static struct tp_ctx tp_ctx;
  struct touch_event event;
  fd_set err_fdset;
  fd_set fdset;

  /* 获取屏幕的宽度和高度， 与tp无关，计算屏幕旋转时需要 */
  /*Get the width and height of the screen, it's needed when calculating the screen rotation and nothing to do with tp*/
  ret = get_display_size(&width, &height);
  if (ret < 0) return -1;

  tp_ctx.width  = width;
  tp_ctx.height = height;

  if (clear == 1 && fd_ts > 0) {
    close(fd_ts);
    fd_ts = -1;
  }
  if (fd_ts < 0) fd_ts = open("/dev/tp", O_RDONLY);
  if (fd_ts < 0) return fd_ts;
  tp_ctx.fd = fd_ts;

  gettimeofday(&tv1, NULL);
  add_ms_to_timeval(&tv1, timeout, &tv1);

  tv3.tv_sec = 0;
  if (timeout < 50) {
    tv3.tv_usec = timeout * 1000;
  } else {
    tv3.tv_usec = 50000;
  }

  while (42) {
    FD_ZERO(&fdset);
    FD_ZERO(&err_fdset);
    FD_SET(fd_ts, &fdset);
    FD_SET(fd_ts, &err_fdset);
    ret = select(fd_ts + 1, &fdset, NULL, &err_fdset, &tv3);

    if (ret < 0) {
      return ret;
    } else if (ret == 0) {
      if (timeout != 0) {
        gettimeofday(&tv2, NULL);
        if (compare_timeval(&tv2, &tv1) == 1) {
          ret = 0;
          break;
        }
      }

      continue;
    } else {
      if (FD_ISSET(fd_ts, &fdset)) {
        if (read_tp(&tp_ctx, &event, x, y) == 0) {
          if (*x != 0 && *y != 0) {
            ret = 1;
            break;
          }
        }
      }
      else if (FD_ISSET(fd_ts, &err_fdset)) {
        ret = -1;
      }
    }
  }

  return ret;
}
