/*  ----------------------------------------------------------------------------
    File: demo_errors.c

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
#include <trilobite/xcore/csv.h>
#include <stdio.h>

// Function to print the eco-friendly products
void print_eco_products(const ccsv* data) {
    // Print header
    for (size_t j = 0; j < data->num_columns; ++j) {
        printf("%s",  tscl_csv_parser_getter(data, 0, j));

        if (j < data->num_columns - 1) {
            printf(",");
        }
    }
    printf("\n");

    // Print product details
    for (size_t i = 1; i < data->num_rows; ++i) {
        for (size_t j = 0; j < data->num_columns; ++j) {
            printf("%s",  tscl_csv_parser_getter(data, i, j));

            if (j < data->num_columns - 1) {
                printf(",");
            }
        }
        printf("\n");
    }
} // end of func

int main() {
    FILE* csv_file = fopen("eco_products.csv", "r");
    if (csv_file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    ccsv* eco_products_data = NULL;

     tscl_csv_parser_parse(csv_file, &eco_products_data);

    // Display the initial list of eco-friendly products
    printf("Initial list of eco-friendly products:\n");
    print_eco_products(eco_products_data);

    // Example: Update the stock of the "Reusable Water Bottle"
     tscl_csv_parser_setter(&eco_products_data, 1, 3, "90");

    // Display the updated list of eco-friendly products
    printf("\nUpdated list of eco-friendly products:\n");
    print_eco_products(eco_products_data);

    // Cleanup
     tscl_csv_parser_erase(&eco_products_data);
    fclose(csv_file);

    return EXIT_SUCCESS;
} // end of func
