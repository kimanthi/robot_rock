#ifndef TOUCH_SCREEN_H
#define TOUCH_SCREEN_H

int GetTouchScreen(long timeout, int *x, int *y, int clear);
int ClearTouchScreen(void);

#endif

