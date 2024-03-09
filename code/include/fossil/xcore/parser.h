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
#ifndef FSCL_FILE_PARSER_H
#define FSCL_FILE_PARSER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* json_data;
} cjson;

typedef struct {
    char key[256];
    char value[256];
} cjson_pair;

typedef struct {
    cjson_pair* pairs;
    size_t numPairs;
} cjson_object;

typedef struct {
    char** items;
    size_t numItems;
} cjson_array;

enum {TRILO_INI_FILE_LENGTH = 1555};

// Structure to store INI data
typedef struct {
    char key[TRILO_INI_FILE_LENGTH];
    char value[TRILO_INI_FILE_LENGTH];
} cini_entry;

typedef struct {
    cini_entry* entries;
    size_t size;
} cini;

// Structure to hold CSV data
typedef struct {
    char*** rows;
    size_t num_rows;
    size_t num_columns;
} ccsv;

// =================================================================
// Create and erase
// =================================================================

/**
 * Create a new JSON parser instance.
 *
 * @return A pointer to the created cjson structure.
 */
cjson* fscl_json_parser_create();

/**
 * Erase a JSON parser instance and free associated memory.
 *
 * @param data Pointer to the cjson pointer to be erased.
 */
void fscl_json_parser_erase(cjson** data);

// =================================================================
// Available Functions
// =================================================================

/**
 * Parse a JSON file and populate a cjson structure.
 *
 * @param file Pointer to the FILE structure of the JSON file to be parsed.
 * @param data Pointer to the cjson pointer to store the parsed data.
 * @return     0 on success, non-zero on failure.
 */
int fscl_json_parser_parse(FILE* file, cjson** data);

/**
 * Set the value of a JSON parser instance.
 *
 * @param data   Pointer to the cjson pointer to be updated.
 * @param update The JSON-formatted string to update the cjson instance.
 */
void fscl_json_parser_setter(cjson** data, const char* update);

/**
 * Get the JSON-formatted string from a cjson instance.
 *
 * @param data Pointer to the cjson pointer.
 * @return     A constant string containing the JSON-formatted data.
 */
const char* fscl_json_parser_getter(cjson** data);

/**
 * Erase metadata from a cjson instance, preserving the actual data.
 *
 * @param data Pointer to the cjson pointer.
 */
void fscl_json_parser_erase_meta(cjson** data);

/**
 * Get the cjson_object from a cjson instance.
 *
 * @param data Pointer to the cjson pointer.
 * @return     A pointer to the cjson_object structure.
 */
cjson_object* fscl_json_parser_get_object(cjson** data);

/**
 * Get the cjson_array from a cjson instance.
 *
 * @param data Pointer to the cjson pointer.
 * @return     A pointer to the cjson_array structure.
 */
cjson_array* fscl_json_parser_get_array(cjson** data);

// =================================================================
// Create and erase
// =================================================================

/**
 * Create a new INI parser instance.
 *
 * @param data Pointer to the cini pointer to store the created cini instance.
 */
void fscl_ini_parser_create(cini** data);

/**
 * Erase an INI parser instance and free associated memory.
 *
 * @param data Pointer to the cini pointer to be erased.
 */
void fscl_ini_parser_erase(cini** data);

// =================================================================
// Available Functions
// =================================================================

/**
 * Parse an INI file and populate a cini structure.
 *
 * @param file Pointer to the FILE structure of the INI file to be parsed.
 * @param data Pointer to the cini pointer to store the parsed data.
 */
void fscl_ini_parser_parse(FILE* file, cini** data);

/**
 * Set the value of an INI parser instance.
 *
 * @param data   Pointer to the cini pointer to be updated.
 * @param update The INI-formatted string to update the cini instance.
 */
void fscl_ini_parser_setter(cini** data, const char* update);

/**
 * Get the cini instance from a cini pointer.
 *
 * @param data Pointer to the cini pointer.
 * @return     A pointer to the cini structure.
 */
cini* fscl_ini_parser_getter(cini** data);

// =================================================================
// Create and erase
// =================================================================

/**
 * Create a new CSV parser instance.
 *
 * @return A pointer to the created ccsv structure.
 */
ccsv* fscl_csv_parser_create();

/**
 * Erase a CSV parser instance and free associated memory.
 *
 * @param data Pointer to the ccsv pointer to be erased.
 */
void fscl_csv_parser_erase(ccsv** data);

// =================================================================
// Available Functions
// =================================================================

/**
 * Parse a CSV file and populate a ccsv structure.
 *
 * @param file Pointer to the FILE structure of the CSV file to be parsed.
 * @param data Pointer to the ccsv pointer to store the parsed data.
 */
void fscl_csv_parser_parse(FILE* file, ccsv** data);

/**
 * Set the value of a specified cell in the CSV parser instance.
 *
 * @param data   Pointer to the ccsv pointer to be updated.
 * @param row    The row index of the cell.
 * @param col    The column index of the cell.
 * @param update The value to update the specified cell.
 */
void fscl_csv_parser_setter(ccsv** data, size_t row, size_t col, const char* update);

/**
 * Get the value of a specified cell in the CSV parser instance.
 *
 * @param data Pointer to the ccsv structure.
 * @param row  The row index of the cell.
 * @param col  The column index of the cell.
 * @return     A constant string containing the value of the specified cell.
 */
const char* fscl_csv_parser_getter(const ccsv* data, size_t row, size_t col);

#ifdef __cplusplus
}
#endif

#endif
