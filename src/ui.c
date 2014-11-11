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

static int fix_x(int x)
{
    return x * LINE_WIDTH;
}

static int fix_y(int y)
{
    return y * LINE_HEIGHT;
}

int xdisplay(char *buf, int len, int x, int y)
{
  XuiClearArea(XuiRootCanvas(), fix_x(x), fix_y(y), SCREEN_X, LINE_HEIGHT);
  XuiCanvasDrawText(XuiRootCanvas(), fix_x(x), fix_y(y), LINE_HEIGHT, xFont, XUI_TEXT_NORMAL, colorMsgFg, buf);
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

int get_string(char *sValue, int min, int max, int mode, int y, int x)
{
  XuiGetStrAttr getStr;

  getStr.parent = XuiRootCanvas();
  getStr.fg = colorMsgFg;
  getStr.x = fix_x(x);
  getStr.y = fix_y(y);
  getStr.font = xFont;
  getStr.size = LINE_HEIGHT;
  getStr.alpha_key = XUI_KEYALPHA;

  return XuiGetString(getStr, sValue, mode, min, max);
}

void display_bitmap(char *path, int y, int x)
{
	XuiImg *img;
	int imgX;
	int imgY;

	img  = XuiImgLoadFromFile(path);
	imgX = XUI_RIGHT_X(0, XuiRootCanvas()->width, img->width);
	/*imgY = 80;*/

  /*display("x %d, y %d, w %d, h %d", imgX, imgY, img->width, img->height);*/
  /*img->width = 120;*/
  /*img->height = 120;*/

	XuiCanvasDrawImg(XuiRootCanvas(), fix_x(x), fix_y(y), img->width, img->height, XUI_BG_NORMAL, img);
	XuiImgFree(img);
}

void display_clear_line(int line)
{
  XuiClearArea(XuiRootCanvas(), 0, fix_y(line), LINE_HEIGHT, SCREEN_Y);
}

void display_clear(void)
{
  XuiClearArea(XuiRootCanvas(), 0, 0, SCREEN_X, SCREEN_Y);
}

XuiFont *OpenFont(void)
{
  colorMsgFg.r = 0x00;
  colorMsgFg.g = 0x00;
  colorMsgFg.b = 0x00;
  colorMsgFg.a = 0xff;

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
