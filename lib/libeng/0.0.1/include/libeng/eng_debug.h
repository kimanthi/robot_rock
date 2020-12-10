/**
 * @file eng_debug.h
 * @brief Debug public API.
 * @platform Pax Prolin
 * @date 2020-11-21
 * 
 * @copyright Copyright (c) 2020 CloudWalk, Inc.
 * 
 */

#ifndef _ENG_DEBUG_H_INCLUDED_
#define _ENG_DEBUG_H_INCLUDED_

/**********/
/* Macros */
/**********/

#define ENG_SERIAL 0
#define ENG_LOGCAT 1

#ifdef _ENG_DEBUG_
#ifndef ENG_TRACE
#define ENG_TRACE(...) eng_debug_send(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#endif /* #ifndef ENG_TRACE */

#ifndef ENG_TRACE_FUNCTION
#define ENG_TRACE_FUNCTION() ENG_TRACE(NULL)
#endif /* #ifndef ENG_TRACE_FUNCTION */

#ifndef ENG_TRACE_INIT
#define ENG_TRACE_INIT(...) eng_debug_init(__VA_ARGS__)
#endif /* #ifndef ENG_TRACE_INIT */
#else
#ifndef ENG_TRACE
#define ENG_TRACE(...)
#endif /* #ifndef ENG_TRACE */

#ifndef ENG_TRACE_FUNCTION
#define ENG_TRACE_FUNCTION()
#endif /* #ifndef ENG_TRACE_FUNCTION */

#ifndef ENG_TRACE_INIT
#define ENG_TRACE_INIT(...)
#endif /* #ifndef ENG_TRACE_INIT */
#endif /* #ifdef _ENG_DEBUG_ */

/********************/
/* Public functions */
/********************/

extern void
eng_debug_init(void);

extern void
eng_debug_send(const char *file, const int line, const char *function, const char *format, ...);

#endif /* #ifndef _ENG_DEBUG_H_INCLUDED_ */
