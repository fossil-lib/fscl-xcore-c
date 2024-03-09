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

/**
 * Parse a military time string and populate a cdatetime structure with the current date.
 *
 * @param str      The military time string to be parsed.
 * @param datetime Pointer to a cdatetime structure to store the parsed date and time.
 * @return         True if parsing is successful, false otherwise.
 */
bool fscl_datetime_get_current_parse_military(const char *str, cdatetime *datetime);

/**
 * Parse a 12-hour time string and populate a cdatetime structure with the current date.
 *
 * @param str      The 12-hour time string to be parsed.
 * @param datetime Pointer to a cdatetime structure to store the parsed date and time.
 * @return         True if parsing is successful, false otherwise.
 */
bool fscl_datetime_get_current_parse_12_hour(const char *str, cdatetime *datetime);

/**
 * Parse a human-readable time string and populate a cdatetime structure with the current date.
 *
 * @param str      The human-readable time string to be parsed.
 * @param datetime Pointer to a cdatetime structure to store the parsed date and time.
 * @return         True if parsing is successful, false otherwise.
 */
bool fscl_datetime_get_current_parse_human_readable(const char *str, cdatetime *datetime);

/**
 * Get a custom string representation of a cdatetime structure.
 *
 * @param datetime Pointer to a cdatetime structure.
 * @param str      Buffer to store the custom string representation.
 * @param max_size Maximum size of the buffer.
 */
void fscl_datetime_get_current_custom(const cdatetime *datetime, char *str, size_t max_size);

// =================================================================
// Calander functions
// =================================================================

/**
 * Get the current date in the "YYYY-MM-DD" format from a ccalendar structure.
 *
 * @param calendar Pointer to a ccalendar structure.
 * @param str      Buffer to store the formatted date string.
 * @param max_size Maximum size of the buffer.
 */
void fscl_datetime_get_current_calendar_yyyy_mm_dd(const ccalendar *calendar, char *str, size_t max_size);

/**
 * Get the current date in the "DD-MM-YYYY" format from a ccalendar structure.
 *
 * @param calendar Pointer to a ccalendar structure.
 * @param str      Buffer to store the formatted date string.
 * @param max_size Maximum size of the buffer.
 */
void fscl_datetime_get_current_calendar_dd_mm_yyyy(const ccalendar *calendar, char *str, size_t max_size);

/**
 * Get the current date in the "Month DD, YYYY" format from a ccalendar structure.
 *
 * @param calendar Pointer to a ccalendar structure.
 * @param str      Buffer to store the formatted date string.
 * @param max_size Maximum size of the buffer.
 */
void fscl_datetime_get_current_calendar_month_dd_yyyy(const ccalendar *calendar, char *str, size_t max_size);

/**
 * Check if the given year is a leap year.
 *
 * @param year The year to be checked.
 * @return     True if the year is a leap year, false otherwise.
 */
bool fscl_datetime_get_current_is_leap_year(int year);

// =================================================================
// DateTime utilities
// =================================================================

/**
 * Sleep for the specified number of seconds.
 *
 * @param seconds The duration of sleep in seconds.
 */
void fscl_datetime_sleep(unsigned int seconds);

/**
 * Get the current date and time and populate a cdatetime structure.
 *
 * @param datetime Pointer to a cdatetime structure to store the current date and time.
 */
void fscl_datetime_get_current(cdatetime *datetime);

#ifdef __cplusplus
}
#endif

#endif
