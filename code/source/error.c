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
#include "fossil/xcore/error.h"

enum {
    MAX_ERROR_BUFFER_SIZE = 1024
};

// Uppercase global variables
static cerror FSCL_CURRENT_ERROR = FSCL_CERROR_SUCCESS;
static const char* FSCL_ERROR_MESSAGES[] = {
    "No error.",
    "Invalid input.",
    "File not found.",
    "Memory allocation failed.",
    "Unknown type - GHOST TYPE!",
    "Something went wrong, but it's probably just a joke - COMEDY ERROR!",
    "Network error.",
    "Permission denied.",
    "Division by zero.",
    "Invalid operation.",
    "Resource unavailable.",
    "Timeout error.",
    "Database error.",
    "Configuration error.",
    "Unexpected result.",
    "Out of bounds.",
    "Invalid format.",
    "Logging failed.",
    "Failed to open media file.",
    "Failed to read from media.",
    "Failed to write to media.",
    "Unsupported media format.",
    "Failed to open output file.",
    "Failed to write to output.",
    "Unsupported output format.",
    "Failed to open input file.",
    "Failed to read from input.",
    "Unsupported input format.",
    "Memory overflow.",
    "Memory underflow.",
    "Failed to create thread.",
    "Failed to join thread."
};

// File for error logs
static FILE* error_log_file;

// Function to set error code
void fscl_error_set(cerror code) {
    FSCL_CURRENT_ERROR = code;
}

// Function to retrieve error message
const char* fscl_error_what() {
    return FSCL_ERROR_MESSAGES[FSCL_CURRENT_ERROR];
}

// Logging function with memorization
void fscl_error_log(const char* message) {
    size_t message_len = strlen(message);

    // If the message plus the current buffer exceeds the maximum size,
    // flush the buffer to the log file
    if (error_buffer_len + message_len >= MAX_ERROR_BUFFER_SIZE) {
        FILE* error_log_file = fopen("error_log.txt", "a");
        if (error_log_file != NULL) {
            fprintf(error_log_file, "%s", error_buffer);
            fclose(error_log_file);
            // Reset the buffer and length after flushing
            error_buffer[0] = '\0';
            error_buffer_len = 0;
        } else {
            // Set logging failed error if unable to open log file
            fscl_error_set(FSCL_CERROR_LOGGING_FAILED);
        }
    }

    // Append the new message to the buffer
    strncat(error_buffer, message, MAX_ERROR_BUFFER_SIZE - error_buffer_len);
    error_buffer_len += message_len;
}
