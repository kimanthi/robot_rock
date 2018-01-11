#ifndef UI_H
#define UI_H

#include <xui.h>

extern int screen_x;
extern int screen_y;
extern int line_width;
extern int line_height;

int xdisplay(char *buf, int len, int x, int y);
void display(const char *format, ...);
void display_bitmap(char *path, int y, int x);
void display_clear_line(int line);
void display_clear(void);
XuiFont *OpenFont(int r, int g, int b, int a, int x, int y, int width, int height, char *path);
XuiFont *GetFont(void);
void CloseFont(void);
int get_string(char *sValue[128], int min, int max, int mode, int y, int x);

#define D200_SCREEN_X 320
#define D200_SCREEN_Y 240

#define S920_SCREEN_X 240
#define S920_SCREEN_Y 320

#define D200_LINE_WIDTH 16
#define D200_LINE_HEIGHT 27

#define S920_LINE_WIDTH 12
#define S920_LINE_HEIGHT 22

#endif  /* PRINT_TEXT_H */
