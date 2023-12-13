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

/**
 * @brief Parses a DateTime string in 24-hour format (military time).
 *
 * This function parses a DateTime string in the format "YYYY-MM-DD HH:MM:SS +/-HHMM"
 * and populates a cdatetime structure with the parsed values.
 *
 * @param str The DateTime string to parse.
 * @param datetime Pointer to a cdatetime structure to store the parsed DateTime.
 * @return true if the parsing is successful, false otherwise.
 */
bool datetime_get_current_parse_military(const char *str, cdatetime *datetime);

/**
 * @brief Parses a DateTime string in 12-hour format with AM/PM.
 *
 * This function parses a DateTime string in the format "YYYY-MM-DD HH:MM:SS AM/PM +/-HHMM"
 * and populates a cdatetime structure with the parsed values.
 *
 * @param str The DateTime string to parse.
 * @param datetime Pointer to a cdatetime structure to store the parsed DateTime.
 * @return true if the parsing is successful, false otherwise.
 */
bool datetime_get_current_parse_12_hour(const char *str, cdatetime *datetime);

/**
 * @brief Parses a DateTime string in human-readable format.
 *
 * This function parses a DateTime string in a human-readable format and populates a
 * cdatetime structure with the parsed values. The format may vary depending on
 * locale and custom representations.
 *
 * @param str The DateTime string to parse.
 * @param datetime Pointer to a cdatetime structure to store the parsed DateTime.
 * @return true if the parsing is successful, false otherwise.
 */
bool datetime_get_current_parse_human_readable(const char *str, cdatetime *datetime);

/**
 * @brief Formats a cdatetime object into a custom string.
 *
 * This function formats a cdatetime object into a custom string format
 * and stores the result in the provided character array 'str'.
 *
 * @param datetime Pointer to a cdatetime structure to be formatted.
 * @param str Pointer to the character array where the formatted string will be stored.
 * @param max_size The maximum size of the character array 'str'.
 */
void datetime_get_current_custom(const cdatetime *datetime, char *str, size_t max_size);

/**
 * @brief Retrieves the current date and time and stores it in the provided cdatetime structure.
 *
 * This function obtains the current system date and time and populates a cdatetime structure
 * with the corresponding year, month, day, hour, minute, and second. The 'ampm' field is set
 * to -1 as it is not applicable in the 24-hour format. The 'timezone' field may need to be
 * set explicitly or left empty depending on your application's requirements.
 *
 * @param datetime Pointer to a cdatetime structure where the current date and time will be stored.
 */
void datetime_get_current_get_current(cdatetime *datetime);

/**
 * @brief Formats a ccalendar object into a string with the format "YYYY-MM-DD".
 *
 * @param calendar Pointer to a ccalendar structure to be formatted.
 * @param str Pointer to the character array where the formatted string will be stored.
 * @param max_size The maximum size of the character array 'str'.
 */
void datetime_get_current_calendar_yyyy_mm_dd(const ccalendar *calendar, char *str, size_t max_size);

/**
 * @brief Formats a ccalendar object into a string with the format "DD/MM/YYYY".
 *
 * @param calendar Pointer to a ccalendar structure to be formatted.
 * @param str Pointer to the character array where the formatted string will be stored.
 * @param max_size The maximum size of the character array 'str'.
 */
void datetime_get_current_calendar_dd_mm_yyyy(const ccalendar *calendar, char *str, size_t max_size);

/**
 * @brief Formats a ccalendar object into a string with the format "Month DD, YYYY".
 *
 * @param calendar Pointer to a ccalendar structure to be formatted.
 * @param str Pointer to the character array where the formatted string will be stored.
 * @param max_size The maximum size of the character array 'str'.
 */
void datetime_get_current_calendar_month_dd_yyyy(const ccalendar *calendar, char *str, size_t max_size);

/**
 * @brief Checks if a given year is a leap year.
 *
 * @param year The year to check.
 * @return true if the year is a leap year, false otherwise.
 */
bool datetime_get_current_is_leap_year(int year);

#ifdef __cplusplus
}
#endif

#endif
