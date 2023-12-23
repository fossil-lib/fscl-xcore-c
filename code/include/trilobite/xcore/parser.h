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
#ifndef TSCL_FILE_PARSER_H
#define TSCL_FILE_PARSER_H

#ifdef __cplusplus
extern "C"
{
#endif

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

// Structure to hold CSV data
typedef struct {
    char*** rows;
    size_t num_rows;
    size_t num_columns;
} ccsv;

// =================================================================
// create and erase
// =================================================================
cjson*  tscl_json_parser_create();
void  tscl_json_parser_erase(cjson** data);

// =================================================================
// avaliable functions
// =================================================================
int  tscl_json_parser_parse(FILE* file, cjson** data);
void  tscl_json_parser_setter(cjson** data, const char* update);
const char*  tscl_json_parser_getter(cjson** data);
void  tscl_json_parser_erase_meta(cjson** data);
cjson_object*  tscl_json_parser_get_object(cjson** data);
cjson_array*  tscl_json_parser_get_array(cjson** data);

// =================================================================
// create and erase
// =================================================================
void  tscl_ini_parser_create(cini** data);
void  tscl_ini_parser_erase(cini** data);

// =================================================================
// avaliable functions
// =================================================================
void  tscl_ini_parser_parse(FILE* file, cini** data);
void  tscl_ini_parser_setter(cini** data, const char* update);
cini*  tscl_ini_parser_getter(cini** data);

// =================================================================
// create and erase
// =================================================================
ccsv*  tscl_csv_parser_create();
void  tscl_csv_parser_erase(ccsv** data);

// =================================================================
// avaliable functions
// =================================================================
void  tscl_csv_parser_parse(FILE* file, ccsv** data);
void  tscl_csv_parser_setter(ccsv** data, size_t row, size_t col, const char* update);
const char*  tscl_csv_parser_getter(const ccsv* data, size_t row, size_t col);


#ifdef __cplusplus
}
#endif

#endif
