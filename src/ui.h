#ifndef UI_H
#define UI_H

#include <xui.h>

int xdisplay(char *buf, int len, int x, int y);
void display(const char *format, ...);
void display_bitmap(char *path, int y, int x);
void display_clear_line(int line);
void display_clear(void);
XuiFont *OpenFont();
XuiFont *GetFont();
void CloseFont();
int get_string(char *sValue[128], int min, int max, int mode, int y, int x);

#define D200_SCREEN_X 320
#define D200_SCREEN_Y 240

#define S920_SCREEN_X 240
#define S920_SCREEN_Y 320

#define D200_LINE_WIDTH 17
#define D200_LINE_HEIGHT 30

#define S920_LINE_WIDTH 12
#define S920_LINE_HEIGHT 22

#endif  /* PRINT_TEXT_H */
