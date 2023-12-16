/*  ----------------------------------------------------------------------------
    File: demo_fossil.c

    Description:
    This demo file serves as a showcase of the Trilobite Stdlib in action. It provides
    example code snippets and usage scenarios to help users understand how to leverage
    the library's features and functions in their own projects.

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
#include <trilobite/xcore/fossil.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file.fossil>\n", argv[0]);
        return 1;
    }

    // Check if the input file has the correct extension
    const char *file_extension = strrchr(argv[1], '.');
    if (file_extension == NULL) {
        fprintf(stderr, "Error: The input file must have a valid extension\n");
        return 1;
    }

    FossilDSL dsl;
    fossil_dsl_create(&dsl, "output.tape");

    if (dsl.error_code != 0) {
        fprintf(stderr, "Error: %s\n", dsl.error_message);
        return dsl.error_code;
    }

    // Define the main function as the entry point
    fossil_dsl_add_function(&dsl, "main");

    // Read the DSL script from the provided file
    FILE *script_file = fopen(argv[1], "r");
    if (script_file == NULL) {
        fprintf(stderr, "Error: Unable to open the input file\n");
        return 1;
    }

    // Read the script line by line and add DSL operations
    char line[256];
    while (fgets(line, sizeof(line), script_file) != NULL) {
        // Assuming each line represents a DSL operation
        // Modify this logic based on your actual DSL syntax
        fossil_dsl_print_value(dsl.tape_file, (FossilDSLValue) {.type = STRING, .string_value = line});
        fprintf(dsl.tape_file, "\n");
    }

    fclose(script_file);

    fossil_dsl_close_block(&dsl);  // Close main function block
    fossil_dsl_erase(&dsl);

    return 0;
} // end of func
