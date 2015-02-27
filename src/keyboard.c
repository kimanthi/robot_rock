#include "constant.h"
#include "header.h"
#include "keyboard.h"
#include <sys/time.h>

/* Adds 'interval_ms' to timeval 'a' and store in 'result'
   - 'interval_ms' is in milliseconds */
static void add_ms_to_timeval(struct timeval *a, unsigned long interval_ms, struct timeval *result) {
  result->tv_sec = a->tv_sec + (interval_ms / 1000);
  result->tv_usec = a->tv_usec + ((interval_ms % 1000) * 1000);
  if (result->tv_usec > 1000000) {
    result->tv_usec -= 1000000;
    result->tv_sec++;
  }
}

static int compare_timeval(struct timeval *a, struct timeval *b)
{
  if (a->tv_sec > b->tv_sec)
    return 1;
  else if (a->tv_sec < b->tv_sec)
    return -1;
  else if (a->tv_usec > b->tv_usec)
    return 1;
  else if (a->tv_usec < b->tv_usec)
    return -1;
  return 0;
}

/**
 * keyboard test case
 * return KEY if successful
 * return 18 if timeout
 */
int GetKey(long timeout)
{
  struct timeval tv1, tv2;
  int i;
  int rd;
  static struct input_event ev[64];
  int flag = 1;
  int event_num;
  int size = sizeof(struct input_event);
  int fd = open(KEYBOARD_NAME, O_RDONLY | O_NONBLOCK);

  gettimeofday(&tv1, NULL);
  add_ms_to_timeval(&tv1, timeout, &tv1);

  while (flag == 1) {
    rd = read(fd, ev, sizeof(ev));

    if (rd < size) {
      if (timeout != 0) {
        gettimeofday(&tv2, NULL);
        if (compare_timeval(&tv2, &tv1) == 1) return 18;
      }

      continue;
    }

    event_num = rd / size;
    for (i = 0; i < event_num; ++i) {
      if (ev[i].type == EV_KEY) return ev[i].code;
    }
  }
  close(fd);
  return 0;
}
