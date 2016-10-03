/*------------------------------------------------------------
 * FileName: touchscreen.c
 * Author: LuX
 * Date: 2013-04-27
 * See header file tslib.h and library file libts-xxx.so,
 * If you want to fulfill touch screen function in your APP,
 * please add -ts link option when building the project.
 * Touch screen coordinate:
 * (X,0)-------(X,Y)
 * |             |
 * |             |
 * |             |
 * (0,0)-------(0,Y)
 ------------------------------------------------------------*/
#include <linux/stddef.h>
#include <osal.h>
#include <stdio.h>
#include <tslib.h>
#include "constant.h"
#include "ts.h"

/* touch screen device */
struct tsdev *g_ptsdev = NULL;

/**
 * open touch screen
 * return 0 if successful, else return -1
 */
int OpenTouchScreen() {
  g_ptsdev = ts_open(TOUCHSCREEN_NAME, 0);
  if (g_ptsdev == NULL) {
    return -1;
  }
  if (0 != ts_config(g_ptsdev)) {
    return -1;
  }
  return 0;
}

/**
 * close touch screen
 * return 0 if successful
 */
int CloseTouchScreen() {
  return ts_close(g_ptsdev);
}

/**
 * get touch coordinate.
 * [out] x x coordinate
 * [out] y y coordinate
 * return 0 if successful, else return -1
 * Touch screen coordinate:
 * (X,0)-------(X,Y)
 * |             |
 * |             |
 * |             |
 * (0,0)-------(0,Y)
 */
int GetPixel(int* x, int* y) {
  int ret;
  int touchscreen_fd;
  fd_set fdset;
  /* 1 second = 1000000 microseconds */
  struct timeval timeout = {0, 100};
  struct ts_sample sample;
  if (NULL == g_ptsdev) {
    return -1;
  }
  touchscreen_fd = ts_fd(g_ptsdev);
  FD_ZERO(&fdset);
  if (touchscreen_fd < 0)	{
    return -1;
  }
  FD_SET(touchscreen_fd, &fdset);
  /* non-block */
  ret = select(touchscreen_fd + 1, &fdset, NULL, NULL, &timeout);
  switch (ret) {
    /* error happens */
    case -1:
      /* time out */
    case 0:
      ret = -1;
      break;
      /* success */
    default:
      ts_read(g_ptsdev, &sample, 1);
      /* if sample.pressure is 0, then sample.x, sample.y is the last touch up coordinate */
      if (sample.pressure == 0) {
        /* so read the next coordinate, which is the current press down coordinate */
        ts_read(g_ptsdev, &sample, 1);
        if (sample.pressure > 0) {
          *x = sample.x;
          *y = sample.y;
          ret = 0;
          return 0;
        }
      }
      break;
  }
  return ret;
}

int TestTouchScreen() {
  int ret;
  int x, y;
  char flag = 1;
  ret = OpenTouchScreen(TOUCHSCREEN_NAME);
  if (ret < 0) {
    printf("Open touch screen failed!\n");
  }
  while (flag) {
    if (0 == GetPixel(&x, &y)) {
      printf("x=%d, y=%d\n", x, y);
      break;
    }
  }
  CloseTouchScreen();
  return 0;
}
