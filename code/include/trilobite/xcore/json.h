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
#ifndef TSCL_JSON_H
#define TSCL_JSON_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* json_data;
} cjson;

typedef struct {
    char key[256];
    char value[256];
} cjson_pair;

typedef struct {
    cjson_pair* pairs;
    size_t numPairs;
} cjson_object;

typedef struct {
    char** items;
    size_t numItems;
} cjson_array;

/**
 * @brief Creates a new cjson object.
 *
 * @return A pointer to the newly created cjson object, or NULL on failure.
 */
cjson* json_parser_create();

/**
 * @brief Erases a cjson object and deallocates its memory.
 *
 * @param data A pointer to a pointer to the cjson object to be erased.
 */
void json_parser_erase(cjson** data);

/**
 * @brief Parses JSON data from a file and populates a cjson object.
 *
 * @param file A pointer to the FILE structure representing the JSON file.
 * @param data A pointer to a pointer to the cjson object to be populated.
 *
 * @return 1 if parsing is successful, 0 otherwise.
 */
int json_parser_parse(FILE* file, cjson** data);

/**
 * @brief Updates the JSON data in a cjson object.
 *
 * @param data A pointer to a pointer to the cjson object to be updated.
 * @param update The new JSON data string to set in the cjson object.
 */
void json_parser_setter(cjson** data, const char* update);

/**
 * @brief Retrieves the JSON data from a cjson object.
 *
 * @param data A pointer to a pointer to the cjson object.
 *
 * @return A pointer to the JSON data string, or NULL if the cjson object is not valid.
 */
const char* json_parser_getter(cjson** data);

/**
 * @brief Frees the JSON data within a cjson object.
 *
 * @param data A pointer to a pointer to the cjson object.
 */
void json_parser_erase_meta(cjson** data);

/**
 * @brief Retrieves the cjson_object structure from a cjson object.
 *
 * @param data A pointer to a pointer to the cjson object.
 *
 * @return A pointer to the cjson_object structure, or NULL if the cjson object is not valid.
 */
cjson_object* json_parser_get_object(cjson** data);

/**
 * @brief Retrieves the cjson_array structure from a cjson object.
 *
 * @param data A pointer to a pointer to the cjson object.
 *
 * @return A pointer to the cjson_array structure, or NULL if the cjson object is not valid.
 */
cjson_array* json_parser_get_array(cjson** data);

#ifdef __cplusplus
}
#endif

#endif
