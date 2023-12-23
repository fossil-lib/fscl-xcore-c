/*
   This C header file is part of the Trilobite Stdlib, a collection of utility functions and
   standard data structures for enhancing software development projects. Feel free to use
   and modify these utilities to streamline your software development process.

   Project: Trilobite Stdlib
   Author: Michael Gene Brockus (Dreamer)
   Email: michaelbrockus@gmail.com
   Website: [Trilobite Coder Blog](https://trilobite.home.blog)

   Trilobite Stdlib is designed to provide a robust set of functionalities that can be
   incorporated into various projects. The utilities included in this library aim to optimize
   and standardize common operations, ensuring efficient and reliable code.

   This header file is a part of a broader initiative to support developers in creating secure,
   efficient, and scalable software. Contributions, suggestions, and feedback are welcomed,
   as we strive to continuously improve and expand the capabilities of Trilobite Stdlib.

   License: Apache License 2.0
   SPDX Identifier: Apache-2.0

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software distributed under the License
   is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
   or implied. See the License for the specific language governing permissions and limitations
   under the License.

   The above copyright notice and this permission notice shall be included in all copies or
   substantial portions of the Software.

   Please review the full text of the Apache License 2.0 for the complete terms and conditions.

   (Apache License 2.0: http://www.apache.org/licenses/LICENSE-2.0)
*/
#ifndef TSCL_FOSSIL_H
#define TSCL_FOSSIL_H

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
void  tscl_fossil_dsl_create(FossilDSL *dsl, const char *tape_filename);
void  tscl_fossil_dsl_erase(FossilDSL *dsl);

// =================================================================
// DSL functions
// =================================================================
void  tscl_fossil_dsl_indent(FossilDSL *dsl);
void  tscl_fossil_dsl_call_function(FossilDSL *dsl, const char *func_name, FossilDSLValue *arguments, int num_arguments);
void  tscl_fossil_dsl_add_function(FossilDSL *dsl, const char *func_name);
void  tscl_fossil_dsl_print_value(FILE *tape_file, FossilDSLValue value);
void  tscl_fossil_dsl_add_binary_operation(FossilDSL *dsl, const char *operation, const char *type, FossilDSLValue operand1, FossilDSLValue operand2);
void  tscl_fossil_dsl_add_bitwise_operation(FossilDSL *dsl, const char *operation, FossilDSLValue operand1, FossilDSLValue operand2);
void  tscl_fossil_dsl_add_loop(FossilDSL *dsl, const char *loop_variable, int start_value, int end_value);
void  tscl_fossil_dsl_add_condition(FossilDSL *dsl, FossilDSLValue condition, const char *true_branch, const char *false_branch);
void  tscl_fossil_dsl_close_block(FossilDSL *dsl);

// =================================================================
// DSL utilites
// =================================================================
void  tscl_fossil_dsl_debug(FossilDSL *dsl, const char *message);
void  tscl_fossil_dsl_enable_debug(FossilDSL *dsl);

#ifdef __cplusplus
}
#endif

#endif
