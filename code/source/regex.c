/*  ----------------------------------------------------------------------------
    File: regex.c

    Description:
    This source file contains the code entry point for the Trilobite Stdlib project.
    It demonstrates the usage of various utilities and functions provided by the
    Trilobite Stdlib to enhance software development.

    Author: Michael Gene Brockus (Dreamer)
    Email: michaelbrockus@gmail.com
    Website: [Trilobite Coder Blog](https://trilobite.home.blog)

    Project: Trilobite Stdlib

    License: Apache License 2.0
    SPDX Identifier: Apache-2.0

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0.

    Unless required by applicable law or agreed to in writing, software distributed under the License
    is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
    or implied. See the License for the specific language governing permissions and limitations
    under the License.

    Please review the full text of the Apache License 2.0 for the complete terms and conditions.

    (Apache License 2.0: http://www.apache.org/licenses/LICENSE-2.0)
    ----------------------------------------------------------------------------
*/
#include "trilobite/xcore/regex.h"
#include <ctype.h>
#include <stdlib.h>

int tscl_regex_create(cregex *preg, const char *pattern) {
    preg->pattern = pattern;
    preg->matched_substring = NULL;
    return 0;  // Success
} // end of func

int tscl_regex_match(cregex *preg, const char *text) {
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

void tscl_regex_reset(cregex *preg) {
    preg->pattern = NULL;
    preg->matched_substring = NULL;
} // end of func

const char *tscl_regex_get_matched_substring(cregex *preg) {
    return preg->matched_substring;
} // end of func

const char *tscl_regex_match_and_extract(cregex *preg, const char *text) {
    if (tscl_regex_match(preg, text)) {
        // Call the function to extract the matched substring
        return tscl_regex_get_matched_substring(preg);
    } else {
        return NULL;
    }
} // end of func


