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
#ifndef FSCL_ERROR_H
#define FSCL_ERROR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>

// Error codes
typedef enum {
    FSCL_CERROR_SUCCESS,
    FSCL_CERROR_INVALID_INPUT,
    FSCL_CERROR_FILE_NOT_FOUND,
    FSCL_CERROR_MEMORY_ALLOCATION_FAILED,
    FSCL_CERROR_GHOST_TYPE,
    FSCL_CERROR_COMEDY_ERROR,
    FSCL_CERROR_NETWORK_ERROR,
    FSCL_CERROR_PERMISSION_DENIED,
    FSCL_CERROR_DIVISION_BY_ZERO,
    FSCL_CERROR_INVALID_OPERATION,
    FSCL_CERROR_RESOURCE_UNAVAILABLE,
    FSCL_CERROR_TIMEOUT,
    FSCL_CERROR_DATABASE_ERROR,
    FSCL_CERROR_CONFIGURATION_ERROR,
    FSCL_CERROR_UNEXPECTED_RESULT,
    FSCL_CERROR_OUT_OF_BOUNDS,
    FSCL_CERROR_INVALID_FORMAT,
    FSCL_CERROR_LOGGING_FAILED,
    FSCL_CERROR_MEDIA_OPEN_FAILED,
    FSCL_CERROR_MEDIA_READ_FAILED,
    FSCL_CERROR_MEDIA_WRITE_FAILED,
    FSCL_CERROR_MEDIA_UNSUPPORTED_FORMAT,
    FSCL_CERROR_OUTPUT_OPEN_FAILED,
    FSCL_CERROR_OUTPUT_WRITE_FAILED,
    FSCL_CERROR_OUTPUT_UNSUPPORTED_FORMAT,
    FSCL_CERROR_INPUT_OPEN_FAILED,
    FSCL_CERROR_INPUT_READ_FAILED,
    FSCL_CERROR_INPUT_UNSUPPORTED_FORMAT,
    FSCL_CERROR_MEMORY_OVERFLOW,
    FSCL_CERROR_MEMORY_UNDERFLOW,
    FSCL_CERROR_THREAD_CREATION_FAILED,
    FSCL_CERROR_THREAD_JOIN_FAILED
} cerror;

// Uppercase global variables
extern cerror FSCL_CURRENT_ERROR;
extern const char* FSCL_ERROR_MESSAGES[];

// File for error logs
extern FILE* error_log_file;

// Last logged error message and its length
extern char last_logged_error[];
extern size_t last_logged_error_len;

// =================================================================
// error functions
// =================================================================

// Function to set error code
void fscl_error_set(cerror code);

// Function to retrieve error message
const char* fscl_error_what();

// Logging function
void fscl_error_log(const char* message);

#ifdef __cplusplus
}
#endif

#endif
