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
#ifndef TSCL_INI_H
#define TSCL_INI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>

enum {TRILO_INI_FILE_LENGTH = 1555};

// Structure to store INI data
typedef struct {
    char key[TRILO_INI_FILE_LENGTH];
    char value[TRILO_INI_FILE_LENGTH];
} cini_entry;

typedef struct {
    cini_entry* entries;
    size_t size;
} cini;

/**
 * @brief Creates a new cini structure.
 *
 * @param data Pointer to the cini structure pointer.
 */
void ini_parser_create(cini** data);

/**
 * @brief Erases a cini structure, freeing allocated memory.
 *
 * @param data Pointer to the cini structure pointer.
 */
void ini_parser_erase(cini** data);

/**
 * @brief Parses an INI file and populates a cini structure.
 *
 * @param file File pointer to the opened INI file.
 * @param data Pointer to the cini structure pointer.
 */
void ini_parser_parse(FILE* file, cini** data);

/**
 * @brief Updates or adds an entry in a cini structure.
 *
 * @param data Pointer to the cini structure pointer.
 * @param update String containing the update in the format "key=value".
 */
void ini_parser_setter(cini** data, const char* update);

/**
 * @brief Gets the cini structure.
 *
 * @param data Pointer to the cini structure pointer.
 * @return Pointer to the cini structure.
 */
cini* ini_parser_getter(cini** data);

#ifdef __cplusplus
}
#endif

#endif
