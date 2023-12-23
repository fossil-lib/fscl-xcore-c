/*  ----------------------------------------------------------------------------
    File: demo_reader.c

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
#include <trilobite/xcore/contract.h>
#include <stdio.h>

// Example pre-condition function
bool example_pre_condition() {
    // Add your pre-condition logic here
    return true;  // Replace with your actual condition
}

// Example post-condition function
void example_post_condition() {
    // Add your post-condition logic here
}

// Function with contracts
void example_function(int *array, size_t array_length, const char *str, void *ptr) {
    // Create contracts
    ccontract *pre_condition_contract = tscl_contract_create(example_pre_condition, NULL);
    ccontract *post_condition_contract = tscl_contract_create(NULL, example_post_condition);

    // Pre-condition checks
    tscl_contract_require_not_null(array, "array");
    tscl_contract_require_array_length(array, array_length, sizeof(int), "array");
    tscl_contract_require_not_null(str, "str");
    tscl_contract_require_string_length(str, 1, 10, "str");
    tscl_contract_require_not_null(ptr, "ptr");

    // Post-condition checks
    tscl_contract_check_pre(pre_condition_contract);

    // Your function logic here

    tscl_contract_check_post(post_condition_contract);

    // Clean up
    free(pre_condition_contract);
    free(post_condition_contract);
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    const char *str = "Hello";
    void *ptr = malloc(sizeof(int));

    // Call the function with valid parameters
    example_function(array, 5, str, ptr);

    // Call the function with invalid parameters to demonstrate a violation
    example_function(NULL, 10, "TooLongString", NULL);

    // Cleanup
    free(ptr);

    return 0;
} // end of func
