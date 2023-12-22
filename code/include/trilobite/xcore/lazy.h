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
#ifndef TSCL_LAZY_H
#define TSCL_LAZY_H

#ifdef __cplusplus
extern "C"
{
#endif

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
clazy tscl_lazy_create(clazy_type type);
void tscl_lazy_destroy(clazy *lazy);

// =================================================================
// Jedi Dreamer force functions
// =================================================================
void tscl_lazy_force(clazy *lazy);
int tscl_lazy_force_int(clazy *lazy);
bool tscl_lazy_force_bool(clazy *lazy);
char tscl_lazy_force_char(clazy *lazy);
const char* tscl_lazy_force_string(clazy *lazy);

// =================================================================
// addintal functions
// =================================================================
clazy tscl_lazy_sequence();
int tscl_lazy_sequence_force(clazy *lazy, int n);

#ifdef __cplusplus
}
#endif

#endif
