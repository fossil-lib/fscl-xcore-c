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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MAX_ERROR_BUFFER_SIZE = 1024
};

// Uppercase global variables
cerror FSCL_CURRENT_ERROR = FSCL_CERROR_SUCCESS;
const char* FSCL_ERROR_MESSAGES[] = {
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
FILE* error_log_file;

// Last logged error message and its length
char last_logged_error[MAX_ERROR_BUFFER_SIZE] = "";
size_t last_logged_error_len = 0;

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

    // Check if the message is different from the last logged error
    if (message_len != last_logged_error_len || strncmp(message, last_logged_error, message_len) != 0) {
        error_log_file = fopen("error_log.txt", "a");
        if (error_log_file != NULL) {
            fprintf(error_log_file, "Error: %s\n", message);
            fclose(error_log_file);

            // Update the last logged error
            strncpy(last_logged_error, message, sizeof(last_logged_error) - 1);
            last_logged_error[sizeof(last_logged_error) - 1] = '\0';
            last_logged_error_len = message_len;
        } else {
            fscl_error_set(FSCL_CERROR_LOGGING_FAILED);
        }
    }
}
