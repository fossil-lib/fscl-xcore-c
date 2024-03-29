/*
==============================================================================
Author: Michael Gene Brockus (Dreamer)
Email: michaelbrockus@gmail.com
Organization: Fossil Logic
Description: 
    This file is part of the Fossil Logic project, where innovation meets
    excellence in software development. Michael Gene Brockus, also known as
    "Dreamer," is a dedicated contributor to this project. For any inquiries,
    feel free to contact Michael at michaelbrockus@gmail.com.
==============================================================================
*/
#include "fossil/xcore/console.h"
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#define _GNU_SOURCE // for getline function
#include <termios.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

enum {
    MAX_INPUT_LENGTH = 1024
};

// General Output Function
void fscl_console_puts(const char *message) {
    puts(message);
}

// Color Output Function
void fscl_console_puts_color(const char *color_name, const char *message) {
    if (strcmp(color_name, "reset") == 0) {
        printf("\033[0m%s\033[0m\n", message);
    } else if (strcmp(color_name, "black") == 0) {
        printf("\033[0;30m%s\033[0m\n", message);
    } else if (strcmp(color_name, "dark_gray") == 0) {
        printf("\033[1;30m%s\033[0m\n", message);
    } else if (strcmp(color_name, "light_gray") == 0) {
        printf("\033[2;37m%s\033[0m\n", message);
    } else if (strcmp(color_name, "white") == 0) {
        printf("\033[1;37m%s\033[0m\n", message);
    } else if (strcmp(color_name, "dark_red") == 0) {
        printf("\033[0;31m%s\033[0m\n", message);
    } else if (strcmp(color_name, "light_red") == 0) {
        printf("\033[1;31m%s\033[0m\n", message);
    } else if (strcmp(color_name, "dark_green") == 0) {
        printf("\033[0;32m%s\033[0m\n", message);
    } else if (strcmp(color_name, "light_green") == 0) {
        printf("\033[1;32m%s\033[0m\n", message);
    } else if (strcmp(color_name, "dark_yellow") == 0) {
        printf("\033[0;33m%s\033[0m\n", message);
    } else if (strcmp(color_name, "light_yellow") == 0) {
        printf("\033[1;33m%s\033[0m\n", message);
    } else if (strcmp(color_name, "dark_blue") == 0) {
        printf("\033[0;34m%s\033[0m\n", message);
    } else if (strcmp(color_name, "light_blue") == 0) {
        printf("\033[1;34m%s\033[0m\n", message);
    } else if (strcmp(color_name, "dark_magenta") == 0) {
        printf("\033[0;35m%s\033[0m\n", message);
    } else if (strcmp(color_name, "light_magenta") == 0) {
        printf("\033[1;35m%s\033[0m\n", message);
    } else if (strcmp(color_name, "dark_cyan") == 0) {
        printf("\033[0;36m%s\033[0m\n", message);
    } else if (strcmp(color_name, "light_cyan") == 0) {
        printf("\033[1;36m%s\033[0m\n", message);
    } else {
        // Default to classic output if an unsupported color is specified
        puts(message);
        return;
    }
}

