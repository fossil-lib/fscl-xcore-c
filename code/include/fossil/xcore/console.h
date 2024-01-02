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
void fscl_console_out(const char *format, ...);
void fscl_console_err(const char *format, ...);
void fscl_console_out_color(const char *color_name, const char *format, ...);
void fscl_console_clear(void);
void fscl_console_flush(void);
void fscl_console_progress(int iterations, int delay);
void fscl_console_pause(void);

// =================================================================
// input functions
// =================================================================
char* fscl_console_in_get_line(void);
char* fscl_console_in_read_line(const char* prompt);
char* fscl_console_in_read_password(const char* prompt);
bool fscl_console_in_valid_input(const char* prompt, bool (*validator)(const char*));
bool fscl_console_in_confirm_yes_no(const char* question);
int  fscl_console_in_confirm_menu(const char* question, const char** menu, int num_options);
void fscl_console_in_confirm_multi_menu(const char* question, const char** menu, bool* selections, int num_options);
bool fscl_console_in_confirm_exit(void);
bool fscl_console_in_read_date(const char* prompt, int* year, int* month, int* day);
bool fscl_console_in_read_time(const char* prompt, int* hour, int* minute, int* second);

#ifdef __cplusplus
}
#endif

#endif
