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
// create and erase
// =================================================================
int fscl_regex_create(cregex *preg, const char *pattern);
int fscl_regex_match(cregex *preg, const char *text);

// =================================================================
// avaliable functions
// =================================================================
void fscl_regex_reset(cregex *preg);
const char *fscl_regex_match_and_extract(cregex *preg, const char *text);
const char *fscl_regex_get_matched_substring(cregex *preg);

#ifdef __cplusplus
}
#endif

#endif
