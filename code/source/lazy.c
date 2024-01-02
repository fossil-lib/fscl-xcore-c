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
#include "fossil/xcore/lazy.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Function to create a lazy type
clazy fscl_lazy_create(clazy_type type) {
    clazy lazy;
    lazy.is_evaluated = 0;
    lazy.type = type;
    return lazy;
}

// Function to force the evaluation of the lazy type
void fscl_lazy_force(clazy *lazy) {
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
int fscl_lazy_force_int(clazy *lazy) {
    fscl_lazy_force(lazy);
    return lazy->cache.memoized_int;
}

bool fscl_lazy_force_bool(clazy *lazy) {
    fscl_lazy_force(lazy);
    return lazy->cache.memoized_bool;
}

char fscl_lazy_force_char(clazy *lazy) {
    fscl_lazy_force(lazy);
    return lazy->cache.memoized_char;
}

const char* fscl_lazy_force_string(clazy *lazy) {
    fscl_lazy_force(lazy);
    return lazy->cache.memoized_string.data;
}

// Function to destroy the resources associated with a string value
void fscl_lazy_erase(clazy *lazy) {
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
clazy fscl_lazy_sequence() {
    clazy lazy;
    lazy.is_evaluated = 0;
    lazy.type = CLAZY_INT;
    return lazy;
}

// Function to force the evaluation of the lazy sequence
int fscl_lazy_sequence_force(clazy *lazy, int n) {
    if (!lazy->is_evaluated) {
        lazy->data.int_value = n;
        lazy->cache.memoized_int = lazy->data.int_value;
        lazy->is_evaluated = 1;
    }
    return lazy->cache.memoized_int;
}

// Utility function to set the value of a lazy integer
void fscl_lazy_set_int(clazy *lazy, int value) {
    lazy->is_evaluated = 1;
    lazy->data.int_value = value;
}

// Setter function for lazy string
void fscl_lazy_set_cstring(clazy *lazy, const char *value) {
    lazy->is_evaluated = 1;
    size_t len = strlen(value);
    lazy->data.string_value.data = malloc(len + 1);
    strcpy(lazy->data.string_value.data, value);
    lazy->cache.memoized_string = lazy->data.string_value;
}

// Utility function to set the value of a lazy integer
void fscl_lazy_set_bool(clazy *lazy, bool value) {
    lazy->is_evaluated = 1;
    lazy->data.bool_value = value;
}

// Utility function to set the value of a lazy integer
void fscl_lazy_set_letter(clazy *lazy, char value) {
    lazy->is_evaluated = 1;
    lazy->data.char_value = value;
}

// Utility function for conditional evaluation of lazy type
void fscl_lazy_conditional_eval(clazy *lazy, int condition) {
    if (condition) {
        fscl_lazy_force(lazy);
    }
}

// Utility function to map a function over a lazy integer
void fscl_lazy_map_int(clazy *lazy, int (*mapFunction)(int)) {
    fscl_lazy_force(lazy);
    lazy->data.int_value = mapFunction(lazy->data.int_value);
}

// Utility function to map a function over a lazy bool
void fscl_lazy_map_bool(clazy *lazy, bool (*mapFunction)(bool)) {
    fscl_lazy_force(lazy);
    lazy->data.bool_value = mapFunction(lazy->data.bool_value);
}

// Utility function to map a function over a lazy char
void fscl_lazy_map_char(clazy *lazy, char (*mapFunction)(char)) {
    fscl_lazy_force(lazy);
    lazy->data.char_value = mapFunction(lazy->data.char_value);
}

// Utility function to map a function over a lazy string
void fscl_lazy_map_cstring(clazy *lazy, const char* (*mapFunction)(const char*)) {
    fscl_lazy_force(lazy);
    const char* result = mapFunction(lazy->data.string_value.data);
    size_t len = strlen(result);
    lazy->data.string_value.data = realloc(lazy->data.string_value.data, len + 1);
    strcpy(lazy->data.string_value.data, result);
}

// Utility function for string concatenation of two lazy strings
void fscl_lazy_concat_cstrings(clazy *result, clazy *str1, clazy *str2) {
    fscl_lazy_force(str1);
    fscl_lazy_force(str2);

    size_t len1 = strlen(str1->cache.memoized_string.data);
    size_t len2 = strlen(str2->cache.memoized_string.data);

    result->data.string_value.data = malloc(len1 + len2 + 1);
    strcpy(result->data.string_value.data, str1->cache.memoized_string.data);
    strcat(result->data.string_value.data, str2->cache.memoized_string.data);

    result->is_evaluated = 1;
    result->type = CLAZY_STRING;
}

// Utility function to print the value of a lazy type
void fscl_lazy_print(clazy *lazy) {
    fscl_lazy_force(lazy);
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