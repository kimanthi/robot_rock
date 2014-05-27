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

// file
#include "my_stat.h"

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
	SystemInit();
	return 0;
}

unsigned long total_allocated_mem = 0;
int counter=0;

static void*
pax_allocf(mrb_state *mrb, void *p, size_t size, void *ud)
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
			printf("\nerr %d mem %lu s %d", new_ptr, total_allocated_mem, size);
		} else {
			counter++;
			total_allocated_mem += size;
		}
	}

	return new_ptr;
}

typedef void (*output_stream_func)(mrb_state*, void*, int, const char*, ...);
//mrb_value mrb_get_backtrace(mrb_state *mrb, mrb_value self);
void mrb_output_backtrace(mrb_state *mrb, struct RObject *exc, output_stream_func func, void *stream);

static void
my_func(mrb_state *mrb, void *stream, int level, const char *format, ...)
{
  va_list ap;

  printf("\nbacktrace:\n");
  va_start(ap, format);
  //vfprintf((FILE*)stream, format, ap);
  printf(format, ap);
  //va_end(ap);
}

int testSimple1(void)
{
	mrb_state *mrb;
	mrb_value exc;
	mrb_value backtrace;
  //char code[] = "puts 'Cheguei'";
	//char code[] = "def fib n; return n if n < 2; fib(n-2) + fib(n-1); end ; puts fib(25)";
	//char code[] = "puts Time.now";
  //char code[] = "puts 'Cheguei'; puts (f = File.open('test', 'w')); puts(f.write('MALUCO')); puts(f.close); k = File.open('test', 'r') ; puts(k.read); k.close";
  char code[] = "puts 'Cheguei'; puts Kernel.getc; puts Kernel.getc; puts IO.getc; puts 'fim'";
  //char code[] = "puts 'Cheguei'; puts Kernel.gets('4'); puts 'fim'";

	printf("\nParse Ruby code with mruby\n");

	printf("\nmrb_open");
	DelayMs(2000);
	mrb = mrb_open_allocf(pax_allocf, NULL);

	printf("\nmrb_load_string\n");
	DelayMs(2000);
  mrb_load_string(mrb, code);

	//printf("\nbacktrace");
	//DelayMs(2000);
  //mrb_output_backtrace(mrb, mrb->exc, my_func, (void *)stderr);

	printf("\nSucesso!");
	DelayMs(2000);

	printf("\nmrb_close");
	DelayMs(2000);
	mrb_close(mrb);

	return 0;
}

//int testSimple2(void)
//{
	//int n;
	//mrb_state *mrb;

	//printf("\nParse Ruby code with mruby\n");
	//DelayMs(2000);

	//printf("\nmrb_open\n");
	//DelayMs(2000);
	//mrb = mrb_open_allocf(allocf2, NULL);
	////mrb = mrb_open();

	////printf("\nmrb_load_irep");
	//DelayMs(2000);
	//mrb_load_irep(mrb, simplest_mrb);

	//printf("\nmrb_close");
	//DelayMs(2000);
	//mrb_close(mrb);

	//printf("\nSucesso!");
	//DelayMs(2000);
	//return 0;
//}

int testSimple3(void)
{
  //test_stat("test3");
  //create_file_and_directory();
  //stat_info();
  //stat_info2();
  //stat_info4();
  //file_basename();
  //file_exists();
  //file_size();
  //file_rename();
  //stat_info4();
  //get_pax_key();
  //get_pax_string();
  get_pax_hz_string();
}

int main(void)
{
  //unsigned char time[7], time2[20], buff[20];
  SystemInit();
  //InitFileSys();

  while (42) {
    //ScrGotoxy(0, 0);
    //ScrAttrSet(1);
    while (42) {
      testSimple1();
      DelayMs(20000);
    }
  }

  return 0;
}

