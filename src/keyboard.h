#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "mruby.h"
#include "mruby/value.h"
#include "mruby/compile.h"
#include "mruby/proc.h"

/**
 * get key value (>=0), see macro in linux/input.h, such as KEY_1, KEY_CANCEL, etc.
 * return key value
 */
int GetKey(mrb_state *mrb, long timeout);
int GetMainKey(mrb_state *mrb, long timeout);

#endif

