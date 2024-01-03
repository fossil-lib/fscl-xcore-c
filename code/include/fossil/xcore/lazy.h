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
#ifndef FSCL_LAZY_H
#define FSCL_LAZY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>

// Define a simple string type
typedef struct {
    char *data;
} clazy_string;

// Enum to represent different data types
typedef enum {
    CLAZY_INT,
    CLAZY_BOOL,
    CLAZY_CHAR,
    CLAZY_STRING,
    CLAZY_NULL
} clazy_type;

typedef struct {
    int is_evaluated;
    clazy_type type;
    union {
        int int_value;
        bool bool_value;
        char char_value;
        clazy_string string_value;
    } data;

    // Memoization cache
    union {
        int memoized_int;
        bool memoized_bool;
        char memoized_char;
        clazy_string memoized_string;
    } cache;
} clazy;

// =================================================================
// create and erase
// =================================================================
clazy fscl_lazy_create(clazy_type type);
void fscl_lazy_erase(clazy *lazy);

// =================================================================
// Jedi Dreamer force functions
// =================================================================
void fscl_lazy_force(clazy *lazy);
int fscl_lazy_force_int(clazy *lazy);
bool fscl_lazy_force_bool(clazy *lazy);
char fscl_lazy_force_char(clazy *lazy);
const char* fscl_lazy_force_string(clazy *lazy);

// =================================================================
// addintal functions
// =================================================================
clazy fscl_lazy_sequence(void);
int fscl_lazy_sequence_force(clazy *lazy, int n);
void fscl_lazy_set_int(clazy *lazy, int value);
void fscl_lazy_set_cstring(clazy *lazy, const char *value);
void fscl_lazy_set_bool(clazy *lazy, bool value);
void fscl_lazy_set_letter(clazy *lazy, char value);
void fscl_lazy_conditional_eval(clazy *lazy, int condition);
void fscl_lazy_map_int(clazy *lazy, int (*mapFunction)(int));
void fscl_lazy_map_bool(clazy *lazy, bool (*mapFunction)(bool));
void fscl_lazy_map_char(clazy *lazy, char (*mapFunction)(char));
void fscl_lazy_map_cstring(clazy *lazy, const char* (*mapFunction)(const char*));
void fscl_lazy_concat_cstrings(clazy *result, clazy *str1, clazy *str2);
void fscl_lazy_print(clazy *lazy);

#ifdef __cplusplus
}
#endif

#endif
