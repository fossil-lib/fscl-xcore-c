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
#ifndef FSCL_FOSSIL_H
#define FSCL_FOSSIL_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum {
    DSL_ARRAY_SIZE   = 100,
    DSL_COMEDY_ERROR = 555
};

typedef enum {
    INTEGER,
    UNSIGNED_INT,
    FLOAT,
    CHAR,
    STRING,
    TOFU, // New generic type
    ARRAY,
    BOOL,  // New BOOL type
    NULL_TYPE
} FossilDSLType;

typedef union {
    int int_value;
    unsigned int unsigned_int_value;
    float float_value;
    char char_value;
    char *string_value;
    void *null_type;
    void *tofu_value; // Generic type
    int array[DSL_ARRAY_SIZE]; // New array type
    int bool_value;  // New BOOL type
    FossilDSLType type;  // New type member
} FossilDSLValue;

typedef struct {
    FILE *tape_file;
    int error_code;
    char error_message[DSL_COMEDY_ERROR];
    int indentation_level;
    int debug_enabled; // Added flag to enable/disable debugging
} FossilDSL;

// =================================================================
// Create and erase
// =================================================================
void  fscl_fossil_dsl_create(FossilDSL *dsl, const char *tape_filename);
void  fscl_fossil_dsl_erase(FossilDSL *dsl);

// =================================================================
// DSL functions
// =================================================================
void  fscl_fossil_dsl_indent(FossilDSL *dsl);
void  fscl_fossil_dsl_call_function(FossilDSL *dsl, const char *func_name, FossilDSLValue *arguments, int num_arguments);
void  fscl_fossil_dsl_add_function(FossilDSL *dsl, const char *func_name);
void  fscl_fossil_dsl_print_value(FILE *tape_file, FossilDSLValue value);
void  fscl_fossil_dsl_add_binary_operation(FossilDSL *dsl, const char *operation, const char *type, FossilDSLValue operand1, FossilDSLValue operand2);
void  fscl_fossil_dsl_add_bitwise_operation(FossilDSL *dsl, const char *operation, FossilDSLValue operand1, FossilDSLValue operand2);
void  fscl_fossil_dsl_add_loop(FossilDSL *dsl, const char *loop_variable, int start_value, int end_value);
void  fscl_fossil_dsl_add_condition(FossilDSL *dsl, FossilDSLValue condition, const char *true_branch, const char *false_branch);
void  fscl_fossil_dsl_close_block(FossilDSL *dsl);

// =================================================================
// DSL utilites
// =================================================================
void  fscl_fossil_dsl_debug(FossilDSL *dsl, const char *message);
void  fscl_fossil_dsl_enable_debug(FossilDSL *dsl);

#ifdef __cplusplus
}
#endif

#endif
