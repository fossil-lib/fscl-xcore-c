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
#include "trilobite/xcore/reader.h" // lib source code
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to validate an input as a positive integer
bool is_positive_integer(const char* input) {
    // Check if the input is a positive integer
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) {
            return false;
        }
    }
    return true;
} // end of func

int main() {
    // Demo of reading a line
    printf("Enter a line of text: ");
    char* line = reader_get_line();
    printf("You entered: %s\n", line);
    free(line);

    // Demo of reading a line with a custom prompt
    const char* custom_prompt = "Enter another line: ";
    line = reader_read_line(custom_prompt);
    printf("You entered: %s\n", line);
    free(line);

    // Demo of validating input using a custom validator function
    const char* prompt_for_number = "Enter a positive integer: ";
    bool is_valid_number = reader_valid_input(prompt_for_number, is_positive_integer);
    printf("Input is %svalid.\n", is_valid_number ? "" : "in");

    // Demo of yes/no confirmation
    const char* exit_question = "Do you want to exit?";
    bool wants_to_exit = reader_confirm_yes_no(exit_question);
    printf("User %s to exit.\n", wants_to_exit ? "wants" : "doesn't want");

    // Demo of a menu
    const char* menu[] = {"Option A", "Option B", "Option C"};
    int selected_option = reader_confirm_menu("Choose an option:", menu, 3);
    printf("Selected option: %s\n", menu[selected_option]);

    // Demo of a multi-menu
    bool selections[3] = {false};
    reader_confirm_multi_menu("Choose multiple options:", menu, selections, 3);
    printf("Selected options: ");
    for (int i = 0; i < 3; i++) {
        if (selections[i]) {
            printf("%s ", menu[i]);
        }
    }
    printf("\n");

    // Demo of confirming exit
    bool confirm_exit = reader_confirm_exit();
    printf("User %s to exit.\n", confirm_exit ? "confirms" : "cancels");

    return 0;
} // end of func
