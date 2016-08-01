#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <osal.h>
#include <xui.h>
#include <ui.h>

XuiFont *xFont;
XuiColor colorMsgFg;

int screen_x    = 0;
int screen_y    = 0;
int line_width  = 0;
int line_height = 0;

static int fix_x(int x)
{
  return x * line_width;
}

static int fix_y(int y)
{
  return y * line_height;
}

int xdisplay(char *buf, int len, int x, int y)
{
  XuiClearArea(XuiRootCanvas(), fix_x(x), fix_y(y), screen_x, line_height);
  XuiCanvasDrawText(XuiRootCanvas(), fix_x(x), fix_y(y), line_height, xFont, XUI_TEXT_NORMAL, colorMsgFg, buf);
  return 0;
}

void display(const char *format, ...)
{
  char dest[128];
  va_list argptr;

  va_start(argptr, format);
  vsprintf(dest, format, argptr);
  va_end(argptr);

  xdisplay(dest, strlen(dest), 0, 0);
  sleep(2);
}

int get_string(char *sValue[128], int min, int max, int mode, int y, int x)
{
  XuiGetStrAttr getStr;

  memset(&getStr, 0, sizeof(getStr));
  memset(sValue, 0, sizeof(128));

  getStr.parent = XuiRootCanvas();
  getStr.fg = colorMsgFg;
  getStr.x = fix_x(x);
  getStr.y = fix_y(y);
  getStr.font = xFont;
  getStr.size = line_height;
  getStr.alpha_key = XUI_KEYF1;

  return XuiGetString(getStr, (char *)sValue, mode, min, max);
}

void display_bitmap(char *path, int y, int x)
{
  XuiImg *img;

  img  = XuiImgLoadFromFile(path);

  XuiCanvasDrawImg(XuiRootCanvas(), fix_x(x), fix_y(y), img->width, img->height, XUI_BG_NORMAL, img);
  XuiImgFree(img);
}

void display_clear_line(int line)
{
  XuiClearArea(XuiRootCanvas(), 0, fix_y(line), screen_x, line_height);
}

void display_clear(void)
{
  XuiClearArea(XuiRootCanvas(), 0, 0, screen_x, screen_y);
}

XuiFont *OpenFont(void)
{
  char model[32]="\0";

  memset(&model, 0, sizeof(model));
	OsRegGetValue("ro.fac.mach", model);

  colorMsgFg.r = 0x00;
  colorMsgFg.g = 0x00;
  colorMsgFg.b = 0x00;
  colorMsgFg.a = 0xff;

  if (strcmp(model, "d200") == 0) {
    screen_x    = D200_SCREEN_X;
    screen_y    = D200_SCREEN_Y;
    line_width  = D200_LINE_WIDTH;
    line_height = D200_LINE_HEIGHT;
  } else {
    screen_x    = S920_SCREEN_X;
    screen_y    = S920_SCREEN_Y;
    line_width  = S920_LINE_WIDTH;
    line_height = S920_LINE_HEIGHT;
  }

  return xFont = XuiCreateFont("./res/inconsolata.ttf", 0, 0);
}

void CloseFont(void)
{
  XuiDestroyFont(xFont);
}

XuiFont *GetFont(void)
{
  return xFont;
}
