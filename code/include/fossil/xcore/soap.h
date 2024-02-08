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
#ifndef FSCL_SOAP_H
#define FSCL_SOAP_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>

// =================================================================
// Clean soap functions
// =================================================================

// Function to sanitize a string by replacing curse words with asterisks
void fscl_soap_sanitize(char *input);

// Function to check if a word is a curse word or racist phrase
bool fscl_soap_is_offensive(const char *word);

// Function to get the number of offensive words found in a string
int fscl_soap_count_offensive(const char *input);

// Custom strdup utility function
char *fscl_soap_strdup(const char *str);

#ifdef __cplusplus
}
#endif

#endif
