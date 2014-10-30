#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <osal.h>
#include <xui.h>

XuiFont *xFont;

int xdisplay(char *buf, int len, int x, int y)
{
    XuiColor colorMsgFg;

    x *= 16;
    y *= 32;

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


XuiFont *OpenFont(void)
{
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
