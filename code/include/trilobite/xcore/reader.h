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

// =================================================================
// avaliable functions
// =================================================================
char* tscl_reader_get_line(void);
char* tscl_reader_read_line(const char* prompt);
bool tscl_reader_valid_input(const char* prompt, bool (*validator)(const char*));
bool tscl_reader_confirm_yes_no(const char* question);
int  tscl_reader_confirm_menu(const char* question, const char** menu, int num_options);
void tscl_reader_confirm_multi_menu(const char* question, const char** menu, bool* selections, int num_options);
bool tscl_reader_confirm_exit(void);
bool tscl_reader_read_date(const char* prompt, int* year, int* month, int* day);
bool tscl_reader_read_time(const char* prompt, int* hour, int* minute, int* second);
void tscl_reader_clear_screen(void);

#ifdef __cplusplus
}
#endif

#endif
