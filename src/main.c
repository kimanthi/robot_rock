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

int robot_rock_execute(void)
{
  mrb_state *mrb;

  //char code[] = "Device::Walk.execute('main.mrb')";
  //char code[] = "Device::Walk.load";
  //char code[] = "require './da_funk.mrb'; Device::Walk.start";
  /*char code[] = "print 'aaaaaaa'; sleep 2; p 'BBBBBB'; sleep 2";*/
  /*char code[] = "print 'aaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbcccccccccccccccccccccddddd\ndddd\ndddddd\ndddddddd'; sleep 2; p 'BBBBBB'; sleep 2";*/
  /*char code[] = "print 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbcccccccccccccccccccccccccccccccccccccccddddd\ndddd\ndddddd\ndddddddd'; sleep 10; p 'BBBBBB'; sleep 2";*/
  /*char code[] = "print '1234567890123456789012345678901234567890'; sleep 2; puts 'BBBBBBBBBBBBBBBBBBBBBBBBBBBB'; puts 'CCCCCCCCCCCCCC'; sleep 30";*/
  /*char code[] = "puts '1234567890123456789012345678901234567890'; puts 'BBBBBBBBBBBBBBBBBBBBBBBBBBBB'; puts 'CCCCCCCCCCCCCC'; sleep 5";*/
  /*char code[] = "puts 'before'; sleep 2; require './mrb/main.mrb'; sleep 2; puts 'after'; sleep 10";*/
  char code[] = "PAX.start";

  //DEBUG
  /*display("Parse Ruby code with mruby");*/
  /*printf("\nParse Ruby code with mruby\n");*/

  //DEBUG
  /*display("mrb_open");*/
  /*mrb = mrb_open_allocf(pax_allocf, NULL);*/
  mrb = mrb_open();

  //DEBUG
  /*display("mrb_load_string\n");*/
  mrb_load_string(mrb, code);

  //DEBUG
  //printf("\nbacktrace");
  //DelayMs(2000);
  //mrb_output_backtrace(mrb, mrb->exc, my_func, (void *)stderr);

  //DEBUG
  /*sleep(5);*/
  /*display("mrb_close");*/
  /*sleep(2);*/
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
  char *bgfilename;
  XuiImg *imgBg;
  XuiColor colorTitleBg;

  if (XuiRootCanvas()->width >=320) {
    bgfilename = "./res/bg_320x240.png";
  }
  else {
    bgfilename = "./res/bg_240x320.png";
  }

  /* load image */
  imgBg = XuiImgLoadFromFile(bgfilename);

  /* set background */
  colorTitleBg.r = 0x10;
  colorTitleBg.g = 0x00;
  colorTitleBg.b = 0xfe;
  colorTitleBg.a = 0xff;
  XuiCanvasSetBackground(XuiRootCanvas(), XUI_BG_CENTER, imgBg, colorTitleBg);
  /* after SetBackground, the imgBg can free it */
  XuiImgFree(imgBg);
  imgBg = NULL;

  /* init statusbar */
  StatusbarInit();

  return 0;
}

int Init()
{
  CrashReportInit();
  GuiInit(18);
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

int main(int argc, char **argv)
{
  OsLog(LOG_INFO, "Teste");
  Init();

  robot_rock_execute();
  DeInit();
  OsLog(LOG_INFO, "Finish");

  return 0;
}

