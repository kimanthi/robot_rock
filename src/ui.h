#ifndef UI_H
#define UI_H

#include <xui.h>

int xdisplay(char *buf, int len, int x, int y);
void display(char *buf);
XuiFont *OpenFont();
XuiFont *GetFont();
void CloseFont();

#define SCREEN_X 320
#define SCREEN_Y 240

#define LINE_WIDTH 16
#define LINE_HEIGHT 32

#endif  /* PRINT_TEXT_H */
