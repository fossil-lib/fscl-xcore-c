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
#ifndef TSCL_READER_H
#define TSCL_READER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>

enum {
    MAX_INPUT_LENGTH = 1024
};

/**
 * @brief Read a line of text from standard input and return it as a dynamically allocated string.
 *
 * @return A dynamically allocated string containing the read line, or NULL on failure.
 */
char* reader_get_line(void);

/**
 * @brief Read a line of text from standard input with a custom prompt and return it as a dynamically allocated string.
 *
 * @param prompt The custom prompt to display to the user.
 *
 * @return A dynamically allocated string containing the read line, or NULL on failure.
 */
char* reader_read_line(const char* prompt);

/**
 * @brief Prompt the user for input with a custom prompt and validate the input using a custom validator function.
 *
 * @param prompt     The custom prompt to display to the user.
 * @param validator  A function that checks the validity of the input string.
 *
 * @return true if the input is valid according to the validator function; false otherwise.
 */
bool reader_valid_input(const char* prompt, bool (*validator)(const char*));

/**
 * @brief Prompt the user for a yes or no confirmation with a custom question.
 *
 * @param question The question to ask the user.
 *
 * @return true if the user confirms with 'yes'; false if the user confirms with 'no'.
 */
bool reader_confirm_yes_no(const char* question);

/**
 * @brief Prompt the user to select an option from a menu with a custom question and an array of menu options.
 *
 * @param question       The question to ask the user.
 * @param menu           An array of menu options as strings.
 * @param num_options    The number of menu options.
 *
 * @return The index of the selected menu option (0-based index).
 */
int reader_confirm_menu(const char* question, const char** menu, int num_options);

/**
 * @brief Prompt the user to select multiple options from a menu with a custom question and an array of menu options.
 *
 * @param question       The question to ask the user.
 * @param menu           An array of menu options as strings.
 * @param selections     An array of boolean values representing user selections.
 * @param num_options    The number of menu options.
 */
void reader_confirm_multi_menu(const char* question, const char** menu, bool* selections, int num_options);

/**
 * @brief Prompt the user to confirm exit with a custom question.
 *
 * @return true if the user confirms exit; false if the user cancels the exit.
 */
bool reader_confirm_exit(void);

/**
 * @brief Prompts the user to enter a date and validates the input.
 *
 * @param prompt The custom prompt to display to the user.
 * @param year   Pointer to store the entered year.
 * @param month  Pointer to store the entered month.
 * @param day    Pointer to store the entered day.
 *
 * @return true if the input is valid; false otherwise.
 */
bool reader_read_date(const char* prompt, int* year, int* month, int* day);

/**
 * @brief Prompts the user to enter a time and validates the input.
 *
 * @param prompt The custom prompt to display to the user.
 * @param hour   Pointer to store the entered hour.
 * @param minute Pointer to store the entered minute.
 * @param second Pointer to store the entered second.
 *
 * @return true if the input is valid; false otherwise.
 */
bool reader_read_time(const char* prompt, int* hour, int* minute, int* second);

/**
 * @brief Clears the console screen.
 */
void reader_clear_screen(void);

#ifdef __cplusplus
}
#endif

#endif
