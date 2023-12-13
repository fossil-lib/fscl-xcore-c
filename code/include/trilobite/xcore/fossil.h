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

// Define token types
typedef enum {
    FSL_KEYWORD,
    FSL_NAME,
    FSL_COLON,
    FSL_TYPE,
    FSL_ARROW,
    FSL_UNIT,
    FSL_COMMENT,
    FSL_END
} TokenType;

// Define a token structure
typedef struct {
    TokenType type;
    char* value;
} Token;

// Define a structure to represent a function parameter
typedef struct {
    char* name;
    char* type;
} Parameter;

// Define a structure to represent a function
typedef struct {
    char* name;
    Parameter* parameters;
    size_t param_count;
    char* return_type;
} Function;

// Define a structure to represent a function call
typedef struct {
    char* function_name;
    char* return_type;
} FunctionCall;

// Define a structure to represent a library
typedef struct {
    char* name;
    char** functions;
    size_t function_count;
} Library;

/**
 * @brief Parses a DSL input file and processes the functions.
 *
 * @param input The content of the DSL file to be parsed.
 */
void fossil_dsl_parse(char* input);

/**
 * @brief Tokenizes the input string and generates an array of tokens.
 *
 * @param input The input string to be tokenized.
 * @param tokens Pointer to the array of tokens (output parameter).
 * @param token_count Pointer to the variable storing the token count (output parameter).
 */
void fossil_dsl_tokenize(char* input, Token** tokens, size_t* token_count);

/**
 * @brief Frees the memory allocated for an array of tokens.
 *
 * @param tokens The array of tokens to be erased.
 * @param token_count The number of tokens in the array.
 */
void fossil_dsl_erase_tokens(Token* tokens, size_t token_count);

/**
 * @brief Frees the memory allocated for a parsed function.
 *
 * @param func The function to be erased.
 */
void fossil_dsl_erase_function(Function* func);

/**
 * @brief Frees the memory allocated for an array of function calls.
 *
 * @param calls The array of function calls to be erased.
 * @param call_count The number of function calls in the array.
 */
void fossil_dsl_erase_function_calls(FunctionCall* calls, size_t call_count);

/**
 * @brief Prints information about a parsed function.
 *
 * @param func The function to be printed.
 */
void fossil_dsl_print_function(Function* func);

/**
 * @brief Loads a custom library and adds function calls to the list.
 *
 * @param library_name The name of the custom library to load.
 * @param calls Pointer to the array of function calls (output parameter).
 * @param call_count Pointer to the variable storing the number of function calls (output parameter).
 */
void fossil_dsl_load_library(const char* library_name, FunctionCall** calls, size_t* call_count);

/**
 * @brief Gets the parsed function after calling fossil_dsl_parse.
 *
 * @return A copy of the parsed function. The caller is responsible for freeing the memory.
 */
Function fossil_dsl_get_parsed_function(void);

/**
 * @brief Resets the internal state of the DSL parser.
 *
 * This function should be called before parsing a new file.
 */
void fossil_dsl_reset(void);


#ifdef __cplusplus
}
#endif

#endif
