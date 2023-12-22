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
#include <trilobite/xcore/console.h>
#include <stdio.h>
#include <stdbool.h>

int main() {
    // Output Functions Demo
    tscl_console_out("This is a %s message.\n", "normal");
    tscl_console_err("This is an %s message.\n", "error");

    // Color Output Demo
    tscl_console_out_color("green", "This is a %s message in green.\n", "colored");

    // Clear and Flush Demo
    tscl_console_clear();
    tscl_console_out("This text appears after clearing the screen.\n");
    tscl_console_flush();

    // Progress Demo
    tscl_console_progress(10, 100); // Simulates a progress bar with 10 iterations and a 100ms delay between iterations

    // Pause Demo
    tscl_console_pause();

    // Input Functions Demo
    char* input_line = tscl_console_in_read_line("Enter a line of text: ");
    tscl_console_out("You entered: %s\n", input_line);
    free(input_line);

    char* password = tscl_console_in_read_password("Enter your password: ");
    tscl_console_out("You entered a password: %s\n", password);
    free(password);

    bool confirmation = tscl_console_in_confirm_yes_no("Do you want to proceed?");
    tscl_console_out("Confirmation: %s\n", confirmation ? "Yes" : "No");

    const char* menu[] = {"Option 1", "Option 2", "Option 3"};
    int choice = tscl_console_in_confirm_menu("Select an option:", menu, 3);
    tscl_console_out("You chose option %d: %s\n", choice + 1, menu[choice]);

    bool selections[3] = {false, false, false};
    tscl_console_in_confirm_multi_menu("Select multiple options:", menu, selections, 3);
    tscl_console_out("Selected options: ");
    for (int i = 0; i < 3; ++i) {
        if (selections[i]) {
            tscl_console_out("%s ", menu[i]);
        }
    }
    tscl_console_out("\n");

    bool exit_confirmed = tscl_console_in_confirm_exit();
    tscl_console_out("Exit confirmed: %s\n", exit_confirmed ? "Yes" : "No");

    int year, month, day;
    bool date_read = tscl_console_in_read_date("Enter a date (YYYY-MM-DD): ", &year, &month, &day);
    if (date_read) {
        tscl_console_out("Date entered: %04d-%02d-%02d\n", year, month, day);
    } else {
        tscl_console_err("Invalid date format.\n");
    }

    int hour, minute, second;
    bool time_read = tscl_console_in_read_time("Enter a time (HH:MM:SS): ", &hour, &minute, &second);
    if (time_read) {
        tscl_console_out("Time entered: %02d:%02d:%02d\n", hour, minute, second);
    } else {
        tscl_console_err("Invalid time format.\n");
    }

    return 0;
} // end of func
