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

const uint8_t start[] = {
  0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x32,0x28,0x53,0x00,0x00,0x00,0xa2,0x4d,0x41,
  0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x55,0x30,0x30,
  0x30,0x30,0x00,0x00,0x00,0x49,0x00,0x01,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x05,
  0x00,0x80,0x00,0x11,0x01,0x00,0x00,0x3d,0x01,0x80,0x00,0xbd,0x00,0x80,0x41,0x20,
  0x00,0x00,0x00,0x4a,0x00,0x00,0x00,0x02,0x00,0x00,0x04,0x6d,0x61,0x69,0x6e,0x00,
  0x00,0x03,0x50,0x41,0x58,0x00,0x00,0x00,0x02,0x00,0x07,0x43,0x6f,0x6e,0x74,0x65,
  0x78,0x74,0x00,0x00,0x05,0x73,0x74,0x61,0x72,0x74,0x00,0x44,0x42,0x47,0x00,0x00,
  0x00,0x00,0x2f,0x00,0x01,0x00,0x08,0x73,0x74,0x61,0x72,0x74,0x2e,0x72,0x62,0x00,
  0x00,0x00,0x1b,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,
  0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x45,0x4e,0x44,0x00,0x00,0x00,
  0x00,0x08,
};

void context_memprof_init(mrb_allocf *funp, void **udp);

int robot_rock_execute(void)
{
  mrbc_context *c;
  mrb_state *mrb;
  mrb_allocf allocf;
  void *ud;

  /*context_memprof_init(&allocf, &ud);*/

  /*mrb = mrb_open_allocf(allocf, ud);*/
  mrb = mrb_open();

  c = mrbc_context_new(mrb);

  mrb_load_irep_cxt(mrb, start, c);

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

  memset(&model, 0, sizeof(model));
  OsRegGetValue("ro.fac.mach", model);

  if (strcmp(model, "d200") == 0)
    ret = XuiOpen(2, xui_argv_d200);
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
  robot_rock_execute();
  DeInit();

  return 0;
}

