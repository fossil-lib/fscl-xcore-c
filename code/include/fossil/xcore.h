/*
==============================================================================
Author: Michael Gene Brockus (Dreamer)
Email: michaelbrockus@gmail.com
Organization: Fossil Logic
Description: 
    This file is part of the Fossil Logic project, where innovation meets
    excellence in software development. Michael Gene Brockus, also known as
    "Dreamer," is a dedicated contributor to this project. For any inquiries,
    feel free to contact Michael at michaelbrockus@gmail.com.
==============================================================================
*/
#ifndef FSCL_XCORE_H
#define FSCL_XCORE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "xcore/datetime.h"
#include "xcore/thread.h"
#include "xcore/stream.h"
#include "xcore/fossil.h"
#include "xcore/console.h"
#include "xcore/regex.h"
#include "xcore/parser.h"
#include "xcore/error.h"
#include "xcore/soap.h"

/**
 * Get the codename associated with the library.
 *
 * @return A constant string representing the library's codename.
 */
inline const char* fscl_codename() {
    return "Paleozoic";
}

/**
 * Return a greeting message.
 *
 * @return A constant string containing a simple greeting message.
 */
inline const char* fscl_hello() {
    return "Hello, World!";
}

#ifdef __cplusplus
}
#endif

#endif
