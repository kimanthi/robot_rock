/* Include the mruby header */
#include "mruby.h"
#include "mruby/value.h"
#include "mruby/compile.h"
#include "mruby/proc.h"

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
      printf("\nerr %d mem %lu s %d", new_ptr, total_allocated_mem, size);
      DelayMs(60000);
    } else {
      counter++;
      total_allocated_mem += size;
    }
  }

  return new_ptr;
}

