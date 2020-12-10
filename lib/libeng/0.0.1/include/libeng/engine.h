/**
 * @file engine.h
 * @brief Payment Engine's public API.
 * @platform Pax Prolin
 * @date 2020-11-19
 * 
 * @copyright Copyright (c) 2020 CloudWalk, Inc.
 * 
 */

#ifndef _ENGINE_H_INCLUDED_
#define _ENGINE_H_INCLUDED_

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif /* #ifndef EXIT_FAILURE */

typedef enum EN_ERROR
{
    ENG_EN_OK = 0,
    ENG_EN_FAILURE = - EXIT_FAILURE - 99999,
    ENG_EN_INV_ARGUMENT,
    ENG_EN_MEM_FAILURE,
    ENG_EN_NOT_SUPPORTED,
    ENG_EN_TIMEOUT,

    ENG_EN_MARKER
} ENG_EN_ERROR;

#include "eng_debug.h"
#include "eng_serial.h"

#endif /* #ifndef _ENGINE_H_INCLUDED_ */
