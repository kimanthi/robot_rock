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

// my test
#include "my_pipe.h"

//#include "mruby/backtrace.h"
mrb_value mrb_get_backtrace(mrb_state *mrb, mrb_value self);

const APPINFO AppInfo={
	"POS-Simple example",
	"APP-TEST",
	"1.0",
	"pcteam",
	"demo program",
	"",
	0,
	0,
	0,
	""
};

const uint8_t simplest_mrb[] = {
	0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x32,0x64,0xf3,0x00,0x00,0x00,0x73,0x4d,0x41,
	0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x55,0x30,0x30,
	0x30,0x30,0x00,0x00,0x00,0x49,0x00,0x01,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x04,
	0x00,0x80,0x00,0x06,0x01,0x00,0x00,0x3d,0x00,0x80,0x00,0xa0,0x00,0x00,0x00,0x4a,
	0x00,0x00,0x00,0x01,0x00,0x00,0x19,0x68,0x65,0x6c,0x6c,0x6f,0x20,0x42,0x65,0x65,
	0x72,0x20,0x3d,0x20,0x4d,0x72,0x75,0x62,0x79,0x20,0x3d,0x20,0x4c,0x6f,0x76,0x65,
	0x00,0x00,0x00,0x01,0x00,0x04,0x70,0x75,0x74,0x73,0x00,0x45,0x4e,0x44,0x00,0x00,
	0x00,0x00,0x08,
};

int event_main(ST_EVENT_MSG *msg)
{
	SystemInit();
	return 0;
}

size_t get_size(void * p) {
    unsigned int *in = p;
    if (in) { --in; return *in; }
    return -1;
}

unsigned long total_allocated_mem = 0;

int counter=0;

static void*
allocf2(mrb_state *mrb, void *p, size_t size, void *ud)
{
	void *new_ptr;

	if (size == 0) {
		if (p) free(p);
		return NULL;
	}
	else {
		//new_ptr = realloc(p, size);
		//new_ptr = my_realloc(p, size);
		//if(counter >= 398)
		//if(0)
		//{
			//printf("\nAllocar           ");
			//printf("\np %d err %d mem %lu s %d", p, new_ptr, total_allocated_mem, size);
			//DelayMs(2000);
			////new_ptr = (p) ? realloc(p, size) : new_ptr = malloc(size);
			//new_ptr = malloc(size);
			//printf("\nAllocou %d          ", new_ptr);
			//DelayMs(2000);
		//} else {
			//neallw_ptr = malloc(size);
		//}
		if (p)
			new_ptr = realloc(p, size);
		else
			new_ptr = malloc(size);

		if(!new_ptr){
			printf("\nerr %d mem %lu s %d", new_ptr, total_allocated_mem, size);
			//DelayMs(2000);
		} else {
			counter++;
			total_allocated_mem += size;
			//printf("\n%d %d %lu %d", new_ptr, counter, total_allocated_mem, p);
			//if(counter > 1070) DelayMs(2000);
			//DelayMs(50);
		}
	}

	return new_ptr;
}

//int testSimple(void)
//{
  //mrb_state *mrb = mrb_open();
  //char code[] = "a = 10";

  //printf("\nExecuting Ruby code with mruby!");
	//DelayMs(2000);

  //mrb_load_string(mrb, code);
	//DelayMs(2000);
  //return 0;
//}

//int testSimple0(void)
//{
  //mrb_state *mrb;// = mrb_open();
  //struct mrb_parser_state *parser;
  //char code[7] = "a = 10\x00";
	//mrbc_context *cxt;

  //printf("\nParse Ruby code with mruby %d!", strlen(code));
	//DelayMs(2000);

  //printf("\nmrb_open_allocf");
	//DelayMs(2000);
	//mrb = mrb_open_allocf(allocf2, NULL);
	////mrb = mrb_open();

  //printf("\nCreate ctx");
	//DelayMs(2000);
	//cxt = mrbc_context_new(mrb);
  ////cxt = (mrbc_context *)mrb_calloc(mrb, 1, sizeof(mrbc_context));

  //printf("\nCreate ctx 2");
	//DelayMs(2000);
	//cxt->capture_errors = 1;
	//cxt->lineno = 1;

  //printf("Create parser 1");
	//DelayMs(2000);
	//parser = mrb_parser_new(mrb);
  //printf("\nCreate parser 2");
	//DelayMs(2000);
	//parser->s = code;
  //printf("\nCreate parser 3");
	//DelayMs(2000);
	//parser->send = code + strlen(code);
  //printf("\nCreate parser 4");
	//DelayMs(2000);
	//parser->lineno = cxt->lineno;

  //printf("\nExecute parser");
	//DelayMs(2000);
	//mrb_parser_parse(parser, cxt);

  //printf("\nSucesso!");
  //return 0;
