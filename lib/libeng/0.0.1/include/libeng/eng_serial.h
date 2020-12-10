/**
 * @file eng_serial.h
 * @brief Serial public API.
 * @platform Pax Prolin
 * @date 2020-11-19
 * 
 * @copyright Copyright (c) 2020 CloudWalk, Inc.
 * 
 */

#ifndef _ENG_SERIAL_H_INCLUDED_
#define _ENG_SERIAL_H_INCLUDED_

/**********/
/* Macros */
/**********/

#define ENG_SERIAL_CHANNEL_USB 1
#define ENG_SERIAL_CHANNEL_COM 0

/********************/
/* Public functions */
/********************/

extern int
eng_serial_close(int channel);

extern int
eng_serial_init(void);

extern int
eng_serial_open(int channel, char *attr);

extern int
eng_serial_recv(int channel, char *buffer, long unsigned int length, unsigned int timeout);

extern int
eng_serial_send(int channel, char *buffer, long unsigned int length);

#endif /* #ifndef _ENG_SERIAL_H_INCLUDED_ */
