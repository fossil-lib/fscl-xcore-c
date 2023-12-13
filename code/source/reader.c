/*  ----------------------------------------------------------------------------
    File: reader.c

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
#include "trilobite/xcore/reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

// Function to get a line of text from the user.
char* reader_get_line() {
    static char buffer[MAX_INPUT_LENGTH];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove the trailing newline
        return buffer;
    }
    return NULL;
} // end of func

// Function to read a line of text from the user.
char* reader_read_line(const char* prompt) {
    printf("%s: ", prompt);
    return reader_get_line();
} // end of func

// Function to validate user input with a specific condition.
bool reader_valid_input(const char* prompt, bool (*validator)(const char*)) {
    while (true) {
        char* input = reader_read_line(prompt);
        if (input && validator(input)) {
            return true;
        }
        printf("Invalid input. Please try again.\n");
    }
} // end of func

// Function to confirm a yes/no question.
bool reader_confirm_yes_no(const char* question) {
    while (true) {
        char* response = reader_read_line(question);
        if (response) {
            if (strncmp(response, "yes", strlen("yes")) == 0 || strncmp(response, "y", strlen("y")) == 0) {
                return true;
            } else if (strncmp(response, "no", strlen("no")) == 0 || strncmp(response, "n", strlen("n")) == 0) {
                return false;
            }
            printf("Please answer with 'yes' or 'no'.\n");
        }
    }
} // end of func

// Function to confirm a selection from a menu.
int reader_confirm_menu(const char* question, const char** menu, int num_options) {
    printf("%s:\n", question);
    for (int i = 0; i < num_options; i++) {
        printf("%d. %s\n", i + 1, menu[i]);
    }

    int choice;
    while (true) {
        char* response = reader_read_line("Enter your choice");
        if (response && sscanf(response, "%d", &choice) == 1 && choice >= 1 && choice <= num_options) {
            return choice - 1;
        }
        printf("Invalid choice. Please enter a valid option.\n");
    }
} // end of func

// Function to confirm multiple selections from a menu.
void reader_confirm_multi_menu(const char* question, const char** menu, bool* selections, int num_options) {
    printf("%s (Choose options by entering their numbers, separated by spaces):\n", question);
    for (int i = 0; i < num_options; i++) {
        printf("%d. %s\n", i + 1, menu[i]);
    }

    char* response = reader_read_line("Enter your choices (e.g., '1 3 5')");

    if (response) {
        int choice;
        const char* token = strtok(response, " ");
        while (token != NULL) {
            if (sscanf(token, "%d", &choice) == 1 && choice >= 1 && choice <= num_options) {
                selections[choice - 1] = true;
            }
            token = strtok(NULL, " ");
        }
    }
} // end of func

// Function to confirm an exit action.
bool reader_confirm_exit() {
    return reader_confirm_yes_no("Do you want to exit?");
} // end of func

bool reader_read_date(const char* prompt, int* year, int* month, int* day) {
    printf("%s", prompt);
    if (scanf("%d-%d-%d", year, month, day) == 3) {
        return true;
    } else {
        // Invalid input
        while (getchar() != '\n');  // Clear the input buffer
        return false;
    }
} // end of func

bool reader_read_time(const char* prompt, int* hour, int* minute, int* second) {
    printf("%s", prompt);
    if (scanf("%d:%d:%d", hour, minute, second) == 3) {
        return true;
    } else {
        // Invalid input
        while (getchar() != '\n');  // Clear the input buffer
        return false;
    }
} // end of func

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>

void reader_clear_screen(void) {
    system("cls");
}
#else
#include <stdio.h>

void reader_clear_screen(void) {
    printf("\033[2J\033[H");
}
#endif
