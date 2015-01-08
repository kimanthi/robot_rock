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

#include "osal.h"
#include "ui.h"

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

mrb_state *mrb;

mrb_state *mrb_robot(void)
{
  return mrb;
}

int robot_rock_execute(void)
{
  mrbc_context *c;
  char code[] = "PAX.start";
  mrb = mrb_open();

  c = mrbc_context_new(mrb);

  mrb_load_string_cxt(mrb, code, c);

  mrbc_context_free(mrb, c);

  mrb_close(mrb);

  return 0;
}

static int GuiInit(int statusbar_height)
{
  char value[128];
  char rotate_str[32];
  char statusbar_str[32];
  int ret;
  char *xui_argv[10];
  int  xui_argc;

  ret = OsRegGetValue("ro.fac.lcd.rotate", value);
  if (ret > 0) {
    snprintf(rotate_str, sizeof(rotate_str), "ROTATE=%s", value);
  }
  else {
    strcpy(rotate_str, "ROTATE=0");
  }

  if (statusbar_height > 0) {
    snprintf(statusbar_str, sizeof(statusbar_str), "STATUSBAR=%d", statusbar_height);
  }
  else {
    strcpy(statusbar_str, "STATUSBAR=0");
  }

  xui_argv[0] = rotate_str;
  xui_argv[1] = statusbar_str;
  xui_argv[2] = NULL;
  xui_argc = 2;

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
  GuiInit(22);
  ScreenInit();
  OpenFont();

  /*if (OpenFont(FONT_NAME) < 0) {*/
  /*return -1;*/
  /*}*/
  /*if (OpenLcd() < 0) {*/
  /*return -1;*/
  /*}*/
  /*if (OpenKeyboard(KEYBOARD_NAME) < 0) {*/
  /*return -1;*/
  /*}*/
  return 0;
}

int DeInit()
{
  CloseFont();
  GuiDeinit();

  return 0;
}

void playMario(void)
{
  int fd, ret = 0;
  char *buff;
  int len;
  struct stat state;
  char FILENAME[20]="./res/smb_coin.wav";

  stat(FILENAME, &state);
  len = state.st_size;
  display("len %d\n", len);
  buff = (char *) malloc(len * sizeof(char));
  fd = open(FILENAME, O_RDONLY);

  if(fd<0) display("Open File Fail\n");

  ret = read(fd, buff, len);
  ret = OsPlayWave(buff, len, 3, 0);

  if(ret != RET_OK) display("PlayWave Fail %d\n", ret);

  close(fd);
  free(buff);
}

void playTone(void)
{
  OsBeep(0, 200);
  OsBeep(1, 200);
  OsBeep(2, 200);
  OsBeep(3, 200);
  OsBeep(4, 200);
  OsBeep(5, 200);
  OsBeep(6, 200);

  sleep(2);

  OsBeep(0, 200);
  OsBeep(1, 200);
  OsBeep(0, 200);
  sleep(1);
  OsBeep(0, 200);
  OsBeep(1, 200);

  sleep(2);
  OsBeep(0, 200);
  OsBeep(1, 200);
  OsBeep(0, 200);
  sleep(1);
  OsBeep(0, 200);
  OsBeep(1, 200);

}

int img_sample(int argc, char **argv)
{
  XuiFont *font_simsun_0;
  char *xui_argv[] = {"ROTATE=0","STATUSBAR=22"};
  XuiImg *img_bg;
  XuiColor colorTitleBg;
  /*XuiWindow *gifSoldier;*/

  XuiOpen(sizeof(xui_argv)/sizeof(xui_argv[0]), xui_argv);

  /*colorTitleBg.r = 0xff;*/
  /*colorTitleBg.g = 0xff;*/
  /*colorTitleBg.b = 0xff;*/
  /*colorTitleBg.a = 0x00;*/
  /*XuiCanvasSetBackground(XuiRootCanvas(), XUI_BG_NORMAL, NULL, colorTitleBg);*/

  font_simsun_0 = XuiCreateFont("./res/arial.ttf", 0, 0);
  img_bg = XuiImgLoadFromFile("./res/qrcode4.bmp");

  XuiSetStatusbarIcon(0,"./res/mobile100.png");
  XuiSetStatusbarIcon(1,"./res/modem.png");
  XuiSetStatusbarIcon(2,"./res/ethernet.png");
  XuiSetStatusbarIcon(3,"./res/wifi100.png");
  XuiSetStatusbarIcon(4,"./res/lock.png");
  XuiSetStatusbarIcon(5,"./res/card.png");
  XuiSetStatusbarIcon(6,"./res/print.png");
  XuiSetStatusbarIcon(7,"./res/battery50.png");

  /*gifSoldier = XuiCreateGif(XuiRootCanvas(), 0, 0, 159, 159, "./res/qrcode.bmp");*/
  /*XuiShowWindow(gifSoldier, 1, 1);*/

  XuiCanvasDrawImg(XuiRootCanvas(), 0, 0, img_bg->width, img_bg->height, XUI_BG_NORMAL, img_bg);

  XuiGetKey();
  return 0;
}

int main(int argc, char **argv)
{
  OsLog(LOG_INFO, "Teste");
  Init();
  robot_rock_execute();
  DeInit();
  OsLog(LOG_INFO, "Finish");

  return 0;
}