// General Output Function
void fscl_console_out(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

// Error Output Function
void fscl_console_err(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}

// Color Output Function
void fscl_console_out_color(const char *color_name, const char *format, ...) {
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
void fscl_console_clear() {
#ifdef _WIN32
    int dummy = system("cls");
#else
    int dummy = system("clear");
#endif
    (void)dummy;  // Avoid unused variable warning
}

// Flush Output Function
void fscl_console_flush() {
    fflush(stdout);
}

// Console Progress Function
void fscl_console_progress(int iterations, int delay) {
    const char *animation[] = {"|", "/", "-", "\\"};
    int i;
    
    for (i = 0; i < iterations; ++i) {
        printf("\rProgress: %s", animation[i % 4]);
        fflush(stdout);

#ifdef _WIN32
        Sleep(delay);  // Sleep in milliseconds on Windows
#else
        usleep(delay * 1000);  // Sleep in microseconds on POSIX
#endif
    }

    printf("\rProgress: Done!\n");
}

// Console Pause Function
void fscl_console_pause() {
    printf("Press Enter to continue...");
    getchar();  // Wait for user input (Enter key)
}

// Function to get a line of text from the user.
char* fscl_console_in_get_line() {
    static char buffer[MAX_INPUT_LENGTH];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove the trailing newline
        return buffer;
    }
    return NULL;
} // end of func

// Function to read a line of text from the user.
char* fscl_console_in_read_line(const char* prompt) {
    printf("%s: ", prompt);
    return fscl_console_in_get_line();
} // end of func

// Function to validate user input with a specific condition.
bool fscl_console_in_valid_input(const char* prompt, bool (*validator)(const char*)) {
    while (true) {
        char* input = fscl_console_in_read_line(prompt);
        if (input && validator(input)) {
            return true;
        }
        printf("Invalid input. Please try again.\n");
    }
} // end of func

// Function to confirm a yes/no question.
bool fscl_console_in_confirm_yes_no(const char* question) {
    while (true) {
        char* response = fscl_console_in_read_line(question);
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
int fscl_console_in_confirm_menu(const char* question, const char** menu, int num_options) {
    printf("%s:\n", question);
    for (int i = 0; i < num_options; i++) {
        printf("%d. %s\n", i + 1, menu[i]);
    }

    int choice;
    while (true) {
        char* response = fscl_console_in_read_line("Enter your choice");
        if (response && sscanf(response, "%d", &choice) == 1 && choice >= 1 && choice <= num_options) {
            return choice - 1;
        }
        printf("Invalid choice. Please enter a valid option.\n");
    }
} // end of func

// Function to confirm multiple selections from a menu.
void fscl_console_in_confirm_multi_menu(const char* question, const char** menu, bool* selections, int num_options) {
    printf("%s (Choose options by entering their numbers, separated by spaces):\n", question);
    for (int i = 0; i < num_options; i++) {
        printf("%d. %s\n", i + 1, menu[i]);
    }

    char* response = fscl_console_in_read_line("Enter your choices (e.g., '1 3 5')");

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
bool fscl_console_in_confirm_exit() {
    return fscl_console_in_confirm_yes_no("Do you want to exit?");
} // end of func

bool fscl_console_in_read_date(const char* prompt, int* year, int* month, int* day) {
    printf("%s", prompt);
    if (scanf("%d-%d-%d", year, month, day) == 3) {
        return true;
    } else {
        // Invalid input
        while (getchar() != '\n');  // Clear the input buffer
        return false;
    }
} // end of func

bool fscl_console_in_read_time(const char* prompt, int* hour, int* minute, int* second) {
    printf("%s", prompt);
    if (scanf("%d:%d:%d", hour, minute, second) == 3) {
        return true;
    } else {
        // Invalid input
        while (getchar() != '\n');  // Clear the input buffer
        return false;
    }
} // end of func

// Function to disable echoing for password input
void disable_echo() {
#ifdef _WIN32
    system("cls");  // Clear the screen to hide the password
#else
    // POSIX-specific code to disable echoing
    struct termios term;
    tcgetattr(fileno(stdin), &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(fileno(stdin), TCSANOW, &term);
#endif
}

// Function to enable echoing after password input
void enable_echo() {
#ifdef _WIN32
    system("cls");  // Clear the screen to show the next output cleanly
#else
    // POSIX-specific code to enable echoing
    struct termios term;
    tcgetattr(fileno(stdin), &term);
    term.c_lflag |= ECHO;
    tcsetattr(fileno(stdin), TCSANOW, &term);
#endif
}

// Function to read a password without displaying it
char* fscl_console_in_read_password(const char* prompt) {
    printf("%s", prompt);

    disable_echo();

    size_t bufsize = 64;  // Adjust this size as needed
    char* password = malloc(bufsize * sizeof(char));

    if (password == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (fgets(password, bufsize, stdin) == NULL) {
        perror("fgets");
        free(password);
        exit(EXIT_FAILURE);
    }

    enable_echo();

    // Remove newline character at the end of the password
    size_t len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }

    return password;
}
