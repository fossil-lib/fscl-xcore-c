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
#ifndef FSCL_DATETIME_H
#define FSCL_DATETIME_H

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
bool fscl_datetime_get_current_parse_military(const char *str, cdatetime *datetime);
bool fscl_datetime_get_current_parse_12_hour(const char *str, cdatetime *datetime);
bool fscl_datetime_get_current_parse_human_readable(const char *str, cdatetime *datetime);
void fscl_datetime_get_current_custom(const cdatetime *datetime, char *str, size_t max_size);

// =================================================================
// Calander functions
// =================================================================
void fscl_datetime_get_current_calendar_yyyy_mm_dd(const ccalendar *calendar, char *str, size_t max_size);
void fscl_datetime_get_current_calendar_dd_mm_yyyy(const ccalendar *calendar, char *str, size_t max_size);
void fscl_datetime_get_current_calendar_month_dd_yyyy(const ccalendar *calendar, char *str, size_t max_size);
bool fscl_datetime_get_current_is_leap_year(int year);

// =================================================================
// DateTime utilities
// =================================================================
void fscl_datetime_sleep(unsigned int seconds);
void fscl_datetime_get_current(cdatetime *datetime);

#ifdef __cplusplus
}
#endif

#endif
