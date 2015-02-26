#ifndef KEYBOARD_H
#define KEYBOARD_H

/**
 * get key value (>=0), see macro in linux/input.h, such as KEY_1, KEY_CANCEL, etc.
 * return key value
 */
int GetKey(long timeout);

#endif

