/*
   This C header file is part of the Trilobite Stdlib, a collection of utility functions and
   standard data structures for enhancing software development projects. Feel free to use
   and modify these utilities to streamline your software development process.

   Project: Trilobite Stdlib
   Author: Michael Gene Brockus (Dreamer)
   Email: michaelbrockus@gmail.com
   Website: [Trilobite Coder Blog](https://trilobite.home.blog)

   Trilobite Stdlib is designed to provide a robust set of functionalities that can be
   incorporated into various projects. The utilities included in this library aim to optimize
   and standardize common operations, ensuring efficient and reliable code.

   This header file is a part of a broader initiative to support developers in creating secure,
   efficient, and scalable software. Contributions, suggestions, and feedback are welcomed,
   as we strive to continuously improve and expand the capabilities of Trilobite Stdlib.

   License: Apache License 2.0
   SPDX Identifier: Apache-2.0

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software distributed under the License
   is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
   or implied. See the License for the specific language governing permissions and limitations
   under the License.

   The above copyright notice and this permission notice shall be included in all copies or
   substantial portions of the Software.

   Please review the full text of the Apache License 2.0 for the complete terms and conditions.

   (Apache License 2.0: http://www.apache.org/licenses/LICENSE-2.0)
*/
#ifndef TSCL_CONSOLE_H
#define TSCL_CONSOLE_H

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
// tscl_console_out_color("color_name", "formatted_text", ...);
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
// tscl_console_out_color("light_blue", "This is a %s message.\n", "light blue");
//

// =================================================================
// output functions
// =================================================================
void tscl_console_out(const char *format, ...);
void tscl_console_err(const char *format, ...);
void tscl_console_out_color(const char *color_name, const char *format, ...);
void tscl_console_clear(void);
void tscl_console_flush(void);
void tscl_console_progress(int iterations, int delay);
void tscl_console_pause(void);

// =================================================================
// input functions
// =================================================================
char* tscl_console_in_get_line(void);
char* tscl_console_in_read_line(const char* prompt);
char* tscl_console_in_read_password(const char* prompt);
bool tscl_console_in_valid_input(const char* prompt, bool (*validator)(const char*));
bool tscl_console_in_confirm_yes_no(const char* question);
int  tscl_console_in_confirm_menu(const char* question, const char** menu, int num_options);
void tscl_console_in_confirm_multi_menu(const char* question, const char** menu, bool* selections, int num_options);
bool tscl_console_in_confirm_exit(void);
bool tscl_console_in_read_date(const char* prompt, int* year, int* month, int* day);
bool tscl_console_in_read_time(const char* prompt, int* hour, int* minute, int* second);

#ifdef __cplusplus
}
#endif

#endif
