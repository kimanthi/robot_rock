#ifndef UI_H
#define UI_H

#include <xui.h>

void xdisplay(char *buf, int len, int x, int y);
void display(char *buf);
XuiFont *OpenFont();
XuiFont *GetFont();
void CloseFont();

#endif  /* PRINT_TEXT_H */
