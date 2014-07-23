#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <posapi.h>
#include <posapi_all.h>

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

const APPINFO AppInfo={
	"CloudWalk",
	"AppFramwork",
	"0.4.2",
	"pcteam",
	"Framework",
	"",
	0,
	0,
	0,
	""
};

int event_main(ST_EVENT_MSG *msg)
{
  printf("\n %s", msg);
	SystemInit();
	return 0;
}

void *pax_allocf(mrb_state *mrb, void *p, size_t size, void *ud);

int robot_rock_execute(void)
{
  mrb_state *mrb;

  //char code[] = "Device::Walk.execute('main.mrb')";
  //char code[] = "Device::Walk.load";
  //char code[] = "require './da_funk.mrb'; Device::Walk.start";
  char code[] = "PAX.start";

  //DEBUG
  //printf("\nParse Ruby code with mruby\n");

  //DEBUG
  //printf("\nmrb_open");
  //DelayMs(2000);
  mrb = mrb_open_allocf(pax_allocf, NULL);

  //DEBUG
  //printf("\nmrb_load_string\n");
  //DelayMs(2000);
  mrb_load_string(mrb, code);

  //DEBUG
  //printf("\nbacktrace");
  //DelayMs(2000);
  //mrb_output_backtrace(mrb, mrb->exc, my_func, (void *)stderr);

  //DEBUG
  //printf("\nmrb_close");
  //DelayMs(2000);
  mrb_close(mrb);

  return 0;
}

int main(void)
{
  SystemInit();

  while (42) {
    robot_rock_execute();
  }
  return 0;
}

