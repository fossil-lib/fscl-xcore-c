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

// Utility function to set the value of a lazy integer
void tscl_lazy_set_int(clazy *lazy, int value) {
    lazy->is_evaluated = 1;
    lazy->data.int_value = value;
}

// Setter function for lazy string
void tscl_lazy_set_cstring(clazy *lazy, const char *value) {
    lazy->is_evaluated = 1;
    size_t len = strlen(value);
    lazy->data.string_value.data = malloc(len + 1);
    strcpy(lazy->data.string_value.data, value);
    lazy->cache.memoized_string = lazy->data.string_value;
}

// Utility function to set the value of a lazy integer
void tscl_lazy_set_bool(clazy *lazy, bool value) {
    lazy->is_evaluated = 1;
    lazy->data.bool_value = value;
}

// Utility function to set the value of a lazy integer
void tscl_lazy_set_letter(clazy *lazy, char value) {
    lazy->is_evaluated = 1;
    lazy->data.char_value = value;
}

// Utility function for conditional evaluation of lazy type
void tscl_lazy_conditional_eval(clazy *lazy, int condition) {
    if (condition) {
        tscl_lazy_force(lazy);
    }
}

// Utility function to map a function over a lazy integer
void tscl_lazy_map_int(clazy *lazy, int (*mapFunction)(int)) {
    tscl_lazy_force(lazy);
    lazy->data.int_value = mapFunction(lazy->data.int_value);
}

// Utility function to map a function over a lazy bool
void tscl_lazy_map_bool(clazy *lazy, bool (*mapFunction)(bool)) {
    tscl_lazy_force(lazy);
    lazy->data.bool_value = mapFunction(lazy->data.bool_value);
}

// Utility function to map a function over a lazy char
void tscl_lazy_map_char(clazy *lazy, char (*mapFunction)(char)) {
    tscl_lazy_force(lazy);
    lazy->data.char_value = mapFunction(lazy->data.char_value);
}

// Utility function to map a function over a lazy string
void tscl_lazy_map_cstring(clazy *lazy, const char* (*mapFunction)(const char*)) {
    tscl_lazy_force(lazy);
    const char* result = mapFunction(lazy->data.string_value.data);
    size_t len = strlen(result);
    lazy->data.string_value.data = realloc(lazy->data.string_value.data, len + 1);
    strcpy(lazy->data.string_value.data, result);
}

// Utility function for string concatenation of two lazy strings
void tscl_lazy_concat_cstrings(clazy *result, clazy *str1, clazy *str2) {
    tscl_lazy_force(str1);
    tscl_lazy_force(str2);

    size_t len1 = strlen(str1->cache.memoized_string.data);
    size_t len2 = strlen(str2->cache.memoized_string.data);

    result->data.string_value.data = malloc(len1 + len2 + 1);
    strcpy(result->data.string_value.data, str1->cache.memoized_string.data);
    strcat(result->data.string_value.data, str2->cache.memoized_string.data);

    result->is_evaluated = 1;
    result->type = CLAZY_STRING;
}

// Utility function to print the value of a lazy type
void tscl_lazy_print(clazy *lazy) {
    tscl_lazy_force(lazy);
    switch (lazy->type) {
        case CLAZY_INT:
            printf("Value (int): %d\n", lazy->data.int_value);
            break;
        case CLAZY_BOOL:
            printf("Value (bool): %s\n", lazy->data.bool_value ? "true" : "false");
            break;
        case CLAZY_CHAR:
            printf("Value (char): %c\n", lazy->data.char_value);
            break;
        case CLAZY_STRING:
            printf("Value (string): %s\n", lazy->data.string_value.data);
            break;
        default:
            printf("Unsupported type\n");
            break;
    }
}