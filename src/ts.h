/*------------------------------------------------------------
* FileName: touchscreen.h
* Author: LuX
* Date: 2013-04-27
------------------------------------------------------------*/
#ifndef TS_H
#define TS_H

/**
 * open touch screen
 * return 0 if successful, else return -1
 */
int OpenTouchScreen();

/**
 * close touch screen
 * return 0 if successful
 */
int CloseTouchScreen();

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
int GetPixel(int* x, int* y);

#endif
