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

/**
 * Sanitize a string by replacing curse words with asterisks.
 *
 * @param input The input string to be sanitized in-place.
 */
void fscl_soap_sanitize(char *input);

/**
 * Check if a word is a curse word or racist phrase.
 *
 * @param word The word to be checked for offensiveness.
 * @return     True if the word is offensive, false otherwise.
 */
bool fscl_soap_is_offensive(const char *word);

/**
 * Get the number of offensive words found in a string.
 *
 * @param input The input string to be checked for offensive words.
 * @return      The number of offensive words found.
 */
int fscl_soap_count_offensive(const char *input);

/**
 * Duplicate a string using a custom strdup utility function.
 *
 * @param str The string to be duplicated.
 * @return    A dynamically allocated string containing the duplicated content.
 */
char *fscl_soap_strdup(const char *str);

#ifdef __cplusplus
}
#endif

#endif
