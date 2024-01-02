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
// create and erase
// =================================================================
cjson*  fscl_json_parser_create();
void  fscl_json_parser_erase(cjson** data);

// =================================================================
// avaliable functions
// =================================================================
int  fscl_json_parser_parse(FILE* file, cjson** data);
void  fscl_json_parser_setter(cjson** data, const char* update);
const char*  fscl_json_parser_getter(cjson** data);
void  fscl_json_parser_erase_meta(cjson** data);
cjson_object*  fscl_json_parser_get_object(cjson** data);
cjson_array*  fscl_json_parser_get_array(cjson** data);

// =================================================================
// create and erase
// =================================================================
void  fscl_ini_parser_create(cini** data);
void  fscl_ini_parser_erase(cini** data);

// =================================================================
// avaliable functions
// =================================================================
void  fscl_ini_parser_parse(FILE* file, cini** data);
void  fscl_ini_parser_setter(cini** data, const char* update);
cini*  fscl_ini_parser_getter(cini** data);

// =================================================================
// create and erase
// =================================================================
ccsv*  fscl_csv_parser_create();
void  fscl_csv_parser_erase(ccsv** data);

// =================================================================
// avaliable functions
// =================================================================
void  fscl_csv_parser_parse(FILE* file, ccsv** data);
void  fscl_csv_parser_setter(ccsv** data, size_t row, size_t col, const char* update);
const char*  fscl_csv_parser_getter(const ccsv* data, size_t row, size_t col);


#ifdef __cplusplus
}
#endif

#endif
