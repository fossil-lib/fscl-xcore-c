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
#include "trilobite/xcore/console.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

enum {
    MAX_INPUT_LENGTH = 1024
};

// General Output Function
void tscl_console_out(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

// Error Output Function
void tscl_console_err(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}

// Color Output Function
void tscl_console_out_color(const char *color_name, const char *format, ...) {
    va_list args;
    va_start(args, format);

    if (strcmp(color_name, "reset") == 0) {
        printf("\033[0m");
    } else if (strcmp(color_name, "black") == 0) {
        printf("\033[0;30m");
    } else if (strcmp(color_name, "dark_gray") == 0) {
        printf("\033[1;30m");
    } else if (strcmp(color_name, "light_gray") == 0) {
        printf("\033[2;37m");
    } else if (strcmp(color_name, "white") == 0) {
        printf("\033[1;37m");
    } else if (strcmp(color_name, "dark_red") == 0) {
        printf("\033[0;31m");
    } else if (strcmp(color_name, "light_red") == 0) {
        printf("\033[1;31m");
    } else if (strcmp(color_name, "dark_green") == 0) {
        printf("\033[0;32m");
    } else if (strcmp(color_name, "light_green") == 0) {
        printf("\033[1;32m");
    } else if (strcmp(color_name, "dark_yellow") == 0) {
        printf("\033[0;33m");
    } else if (strcmp(color_name, "light_yellow") == 0) {
        printf("\033[1;33m");
    } else if (strcmp(color_name, "dark_blue") == 0) {
        printf("\033[0;34m");
    } else if (strcmp(color_name, "light_blue") == 0) {
        printf("\033[1;34m");
    } else if (strcmp(color_name, "dark_magenta") == 0) {
        printf("\033[0;35m");
    } else if (strcmp(color_name, "light_magenta") == 0) {
        printf("\033[1;35m");
    } else if (strcmp(color_name, "dark_cyan") == 0) {
        printf("\033[0;36m");
    } else if (strcmp(color_name, "light_cyan") == 0) {
        printf("\033[1;36m");
    } else {
        // Default to classic output if an unsupported color is specified
        vprintf(format, args);
        va_end(args);
        return;
    }

    vprintf(format, args);
    printf("\033[0m"); // Reset color
    va_end(args);
}

// Clear Screen Function
void tscl_console_clear() {
#ifdef _WIN32
    int dummy = system("cls");
#else
    int dummy = system("clear");
#endif
    (void)dummy;  // Avoid unused variable warning
}

// Flush Output Function
void tscl_console_flush() {
    fflush(stdout);
}

// Console Progress Function
void tscl_console_progress(int iterations, int delay) {
    const char *animation[] = {"|", "/", "-", "\\"};
    int i;
    
    for (i = 0; i < iterations; ++i) {
        printf("\rProgress: %s", animation[i % 4]);
        fflush(stdout);

#ifdef _WIN32
        Sleep(delay);  // Sleep in milliseconds on Windows
#else
        sleep(delay * 1000);  // Sleep in microseconds on POSIX
#endif
    }

    printf("\rProgress: Done!\n");
}

// Console Pause Function
void tscl_console_pause() {
    printf("Press Enter to continue...");
    getchar();  // Wait for user input (Enter key)
}

// Function to get a line of text from the user.
char* tscl_console_in_get_line() {
    static char buffer[MAX_INPUT_LENGTH];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove the trailing newline
        return buffer;
    }
    return NULL;
} // end of func

// Function to read a line of text from the user.
char* tscl_console_in_read_line(const char* prompt) {
    printf("%s: ", prompt);
    return tscl_console_in_get_line();
} // end of func

// Function to validate user input with a specific condition.
bool tscl_console_in_valid_input(const char* prompt, bool (*validator)(const char*)) {
    while (true) {
        char* input = tscl_console_in_read_line(prompt);
        if (input && validator(input)) {
            return true;
        }
        printf("Invalid input. Please try again.\n");
    }
} // end of func

// Function to confirm a yes/no question.
bool tscl_console_in_confirm_yes_no(const char* question) {
    while (true) {
        char* response = tscl_console_in_read_line(question);
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
int tscl_console_in_confirm_menu(const char* question, const char** menu, int num_options) {
    printf("%s:\n", question);
    for (int i = 0; i < num_options; i++) {
        printf("%d. %s\n", i + 1, menu[i]);
    }

    int choice;
    while (true) {
        char* response = tscl_console_in_read_line("Enter your choice");
        if (response && sscanf(response, "%d", &choice) == 1 && choice >= 1 && choice <= num_options) {
            return choice - 1;
        }
        printf("Invalid choice. Please enter a valid option.\n");
    }
} // end of func

// Function to confirm multiple selections from a menu.
void tscl_console_in_confirm_multi_menu(const char* question, const char** menu, bool* selections, int num_options) {
    printf("%s (Choose options by entering their numbers, separated by spaces):\n", question);
    for (int i = 0; i < num_options; i++) {
        printf("%d. %s\n", i + 1, menu[i]);
    }

    char* response = tscl_console_in_read_line("Enter your choices (e.g., '1 3 5')");

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
bool tscl_console_in_confirm_exit() {
    return tscl_console_in_confirm_yes_no("Do you want to exit?");
} // end of func

bool tscl_console_in_read_date(const char* prompt, int* year, int* month, int* day) {
    printf("%s", prompt);
    if (scanf("%d-%d-%d", year, month, day) == 3) {
        return true;
    } else {
        // Invalid input
        while (getchar() != '\n');  // Clear the input buffer
        return false;
    }
} // end of func

bool tscl_console_in_read_time(const char* prompt, int* hour, int* minute, int* second) {
    printf("%s", prompt);
    if (scanf("%d:%d:%d", hour, minute, second) == 3) {
        return true;
    } else {
        // Invalid input
        while (getchar() != '\n');  // Clear the input buffer
        return false;
    }
} // end of func

void disable_echo() {
#ifdef _WIN32
    system("cls");  // Clear the screen to hide the password
#else
    printf("\033[2J\033[1;1H");  // ANSI escape code to clear the terminal
    fflush(stdout);
#endif
}

void enable_echo() {
#ifdef _WIN32
    system("cls");  // Clear the screen to show the next output cleanly
#else
    printf("\033[2J\033[1;1H");  // ANSI escape code to clear the terminal
    fflush(stdout);
#endif
}

// Function to read a password without displaying it
char* tscl_console_in_read_password(const char* prompt) {
    printf("%s", prompt);

    disable_echo();

    size_t bufsize = 0;
    char* password = NULL;
    
    // Ensure getline is declared explicitly
    ssize_t bytesRead = getline(&password, &bufsize, stdin);

    enable_echo();

    // Check if getline was successful
    if (bytesRead == -1) {
        perror("getline");
        exit(EXIT_FAILURE);
    }

    // Remove newline character at the end of the password
    size_t len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }

    return password;
}
