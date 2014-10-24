#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* Sample */
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <osal.h>
#include <xui.h>

#include <linux/input.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <linux/stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "debugger.h"
#include "font.h"
#include "header.h"
#include "lcd.h"
#include "keyboard.h"
#include "osal.h"

/* Include the mruby header */
#include "mruby.h"
#include "mruby/value.h"
#include "mruby/compile.h"
#include "mruby/proc.h"

/* backtrace */
#include "mruby/variable.h"
#include "mruby/array.h"
#include "mruby/string.h"
#include "mruby/class.h"
#include "mruby/debug.h"

unsigned long total_allocated_mem = 0;
int counter=0;

void *pax_allocf(mrb_state *mrb, void *p, size_t size, void *ud)
{
    void *new_ptr;

    if (size == 0) {
        if (p) free(p);
        return NULL;
    }
    else {
        if (p)
            new_ptr = realloc(p, size);
        else
            new_ptr = malloc(size);

        if(!new_ptr){
            /*printf("\nMemory Allocation Error: err %d total %lu object %d free %d", new_ptr, total_allocated_mem, size, freesize());*/
            printf("\nMemory Allocation Error: err %d total %lu object %d", (int)new_ptr, total_allocated_mem, size);
            /*kbflush();*/
            /*getkey();*/
        } else {
            counter++;
            total_allocated_mem += size;
        }
    }

    return new_ptr;
}

int robot_rock_execute(void)
{
    mrb_state *mrb;

    //char code[] = "Device::Walk.execute('main.mrb')";
    //char code[] = "Device::Walk.load";
    //char code[] = "require './da_funk.mrb'; Device::Walk.start";
    char code[] = "puts \"EEEEEEEEEEEEEEEEE\"";

    //DEBUG
    HelloWorld("Parse Ruby code with mruby");
    /*printf("\nParse Ruby code with mruby\n");*/

    //DEBUG
    HelloWorld("mrb_open");
    sleep(5);
    /*mrb = mrb_open_allocf(pax_allocf, NULL);*/
    mrb = mrb_open();

    //DEBUG
    HelloWorld("mrb_load_string\n");
    sleep(2);
    mrb_load_string(mrb, code);

    //DEBUG
    //printf("\nbacktrace");
    //DelayMs(2000);
    //mrb_output_backtrace(mrb, mrb->exc, my_func, (void *)stderr);

    //DEBUG
    HelloWorld("mrb_close");
    sleep(2);
    mrb_close(mrb);

    return 0;
}

int Time2Str(ST_TIME* time, char* str)
{
	sprintf(str, "%04d-%02d-%02d %02d:%02d:%02d", time->Year, time->Month, time->Day, time->Hour, time->Minute, time->Second);
	return 0;
}

int Init()
{
	if (OpenFont(FONT_NAME) < 0) {
		return -1;
	}
	if (OpenLcd() < 0) {
		return -1;
	}
	if (OpenKeyboard(KEYBOARD_NAME) < 0) {
		return -1;
	}
	return 0;
}

int Finish()
{
	CloseFont();
	CloseLcd();
	CloseKeyboard();
	return 0;
}

int HelloWorld(char *title)
{
	int w, h;
	int titleHeight = 32;
	int strLen;

	/* get LCD size*/
    GetLcdSize(&w, &h);

	/* set background color */
    DrawLcd(0, 0, w, h, WHITE);

	/* print hello world */
	strLen = GetStringLength(title, titleHeight);
	DrawString(title, titleHeight, (w - strLen), titleHeight, BLACK);
	StartDrawLcd(0, 0, w, h);
	return 0;
}

int main(int argc, char **argv)
{
    /*ScrClrLine(0, 1);*/
    /*ScrPrint(0, 0, 1, "Test");*/

	Init();

    robot_rock_execute();

    return 0;
}

