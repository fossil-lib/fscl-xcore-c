/*  ----------------------------------------------------------------------------
    File: lambda.c

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
#include "trilobite/xcore/lazy.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Function to create a lazy type
clazy tscl_lazy_create(clazy_type type) {
    clazy lazy;
    lazy.is_evaluated = 0;
    lazy.type = type;
    return lazy;
}

// Function to force the evaluation of the lazy type
void tscl_lazy_force(clazy *lazy) {
    if (!lazy->is_evaluated) {
        switch (lazy->type) {
            case CLAZY_INT:
                lazy->data.int_value = 0;  // Default value for int
                lazy->cache.memoized_int = lazy->data.int_value;
                break;
            case CLAZY_BOOL:
                lazy->data.bool_value = false;  // Default value for bool
                lazy->cache.memoized_bool = lazy->data.bool_value;
                break;
            case CLAZY_CHAR:
                lazy->data.char_value = '\0';  // Default value for char
                lazy->cache.memoized_char = lazy->data.char_value;
                break;
            case CLAZY_STRING:
                lazy->data.string_value.data = NULL;  // Default value for string
                lazy->cache.memoized_string = lazy->data.string_value;
                break;
            case CLAZY_NULL:
                // No evaluation needed for null type
                break;
            default:
                // Handle unknown type
                break;
        }
        lazy->is_evaluated = 1;
    }
}

// Function to retrieve the value or default value if not evaluated
int tscl_lazy_force_int(clazy *lazy) {
    tscl_lazy_force(lazy);
    return lazy->cache.memoized_int;
}

bool tscl_lazy_force_bool(clazy *lazy) {
    tscl_lazy_force(lazy);
    return lazy->cache.memoized_bool;
}

char tscl_lazy_force_char(clazy *lazy) {
    tscl_lazy_force(lazy);
    return lazy->cache.memoized_char;
}

const char* tscl_lazy_force_string(clazy *lazy) {
    tscl_lazy_force(lazy);
    return lazy->cache.memoized_string.data;
}

// Function to destroy the resources associated with a string value
void tscl_lazy_erase(clazy *lazy) {
    if (lazy->is_evaluated) {
        switch (lazy->type) {
            case CLAZY_STRING:
                free(lazy->cache.memoized_string.data);
                break;
            default:
                // No resources to free for other types
                break;
        }
    }
}

// Function to create a lazy sequence of integers
clazy tscl_lazy_sequence() {
    clazy lazy;
    lazy.is_evaluated = 0;
    lazy.type = CLAZY_INT;
    return lazy;
}

// Function to force the evaluation of the lazy sequence
int tscl_lazy_sequence_force(clazy *lazy, int n) {
    if (!lazy->is_evaluated) {
        lazy->data.int_value = n;
        lazy->cache.memoized_int = lazy->data.int_value;
        lazy->is_evaluated = 1;
    }
    return lazy->cache.memoized_int;
}
