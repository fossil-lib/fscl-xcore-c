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
#include "fossil/xcore/regex.h"
#include <ctype.h>
#include <stdlib.h>

int fscl_regex_create(cregex *preg, const char *pattern) {
    preg->pattern = pattern;
    preg->matched_substring = NULL;
    return 0;  // Success
} // end of func

int fscl_regex_match(cregex *preg, const char *text) {
    while (*text != '\0') {
        if (tolower(*preg->pattern) == tolower(*text) || *preg->pattern == '.') {
            preg->pattern++;
            text++;
        } else if (*(preg->pattern) == '*' && (tolower(*(preg->pattern - 1)) == tolower(*text))) {
            preg->pattern++;
        } else if (*(preg->pattern) == '*' && (tolower(*(preg->pattern - 1)) != tolower(*text))) {
            text++;
        } else if (*(preg->pattern + 1) == '*') {
            preg->pattern += 2;
        } else {
            return 0;  // No match
        }
    }

    preg->matched_substring = text;

    return (*preg->pattern == '\0');
} // end of func

void fscl_regex_reset(cregex *preg) {
    preg->pattern = NULL;
    preg->matched_substring = NULL;
} // end of func

const char *fscl_regex_get_matched_substring(cregex *preg) {
    return preg->matched_substring;
} // end of func

const char *fscl_regex_match_and_extract(cregex *preg, const char *text) {
    if (fscl_regex_match(preg, text)) {
        // Call the function to extract the matched substring
        return fscl_regex_get_matched_substring(preg);
    } else {
        return NULL;
    }
} // end of func


