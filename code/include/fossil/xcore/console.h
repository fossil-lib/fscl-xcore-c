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
#ifndef FSCL_CONSOLE_H
#define FSCL_CONSOLE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>

// Color Output Function
//
// This function enables colored console output by applying ANSI escape codes for text color.
// It supports various colors including dark, light, and standard versions of common colors.
//
// Usage:
// fscl_console_out_color("color_name", "formatted_text", ...);
//
// Supported Colors:
// - "reset": Resets the text color to the default.
// - "black", "dark_gray", "light_gray", "white": Various shades of gray and white.
// - "dark_red", "light_red": Dark and light shades of red.
// - "dark_green", "light_green": Dark and light shades of green.
// - "dark_yellow", "light_yellow": Dark and light shades of yellow.
// - "dark_blue", "light_blue": Dark and light shades of blue.
// - "dark_magenta", "light_magenta": Dark and light shades of magenta.
// - "dark_cyan", "light_cyan": Dark and light shades of cyan.
//
// Example:
//
// fscl_console_out_color("light_blue", "This is a %s message.\n", "light blue");
//

// =================================================================
// output functions
// =================================================================

/**
 * Print a message to the console without color.
 *
 * @param message The message to be printed.
 */
void fscl_console_puts(const char *message);

/**
 * Print a colored message to the console.
 *
 * @param color_name The name of the color for the message.
 * @param message    The message to be printed.
 */
void fscl_console_puts_color(const char *color_name, const char *message);

/**
 * Print formatted output to the console without color.
 *
 * @param format  The format string for the output.
 * @param ...     Additional arguments for formatted output.
 */
void fscl_console_out(const char *format, ...);

/**
 * Print formatted output with color to the console.
 *
 * @param color_name The name of the color for the output.
 * @param format     The format string for the output.
 * @param ...        Additional arguments for formatted output.
 */
void fscl_console_out_color(const char *color_name, const char *format, ...);

/**
 * Print formatted error message to the console.
 *
 * @param format The format string for the error message.
 * @param ...    Additional arguments for formatted output.
 */
void fscl_console_err(const char *format, ...);

/**
 * Clear the console screen.
 */
void fscl_console_clear(void);

/**
 * Flush the console output.
 */
void fscl_console_flush(void);

/**
 * Display a progress bar in the console.
 *
 * @param iterations The total number of iterations for the progress.
 * @param delay      The delay in milliseconds between progress updates.
 */
void fscl_console_progress(int iterations, int delay);

/**
 * Pause the console until user input is received.
 */
void fscl_console_pause(void);

// =================================================================
// input functions
// =================================================================

/**
 * Get a line of input from the console.
 *
 * @return A dynamically allocated string containing the user input.
 */
char* fscl_console_in_get_line(void);

/**
 * Read a line of input from the console with a prompt.
 *
 * @param prompt The prompt displayed to the user.
 * @return       A dynamically allocated string containing the user input.
 */
char* fscl_console_in_read_line(const char* prompt);

/**
 * Read a password from the console with a prompt, masking input.
 *
 * @param prompt The prompt displayed to the user.
 * @return       A dynamically allocated string containing the user input.
 */
char* fscl_console_in_read_password(const char* prompt);

/**
 * Validate user input using a custom validator function.
 *
 * @param prompt    The prompt displayed to the user.
 * @param validator A function pointer to a custom validator function.
 * @return          True if the input is valid, false otherwise.
 */
bool fscl_console_in_valid_input(const char* prompt, bool (*validator)(const char*));

/**
 * Confirm a yes/no question with the user.
 *
 * @param question The question displayed to the user.
 * @return         True if the user confirms with "yes," false otherwise.
 */
bool fscl_console_in_confirm_yes_no(const char* question);

/**
 * Display a menu and get the user's selection.
 *
 * @param question    The question or prompt for the menu.
 * @param menu        An array of strings representing menu options.
 * @param num_options The number of options in the menu.
 * @return            The index of the selected option.
 */
int fscl_console_in_confirm_menu(const char* question, const char** menu, int num_options);

/**
 * Display a multi-choice menu and get the user's selections.
 *
 * @param question    The question or prompt for the menu.
 * @param menu        An array of strings representing menu options.
 * @param selections  An array of boolean values indicating user selections.
 * @param num_options The number of options in the menu.
 */
void fscl_console_in_confirm_multi_menu(const char* question, const char** menu, bool* selections, int num_options);

/**
 * Confirm if the user wants to exit the program.
 *
 * @return True if the user confirms exit, false otherwise.
 */
bool fscl_console_in_confirm_exit(void);

/**
 * Read a date input from the console.
 *
 * @param prompt The prompt displayed to the user.
 * @param year   Pointer to store the entered year.
 * @param month  Pointer to store the entered month.
 * @param day    Pointer to store the entered day.
 * @return       True if the input is valid, false otherwise.
 */
bool fscl_console_in_read_date(const char* prompt, int* year, int* month, int* day);

/**
 * Read a time input from the console.
 *
 * @param prompt The prompt displayed to the user.
 * @param hour   Pointer to store the entered hour.
 * @param minute Pointer to store the entered minute.
 * @param second Pointer to store the entered second.
 * @return       True if the input is valid, false otherwise.
 */
bool fscl_console_in_read_time(const char* prompt, int* hour, int* minute, int* second);

#ifdef __cplusplus
}
#endif

#endif
