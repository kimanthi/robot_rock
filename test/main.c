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
#include "mruby/compile.h"
#include "mruby/proc.h"

const APPINFO AppInfo={
	"CloudWalk Framework",
	"CloudWalk Framework",
	"0.4.2",
	"pcteam",
	"CloudWalk Framework",
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

mrb_value mrb_get_backtrace(mrb_state *mrb, mrb_value self);

int testSimple1(void)
{
	mrb_state *mrb;
	mrb_value exc;
	mrb_value backtrace;
	//char code[] = "def fib n; return n if n < 2; fib(n-2) + fib(n-1); end ; puts fib(25)";
	//char code[] = "puts Time.now";
	char code[] = "puts 'Cheguei'; f = File.open('w', 'test'); f.write('MALUCO'); f.close; puts File.read('test')";
	//char code[] = "puts 'Cheguei'";

	printf("\nParse Ruby code with mruby\n");

	printf("\nmrb_open 1");
	DelayMs(2000);
	mrb = mrb_open_allocf(pax_allocf, NULL);

	printf("\nmrb_load_string\n");
	DelayMs(2000);
	mrb_load_string(mrb, code);

	printf("\nbacktrace");
	DelayMs(2000);
	exc = mrb_obj_value(mrb->exc);
	printf("\nexc%d", exc.tt);
	DelayMs(2000);
	backtrace = mrb_get_backtrace(mrb, exc);
	printf("\nback:%d", backtrace.tt);
	DelayMs(2000);
	//printf("\n%s", mrb_str_to_cstr(mrb, mrb_inspect(mrb, backtrace)));

	printf("\nSucesso!");
	DelayMs(2000);
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

int main(void)
{
	unsigned char time[7], time2[20], buff[20];
	SystemInit();

  while (1000) {
    ScrGotoxy(0, 0);
    ScrAttrSet(1);
    while (42) {
      testSimple1();
      DelayMs(20000);
    }
  }

	return 0;
}


