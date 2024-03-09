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
#ifndef FSCL_REGEX_H
#define FSCL_REGEX_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
    const char *pattern;
    const char *matched_substring;  // Added field to store the matched substring
} cregex;

// =================================================================
// Create and erase
// =================================================================

/**
 * Create a new regex pattern instance.
 *
 * @param preg    Pointer to the cregex structure to store the created regex pattern.
 * @param pattern The regex pattern to be compiled.
 * @return        0 on success, non-zero on failure.
 */
int fscl_regex_create(cregex *preg, const char *pattern);

/**
 * Match a text against a compiled regex pattern.
 *
 * @param preg Pointer to the cregex structure containing the compiled pattern.
 * @param text The text to be matched against the regex pattern.
 * @return     0 if there is a match, non-zero otherwise.
 */
int fscl_regex_match(cregex *preg, const char *text);

// =================================================================
// Available Functions
// =================================================================

/**
 * Reset the regex pattern instance to the initial state.
 *
 * @param preg Pointer to the cregex structure.
 */
void fscl_regex_reset(cregex *preg);

/**
 * Match a text against a compiled regex pattern and extract the matched substring.
 *
 * @param preg Pointer to the cregex structure containing the compiled pattern.
 * @param text The text to be matched against the regex pattern.
 * @return     A constant string containing the matched substring or NULL if no match.
 */
const char *fscl_regex_match_and_extract(cregex *preg, const char *text);

/**
 * Get the matched substring from the last successful match.
 *
 * @param preg Pointer to the cregex structure.
 * @return     A constant string containing the matched substring or NULL if no match.
 */
const char *fscl_regex_get_matched_substring(cregex *preg);

#ifdef __cplusplus
}
#endif

#endif
