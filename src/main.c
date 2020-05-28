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

/* Include the mruby header */
#include "mruby.h"
#include "mruby/value.h"
#include "mruby/compile.h"
#include "mruby/proc.h"

/*PAX*/
#include "osal.h"
#include "ui.h"
#include <xui.h>
#include "keyboard.h"
#include "debugger.h"
#include "runtime_system.h"

void context_memprof_init(mrb_allocf *funp, void **udp);

int robot_rock_execute(void)
{
  mrbc_context *c;
  mrb_state *mrb;
  mrb_allocf allocf;
  void *ud;

  context_memprof_init(&allocf, &ud);
  mrb = mrb_open_allocf(allocf, ud);

  c = mrbc_context_new(mrb);
  c->capture_errors = TRUE;
  c->no_optimize = TRUE;

  mrb_load_string_cxt(mrb, "Context.start('main', 'PAX'); Device::Runtime.start('main'); Context.execute('main', 'PAX');", c);

  mrbc_context_free(mrb, c);

  mrb_close(mrb);

  return 0;
}

static int GuiInit(void)
{
  int ret;
  char model[32]="\0";
  char *xui_argv_s920[] = {"ROTATE=90","STATUSBAR=16"};
  char *xui_argv_d200[] = {"ROTATE=0","STATUSBAR=22"};
  char *xui_argv_d195[] = {"ROTATE=0","STATUSBAR=22"};

  memset(&model, 0, sizeof(model));
  OsRegGetValue("ro.fac.mach", model);

  if (strcmp(model, "d200") == 0)
    ret = XuiOpen(2, xui_argv_d200);
  else if (strcmp(model, "D195") == 0)
    ret = XuiOpen(2, xui_argv_d195);
  else
    ret = XuiOpen(2, xui_argv_s920);

  if (ret == XUI_RET_OK)
    return RET_OK;
  else
    return -1;
}

static void GuiDeinit(void)
{
  XuiClose();
}

static void RobotRockCrash(int sig)
{
  mrbc_context *c;
  mrb_state *mrb;

  display("before crash");
  OsSaveCrashReport(sig);
  display("after crash");

  mrb = mrb_open();
  c = mrbc_context_new(mrb);
  ContextLog(mrb, 3, "CRASH");
  mrbc_context_free(mrb, c);
  mrb_close(mrb);

  OsReboot();
}

static void CrashReportInit(void)
{
  signal(SIGILL,    RobotRockCrash);
  signal(SIGABRT,   RobotRockCrash);
  signal(SIGBUS,    RobotRockCrash);
  signal(SIGFPE,    RobotRockCrash);
  signal(SIGSEGV,   RobotRockCrash);
  signal(SIGSTKFLT, RobotRockCrash);
  signal(SIGPIPE,   RobotRockCrash);
}

int ScreenInit(void)
{
  XuiColor colorTitleBg;

  colorTitleBg.r = 0xff;
  colorTitleBg.g = 0xff;
  colorTitleBg.b = 0xff;
  colorTitleBg.a = 0x00;

  XuiCanvasSetBackground(XuiRootCanvas(), XUI_BG_NORMAL, NULL, colorTitleBg);

  return 0;
}

void Init(void)
{
  char model[32]="\0";

  memset(&model, 0, sizeof(model));
	OsRegGetValue("ro.fac.mach", model);

  CrashReportInit();
  GuiInit();
  ScreenInit();

  if (strcmp(model, "d200") == 0) {
    OpenFont(0x00, 0x00, 0x00, 0xFF, D200_SCREEN_X, D200_SCREEN_Y,
        D200_LINE_WIDTH, D200_LINE_HEIGHT, "./res/inconsolata.ttf");
  } else if (strcmp(model, "D195") == 0) {
    OpenFont(0x00, 0x00, 0x00, 0xFF, D195_SCREEN_X, D195_SCREEN_Y,
        D195_LINE_WIDTH, D195_LINE_HEIGHT, "./res/inconsolata.ttf");
  } else {
    OpenFont(0x00, 0x00, 0x00, 0xFF, S920_SCREEN_X, S920_SCREEN_Y,
        S920_LINE_WIDTH, S920_LINE_HEIGHT, "./res/inconsolata.ttf");
  }

  return;
}

int DeInit()
{
  CloseFont();
  GuiDeinit();

  return 0;
}

int SystemInit(void);

int main(int argc, char **argv)
{
  Init();
  SystemInit();
  reload_flag = 1;
  while(reload_flag) {
    reload_flag = 0;
    robot_rock_execute();
    display_clear();
  }
  DeInit();

  return 0;
}

