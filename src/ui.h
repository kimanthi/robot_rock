#ifndef UI_H
#define UI_H

#include <xui.h>

int xdisplay(char *buf, int len, int x, int y);
void display(const char *format, ...);
void display_bitmap(char *path, int y, int x);
XuiFont *OpenFont();
XuiFont *GetFont();
void CloseFont();
int get_string(char *sValue, int min, int max, int mode, int y, int x);

#define SCREEN_X 320
#define SCREEN_Y 240

#define LINE_WIDTH 16
#define LINE_HEIGHT 32

#endif  /* PRINT_TEXT_H */
