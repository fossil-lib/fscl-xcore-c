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
#ifndef TSCL_CSV_H
#define TSCL_CSV_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>

// Structure to hold CSV data
typedef struct {
    char*** rows;
    size_t num_rows;
    size_t num_columns;
} ccsv;

/**
 * @brief Creates a ccsv structure.
 *
 * @return A pointer to the newly created ccsv structure.
 */
ccsv*  tscl_csv_parser_create();

/**
 * @brief Erases a ccsv structure.
 *
 * @param data A double pointer to the ccsv structure to be erased.
 */
void  tscl_csv_parser_erase(ccsv** data);

/**
 * @brief Parses a CSV file and populates a ccsv structure.
 *
 * @param file A pointer to the FILE structure representing the CSV file.
 * @param data A double pointer to the ccsv structure to be populated.
 */
void  tscl_csv_parser_parse(FILE* file, ccsv** data);

/**
 * @brief Updates a specific cell in the ccsv structure.
 *
 * @param data A double pointer to the ccsv structure.
 * @param row The row index of the cell to be updated.
 * @param col The column index of the cell to be updated.
 * @param update The new content to be set in the specified cell.
 */
void  tscl_csv_parser_setter(ccsv** data, size_t row, size_t col, const char* update);

/**
 * @brief Retrieves the content of a specific cell in the ccsv structure.
 *
 * @param data A pointer to the ccsv structure.
 * @param row The row index of the cell to be retrieved.
 * @param col The column index of the cell to be retrieved.
 * @return The content of the specified cell.
 */
const char*  tscl_csv_parser_getter(const ccsv* data, size_t row, size_t col);

#ifdef __cplusplus
}
#endif

#endif
