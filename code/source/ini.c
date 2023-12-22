/*  ----------------------------------------------------------------------------
    File: ini.c

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
#include "trilobite/xcore/ini.h"
#include <stdlib.h>
#include <string.h>

// Function to create a new cini structure
void  tscl_ini_parser_create(cini** data) {
    *data = (cini*)malloc(sizeof(cini));
    (*data)->entries = NULL;
    (*data)->size = 0;
}

// Function to erase a cini structure
void  tscl_ini_parser_erase(cini** data) {
    if (*data != NULL) {
        free((*data)->entries);
        free(*data);
        *data = NULL;
    }
}

// Function to parse an INI file and populate cini structure
void  tscl_ini_parser_parse(FILE* file, cini** data) {
     tscl_ini_parser_erase(data); // Clear existing data

    *data = (cini*)malloc(sizeof(cini));

    // Initialize entries array
    (*data)->entries = NULL;
    (*data)->size = 0;

    char line[TRILO_INI_FILE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Skip comments and empty lines
        if (line[0] == ';' || line[0] == '#' || line[0] == '\n' || line[0] == '\r') {
            continue;
        }

        // Parse key-value pairs
        cini_entry entry;
        if (sscanf(line, "%[^=]=%[^\n]", entry.key, entry.value) == 2) {
            (*data)->entries = (cini_entry*)realloc((*data)->entries,
                ((*data)->size + 1) * sizeof(cini_entry));

            // Copy the entry to the array
            strcpy((*data)->entries[(*data)->size].key, entry.key);
            strcpy((*data)->entries[(*data)->size].value, entry.value);

            (*data)->size++;
        }
    }
}

// Function to update or add an entry in cini structure
void  tscl_ini_parser_setter(cini** data, const char* update) {
    char key[TRILO_INI_FILE_LENGTH];
    char value[TRILO_INI_FILE_LENGTH];

    if (sscanf(update, "%[^=]=%[^\n]", key, value) == 2) {
        // Search for existing key and update its value
        for (size_t i = 0; i < (*data)->size; ++i) {
            if (strcmp((*data)->entries[i].key, key) == 0) {
                strcpy((*data)->entries[i].value, value);
                return;
            }
        }

        // Key not found, add a new entry
        (*data)->entries = (cini_entry*)realloc((*data)->entries,
            ((*data)->size + 1) * sizeof(cini_entry));

        strcpy((*data)->entries[(*data)->size].key, key);
        strcpy((*data)->entries[(*data)->size].value, value);

        (*data)->size++;
    }
}

// Function to get the cini structure
cini*  tscl_ini_parser_getter(cini** data) {
    return *data;
} // end of func // end of func
