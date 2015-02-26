#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

/*PAX*/
#include "osal.h"
#include "ui.h"
#include <xui.h>
#include "emvlib_Prolin.h"
#include "keyboard.h"

/* Include the mruby header */
#include "mruby.h"
#include "mruby/value.h"
#include "mruby/compile.h"
#include "mruby/proc.h"

mrb_state *mrb;

mrb_state *mrb_robot(void)
{
  return mrb;
}

int robot_rock_execute(void)
{
  mrbc_context *c;
  char code[] = "Context.start('main', 'PAX')";
  mrb = mrb_open();

  c = mrbc_context_new(mrb);

  mrb_load_string_cxt(mrb, code, c);

  mrbc_context_free(mrb, c);

  mrb_close(mrb);

  return 0;
}

static int GuiInit(void)
{
  int ret;
  int  xui_argc=2;
  char *xui_argv[] = {"ROTATE=0","STATUSBAR=22"};

  ret = XuiOpen(xui_argc, xui_argv);
  if (ret == XUI_RET_OK) {
    return RET_OK;
  }
  else {
    return -1;
  }

}

static void GuiDeinit(void)
{
  XuiClose();
}

static void CrashReportInit(void)
{
  signal(SIGILL,    OsSaveCrashReport);
  signal(SIGABRT,   OsSaveCrashReport);
  signal(SIGBUS,    OsSaveCrashReport);
  signal(SIGFPE,    OsSaveCrashReport);
  signal(SIGSEGV,   OsSaveCrashReport);
  signal(SIGSTKFLT, OsSaveCrashReport);
  signal(SIGPIPE,   OsSaveCrashReport);
}

void StatusbarInit(void)
{
  XuiSetStatusbarIcon(0,"./res/mobile100.png");
  XuiSetStatusbarIcon(1,"./res/modem.png");
  XuiSetStatusbarIcon(2,"./res/ethernet.png");
  XuiSetStatusbarIcon(3,"./res/wifi100.png");
  XuiSetStatusbarIcon(4,"./res/lock.png");
  XuiSetStatusbarIcon(5,"./res/card.png");
  XuiSetStatusbarIcon(6,"./res/print.png");
  XuiSetStatusbarIcon(7,"./res/battery0c.png");
}

int ScreenInit(void)
{
  XuiColor colorTitleBg;

  colorTitleBg.r = 0xff;
  colorTitleBg.g = 0xff;
  colorTitleBg.b = 0xff;
  colorTitleBg.a = 0x00;

  XuiCanvasSetBackground(XuiRootCanvas(), XUI_BG_NORMAL, NULL, colorTitleBg);

  StatusbarInit();

  return 0;
}

void Init(void)
{
  CrashReportInit();
  GuiInit();
  ScreenInit();
  OpenFont();

  return;
}

int DeInit()
{
  CloseFont();
  GuiDeinit();

  return 0;
}

void emv_test_open(void)
{
  /*Should return 0*/
  display("EMVCore Init %d", EMVCoreInit());
}

int main(int argc, char **argv)
{
  Init();
  robot_rock_execute();
  DeInit();

  return 0;
}

