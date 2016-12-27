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

