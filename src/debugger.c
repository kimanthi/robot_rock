/*------------------------------------------------------------
* FileName: debugger.c
* Author: LuX
* Date: 2013-04-12
------------------------------------------------------------*/
#include "header.h"
#include "mruby.h"
#include "mruby/value.h"
#include "mruby/compile.h"
#include "mruby/variable.h"
#include "mruby/string.h"

#include <unistd.h>
#include "osal.h"

#include "debugger.h"

/**
 * call this function if you want to debug source code.
 * return 0 if successful
 */
int start_debug()
{
	int ret = 0;
	pid_t mypid;
	pid_t pid;
	char idstr[16];
	mypid = getpid();
	pid = vfork();
	/* child */
	if (pid == 0)
	{
		snprintf(idstr, sizeof(idstr), "%u", (unsigned int)mypid);
		/* set TCP/IP port to default value 51000 */
		execlp("gdbserver", "gdbserver", "--attach", "127.0.0.1:51000", idstr, NULL);
		exit(127);
	}
	/* parent */
	else if (pid > 0) {
		/* wait for attached by gdbserver */
		sleep(5);
	}
	else {
		ret = -1;
	}
	return ret;
}

void ContextLog(mrb_state *mrb, int severity_level, const char *format, ...)
{
  char dest[1024];
  va_list argptr;

  va_start(argptr, format);
  vsprintf(dest, format, argptr);
  va_end(argptr);

  mrb_value msg, context;
  context = mrb_const_get(mrb, mrb_obj_value(mrb->object_class), mrb_intern_lit(mrb, "ContextLog"));
  msg = mrb_funcall(mrb, mrb_str_new(mrb, dest, strlen(dest)), "inspect", 0);
  if (severity_level == 3) /*Error*/
    mrb_funcall(mrb, context, "error", 1, msg);
  else
    mrb_funcall(mrb, context, "info", 1, msg);
}

