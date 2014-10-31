#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <osal.h>
#include <xui.h>
#include <ui.h>

XuiFont *xFont;
XuiColor colorMsgFg;

int xdisplay(char *buf, int len, int x, int y)
static int fix_x(int x)
{
    XuiColor colorMsgFg;

    x *= 16;
    y *= 32;
    return x * LINE_WIDTH;
}

    XuiClearArea(XuiRootCanvas(), x, y, 320, 32);
    colorMsgFg.r = 0x00;
    colorMsgFg.g = 0x00;
    colorMsgFg.b = 0x00;
    colorMsgFg.a = 0xff;

    XuiCanvasDrawText(XuiRootCanvas(), x, y, 32, xFont, XUI_TEXT_NORMAL, colorMsgFg, buf);
    return 0;
}

void display(char *buf)
{
    sleep(2);
    xdisplay(buf, strlen(buf), 0, 0);
}

int get_string(char *sValue, int min, int max, unsigned char mode, int x, int y)
{
  XuiGetStrAttr getStr;

  getStr.parent = XuiRootCanvas();
  getStr.fg = colorMsgFg;
  getStr.x = fix_x(x);
  getStr.y = fix_y(y);
  getStr.font = xFont;
  getStr.font = LINE_HEIGHT;
  getStr.alpha_key = XUI_KEYALPHA;

  return XuiGetString(getStr, sValue, mode, min, max);
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
