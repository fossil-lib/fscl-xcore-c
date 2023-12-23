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
#ifndef TSCL_datetime_H
#define TSCL_datetime_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>

typedef struct cdatetime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int ampm;         // Additional member for 12-hour format with AM/PM
    char timezone[6]; // Stores time zone as a string (e.g., "+0300")
} cdatetime;

// Calendar type
typedef struct {
    int year;
    int month;
    int day;
} ccalendar;

// =================================================================
// Timestamp functions
// =================================================================
bool tscl_datetime_get_current_parse_military(const char *str, cdatetime *datetime);
bool tscl_datetime_get_current_parse_12_hour(const char *str, cdatetime *datetime);
bool tscl_datetime_get_current_parse_human_readable(const char *str, cdatetime *datetime);
void tscl_datetime_get_current_custom(const cdatetime *datetime, char *str, size_t max_size);

// =================================================================
// Calander functions
// =================================================================
void tscl_datetime_get_current_calendar_yyyy_mm_dd(const ccalendar *calendar, char *str, size_t max_size);
void tscl_datetime_get_current_calendar_dd_mm_yyyy(const ccalendar *calendar, char *str, size_t max_size);
void tscl_datetime_get_current_calendar_month_dd_yyyy(const ccalendar *calendar, char *str, size_t max_size);
bool tscl_datetime_get_current_is_leap_year(int year);

// =================================================================
// DateTime utilities
// =================================================================
void tscl_datetime_sleep(unsigned int seconds);
void tscl_datetime_get_current(cdatetime *datetime);

#ifdef __cplusplus
}
#endif

#endif
