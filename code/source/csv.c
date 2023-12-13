/*  ----------------------------------------------------------------------------
    File: csv.c

    Description:
    This source file contains the code entry point for the Trilobite Stdlib project.
    It demonstrates the usage of various utilities and functions provided by the
    Trilobite Stdlib to enhance software development.

    Author: Michael Gene Brockus (Dreamer)
    Email: michaelbrockus@gmail.com
    Website: [Trilobite Coder Blog](https://trilobite.home.blog)

    Project: Trilobite Stdlib

    License: Apache License 2.0
    SPDX Identifier: Apache-2.0

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0.

    Unless required by applicable law or agreed to in writing, software distributed under the License
    is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
    or implied. See the License for the specific language governing permissions and limitations
    under the License.

    Please review the full text of the Apache License 2.0 for the complete terms and conditions.

    (Apache License 2.0: http://www.apache.org/licenses/LICENSE-2.0)
    ----------------------------------------------------------------------------
*/
#include "trilobite/xcore/csv.h"
#include <stdio.h>
#include <string.h>

// Function to create a ccsv structure
ccsv* csv_parser_create() {
    ccsv* csv = (ccsv*)malloc(sizeof(ccsv));
    if (csv == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    csv->rows = NULL;
    csv->num_rows = 0;
    csv->num_columns = 0;

    return csv;
} // end of func

// Function to erase a ccsv structure
void csv_parser_erase(ccsv** data) {
    if (data != NULL && *data != NULL) {
        // Free memory for each row
        for (size_t i = 0; i < (*data)->num_rows; ++i) {
            for (size_t j = 0; j < (*data)->num_columns; ++j) {
                free((*data)->rows[i][j]);
            }
            free((*data)->rows[i]);
        }

        // Free memory for rows array
        free((*data)->rows);

        // Free memory for ccsv structure
        free(*data);

        // Set data pointer to NULL
        *data = NULL;
    }
} // end of func

// Function to parse CSV file and populate ccsv structure
void csv_parser_parse(FILE* file, ccsv** data) {
    char buffer[1024];  // Adjust buffer size as needed

    // Count the number of rows and columns in the CSV file
    size_t num_rows = 0;
    size_t num_columns = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char* token = strtok(buffer, ",");
        size_t current_columns = 0;

        while (token != NULL) {
            token = strtok(NULL, ",");
            current_columns++;
        }

        // Update the number of columns if it is greater than the current count
        if (current_columns > num_columns) {
            num_columns = current_columns;
        }

        num_rows++;
    }

    // Reset file position to the beginning
    fseek(file, 0, SEEK_SET);

    // Allocate memory for ccsv structure
    *data = csv_parser_create();

    // Allocate memory for rows array
    (*data)->rows = (char***)malloc(num_rows * sizeof(char**));
    if ((*data)->rows == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < num_rows; ++i) {
        (*data)->rows[i] = (char**)malloc(num_columns * sizeof(char*));
        if ((*data)->rows[i] == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        // Initialize each element to NULL
        for (size_t j = 0; j < num_columns; ++j) {
            (*data)->rows[i][j] = NULL;
        }
    }

    // Populate the ccsv structure with data from the CSV file
    size_t row_index = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char* token = strtok(buffer, ",");
        size_t col_index = 0;

        while (token != NULL) {
            size_t len = strlen(token);
            // Remove newline character if present
            if (len > 0 && token[len - 1] == '\n') {
                token[len - 1] = '\0';
            }

            // Allocate memory for the token
            (*data)->rows[row_index][col_index] = (char*)malloc((len + 1) * sizeof(char));
            if ((*data)->rows[row_index][col_index] == NULL) {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }

            // Copy the token to the ccsv structure
            strcpy((*data)->rows[row_index][col_index], token);

            token = strtok(NULL, ",");
            col_index++;
        }

        row_index++;
    }

    (*data)->num_rows = num_rows;
    (*data)->num_columns = num_columns;
} // end of func

// Function to update a specific cell in the ccsv structure
void csv_parser_setter(ccsv** data, size_t row, size_t col, const char* update) {
    // Check if the provided indices are valid
    if (row < (*data)->num_rows && col < (*data)->num_columns) {
        // Free the existing content of the cell
        free((*data)->rows[row][col]);

        // Allocate memory for the updated content
        size_t len = strlen(update);
        (*data)->rows[row][col] = (char*)malloc((len + 1) * sizeof(char));
        if ((*data)->rows[row][col] == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        // Copy the updated content to the cell
        strcpy((*data)->rows[row][col], update);
    } else {
        fprintf(stderr, "Invalid row or column index\n");
    }
} // end of func

// Function to retrieve the content of a specific cell in the ccsv structure
const char* csv_parser_getter(const ccsv* data, size_t row, size_t col) {
    // Check if the provided indices are valid
    if (row < data->num_rows && col < data->num_columns) {
        return data->rows[row][col];
    } else {
        fprintf(stderr, "Invalid row or column index\n");
        return NULL;
    }
} // end of func