//}

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
	mrb = mrb_open_allocf(allocf2, NULL);
	//mrb = mrb_open();

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

//int testSimple4(void)
//{
	//int i=0;
	//int mem=1000;
	//char *ptr;
	//char *newptr;

	//printf("\nbefore testSimple4");
	//DelayMs(2000);
	//ptr = (char*)malloc(1000);
	//while(42)
	//{
		//i++;
		//mem+=1000;
		////printf("\nrealloc %d", i);
		//memcpy(ptr, "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", 1000);
		//newptr = (char*)malloc(mem);
		//printf("\n%d %d %d", i, newptr, mem);
		//if(newptr == NULL) DelayMs(10000);
		//memcpy(newptr, ptr, mem-1000);
		//free(ptr);
		//ptr = newptr;
		//DelayMs(200);
	//}
//}

void testSimple3(void)
{
	my_pipe3();
	my_pipe2();
	my_pipe();
}

int main(void)
{
	unsigned char time[7], time2[20], buff[20];
	//int fd[2];
	// http://matt.aimonetti.net/posts/2012/04/25/getting-started-with-mruby/
	//char buffer[10] = "Uhul!";

	//char code[20];
	//mrbc_context *cxt;
  //struct mrb_parser_state *parser;
  //mrb_state *mrb;
  //mrb_value result;
	//struct node *init=NULL, *p=NULL;
	//float fVal=1.1;
	//float fVal2=3.1;
	//float fVal3=0;
	//int iVal=0;

	SystemInit();

	//printf("------%d------", test_file());
	//testSimple1();

  testSimple3();

	DelayMs(20000);

	//printf("before float operation");
	//DelayMs(2000);
	//fVal3 = fVal2-fVal;

	//printf("before float operation 2");
	//DelayMs(2000);
	//iVal = (int)fVal3;

	//printf("before print int");
	//DelayMs(2000);
	//printf("iVal %d", iVal);

	//DelayMs(2000);
	//printf("float fedo %0.2f", fVal);
	//DelayMs(2000);
	//Lcdprintf("float fedo %0.2f", fVal);
	//DelayMs(2000);

	//insert(&init, p);
	//DelayMs(2000);
	//my_print(init);
	//DelayMs(2000);
	//printf("\nTooooooooootal   %d", count1(init));
	//DelayMs(2000);
	//printf("\nAverage %d", average(init));
	//DelayMs(2000);
	//clear1(init, p);

	//while(42)
	//{
		//printf("      PagSeguro UOL       ");
		//DelayMs(20000);
	//}

	//testMalloc();

	//mrb = mrb_open();
	//mrb = mrb_open_allocf(myallocf, NULL);
	//cxt = mrbc_context_new(mrb);
  //cxt->capture_errors = 1;
  //cxt->lineno = 1;

  //memset(code, 0, sizeof(code));
  //strcpy(code, "a = 1234");

	//DelayMs(2000);

	//parser = mrb_parser_new(mrb);
	//parser->s = code;
	//parser->send = code + strlen(code);
	//parser->lineno = cxt->lineno;
	//mrb_parser_parse(parser, cxt);

	DelayMs(10000);
	//while (1000) {
		////TODO: Start your application
		//ScrGotoxy(0, 0);
		//ScrAttrSet(1);
		//Lcdprintf("  Hello World!  ");
		//ScrAttrSet(0);
		//ScrGotoxy(0,3);
		//Lcdprintf(" Swiped card<<<");
		//while (1) {
			//GetTime(time);
			//if (!memcmp(time, time2, 6)) continue;
			//sprintf(buff, "%c%c/%c%c   %c%c:%c%c:%c%c",
					//(time[1] >> 4) + 0x30, (time[1] & 0x0f) + 0x30,
					//(time[2] >> 4) + 0x30, (time[2] & 0x0f) + 0x30,
					//(time[3] >> 4) + 0x30, (time[3] & 0x0f) + 0x30,
					//(time[4] >> 4) + 0x30, (time[4] & 0x0f) + 0x30,
					//(time[5] >> 4) + 0x30, (time[5] & 0x0f) + 0x30);
			//ScrGotoxy(0, 6);
			//Lcdprintf(buff);
			//memcpy(time2, time, 6);
		//}
	//}
	return 0;
}


