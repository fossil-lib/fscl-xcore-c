/*  ----------------------------------------------------------------------------
    File: datetime.c

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
#include "trilobite/xcore/datetime.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Function to get the month index from a month name
char* tscl_datetime_get_current_month(int month) {
    char *months[] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    if (month >= 1 && month <= 12) {
        return months[month];
    } else {
        return "Invalid Index";
    }
} // end of func

char* tscl_datetime_get_current_ampm(int hour) {
    if (hour >= 0 && hour <= 11) {
        return "AM";
    } else if (hour >= 12 && hour <= 23) {
        return "PM";
    } else {
        return "Invalid Hour"; // Handle invalid hour values
    }
} // end of func

// Function to parse a DateTime string in 24-hour format (military time)
bool tscl_datetime_get_current_parse_military(const char *str, cdatetime *datetime) {
    // Error checking for NULL pointers
    if (str == NULL || datetime == NULL) {
        return false;
    }

    // Parse the string in 24-hour format
    if (sscanf(str, "%d-%d-%d %d:%d:%d %s",
               &datetime->year, &datetime->month, &datetime->day,
               &datetime->hour, &datetime->minute, &datetime->second,
               datetime->timezone) != 7) {
        return false; // Parsing failed
    }

    return true; // Successful parsing
} // end of func

// Function to parse a DateTime string in 12-hour format with AM/PM
bool tscl_datetime_get_current_parse_12_hour(const char *str, cdatetime *datetime) {
    // Error checking for NULL pointers
    if (str == NULL || datetime == NULL) {
        return false;
    }

    // Parse the string in 12-hour format with AM/PM
    if (sscanf(str, "%d-%d-%d %d:%d:%d %2d %s",
               &datetime->year, &datetime->month, &datetime->day,
               &datetime->hour, &datetime->minute, &datetime->second,
               &datetime->ampm, datetime->timezone) != 8) {
        return false; // Parsing failed
    }

    return true; // Successful parsing
} // end of func

// Function to parse a DateTime string in human-readable format
bool tscl_datetime_get_current_parse_human_readable(const char *str, cdatetime *datetime) {
    // Error checking for NULL pointers
    if (str == NULL || datetime == NULL) {
        return false;
    }

    // Parse the string in human-readable format
    if (sscanf(str, "%d-%3s-%d, %d:%d %2s",
               &datetime->year, tscl_datetime_get_current_month(datetime->month),
               &datetime->day, &datetime->hour, &datetime->minute,
               tscl_datetime_get_current_ampm(datetime->ampm)) != 6) {
        return false; // Parsing failed
    }

    return true; // Successful parsing
} // end of func

// Function to format a cdatetime object into a custom string
void tscl_datetime_get_current_custom(const cdatetime *datetime, char *str, size_t max_size) {
    // Error checking for NULL pointers
    if (datetime == NULL || str == NULL) {
        return;
    }

    // Format the cdatetime object into a custom string
    snprintf(str, max_size, "%04d-%02d-%02d %02d:%02d:%02d %s",
             datetime->year, datetime->month, datetime->day,
             datetime->hour, datetime->minute, datetime->second,
             datetime->timezone);
} // end of func

void tscl_datetime_get_current(cdatetime *datetime) {
    time_t current_time;
    struct tm *time_info;

    time(&current_time);
    time_info = localtime(&current_time);

    datetime->year = time_info->tm_year + 1900;
    datetime->month = time_info->tm_mon + 1;
    datetime->day = time_info->tm_mday;
    datetime->hour = time_info->tm_hour;
    datetime->minute = time_info->tm_min;
    datetime->second = time_info->tm_sec;
    datetime->ampm = -1; // Not applicable
    // You may want to set a default timezone or leave it blank
    // datetime->timezone[0] = '\0';
} // end of func

// Formats a ccalendar object into a string with the format "YYYY-MM-DD".
void tscl_datetime_get_current_calendar_yyyy_mm_dd(const ccalendar *calendar, char *str, size_t max_size) {
    snprintf(str, max_size, "%04d-%02d-%02d", calendar->year, calendar->month, calendar->day);
} // end of func

// Formats a ccalendar object into a string with the format "DD/MM/YYYY".
void tscl_datetime_get_current_calendar_dd_mm_yyyy(const ccalendar *calendar, char *str, size_t max_size) {
    snprintf(str, max_size, "%02d/%02d/%04d", calendar->day, calendar->month, calendar->year);
} // end of func

// Formats a ccalendar object into a string with the format "Month DD, YYYY".
void tscl_datetime_get_current_calendar_month_dd_yyyy(const ccalendar *calendar, char *str, size_t max_size) {
    static const char *months[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    snprintf(str, max_size, "%s %02d, %04d", months[calendar->month], calendar->day, calendar->year);
} // end of func

// Checks if a given year is a leap year.
bool tscl_datetime_get_current_is_leap_year(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
} // end of func

void tscl_datetime_sleep(unsigned int seconds) {
#ifdef _WIN32
    Sleep(seconds * 1000);  // Sleep takes milliseconds on Windows
#else
    sleep(seconds);
#endif
} // end of func