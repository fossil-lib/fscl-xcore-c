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
#include "fossil/xcore/parser.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


static void skip_whitespace(const char** ptr) {
    while (**ptr == ' ' || **ptr == '\t' || **ptr == '\n' || **ptr == '\r') {
        (*ptr)++;
    }
}

// Add this function inside the json.c file
static int parse_number(const char** ptr, double* number) {
    skip_whitespace(ptr);

    char numberStr[256];
    size_t len = 0;

    // Allow for an optional minus sign
    if (**ptr == '-') {
        numberStr[len++] = *(*ptr)++;
    }

    // Parse digits before the decimal point
    while (isdigit(**ptr)) {
        numberStr[len++] = *(*ptr)++;
    }

    // Parse digits after the decimal point
    if (**ptr == '.') {
        numberStr[len++] = *(*ptr)++;  // Include the decimal point

        while (isdigit(**ptr)) {
            numberStr[len++] = *(*ptr)++;
        }
    }

    // Parse exponent (optional)
    if (**ptr == 'e' || **ptr == 'E') {
        numberStr[len++] = *(*ptr)++;  // Include 'e' or 'E'

        if (**ptr == '+' || **ptr == '-') {
            numberStr[len++] = *(*ptr)++;
        }

        while (isdigit(**ptr)) {
            numberStr[len++] = *(*ptr)++;
        }
    }

    numberStr[len] = '\0';

    // Convert string to double
    *number = strtod(numberStr, NULL);

    return 1;  // Success
}

static int parse_value(const char** ptr, char* buffer, size_t bufferSize, double* number, int* boolean, int* isNull) {
    skip_whitespace(ptr);

    if (**ptr == '\"') {
        // String value
        (*ptr)++;
        size_t len = 0;
        while (**ptr != '\"' && len < bufferSize - 1) {
            buffer[len++] = *(*ptr)++;
        }
        buffer[len] = '\0';

        if (**ptr == '\"') {
            (*ptr)++;
            return 1; // Success
        } else {
            return 0; // String not terminated properly
        }
    } else if (isdigit(**ptr) || **ptr == '-') {
        // Number value
        if (parse_number(ptr, number)) {
            return 2;  // Numeric value
        }
    } else if (**ptr == 't' && strncmp(*ptr, "true", 4) == 0) {
        // Boolean true
        *boolean = 1;
        (*ptr) += 4;
        return 3;  // Boolean true
    } else if (**ptr == 'f' && strncmp(*ptr, "false", 5) == 0) {
        // Boolean false
        *boolean = 0;
        (*ptr) += 5;
        return 4;  // Boolean false
    } else if (**ptr == 'n' && strncmp(*ptr, "null", 4) == 0) {
        // Null value
        *isNull = 1;
        (*ptr) += 4;
        return 5;  // Null
    } else {
        // Other types not implemented for simplicity
        return 0; // Unsupported type
    }
    return 0;
}

static int parse_object(const char** ptr, cjson_object* object) {
    skip_whitespace(ptr);

    if (**ptr == '{') {
        (*ptr)++;
        while (**ptr != '\0' && **ptr != '}') {
            skip_whitespace(ptr);

            char key[256];
            double number; // Added for numeric value
            int boolean;   // Added for boolean value
            int isNull;     // Added for null value

            int result = parse_value(ptr, key, sizeof(key), &number, &boolean, &isNull);
            if (result == 1) {
                skip_whitespace(ptr);

                if (**ptr == ':') {
                    (*ptr)++;
                    skip_whitespace(ptr);

                    char value[256];
                    result = parse_value(ptr, value, sizeof(value), &number, &boolean, &isNull);
                    if (result == 1 || result == 2 || result == 3 || result == 4 || result == 5) {
                        // Add the key-value pair to the object
                        object->numPairs++;
                        object->pairs = (cjson_pair*)realloc(object->pairs, object->numPairs * sizeof(cjson_pair));
                        strcpy(object->pairs[object->numPairs - 1].key, key);

                        if (result == 1) {
                            strcpy(object->pairs[object->numPairs - 1].value, value);
                        } else if (result == 2) {
                            sprintf(object->pairs[object->numPairs - 1].value, "%.17g", number);
                        } else if (result == 3) {
                            strcpy(object->pairs[object->numPairs - 1].value, "true");
                        } else if (result == 4) {
                            strcpy(object->pairs[object->numPairs - 1].value, "false");
                        } else if (result == 5) {
                            strcpy(object->pairs[object->numPairs - 1].value, "null");
                        }
                    }
                }
            }

            skip_whitespace(ptr);

            if (**ptr == ',') {
                (*ptr)++;
                skip_whitespace(ptr);
            }
        }

        if (**ptr == '}') {
            (*ptr)++;
            return 1; // Success
        }
    }

    return 0; // Parsing failure
}

static int parse_array(const char** ptr, cjson_array* array) {
    skip_whitespace(ptr);

    if (**ptr == '[') {
        (*ptr)++;
        while (**ptr != '\0' && **ptr != ']') {
            skip_whitespace(ptr);

            char value[256];
            double number; // Added for numeric value
            int boolean;   // Added for boolean value
            int isNull;     // Added for null value

            int result = parse_value(ptr, value, sizeof(value), &number, &boolean, &isNull);
            if (result == 1 || result == 2 || result == 3 || result == 4 || result == 5) {
                // Add the value to the array
                array->numItems++;
                array->items = (char**)realloc(array->items, array->numItems * sizeof(char*));

                // Allocate memory for the new string and copy the value
                array->items[array->numItems - 1] = (char*)malloc(strlen(value) + 1);
                if (result == 1) {
                    strcpy(array->items[array->numItems - 1], value);
                } else if (result == 2) {
                    sprintf(array->items[array->numItems - 1], "%.17g", number);
                } else if (result == 3) {
                    strcpy(array->items[array->numItems - 1], "true");
                } else if (result == 4) {
                    strcpy(array->items[array->numItems - 1], "false");
                } else if (result == 5) {
                    strcpy(array->items[array->numItems - 1], "null");
                }
            }

            skip_whitespace(ptr);

            if (**ptr == ',') {
                (*ptr)++;
                skip_whitespace(ptr);
            }
        }

        if (**ptr == ']') {
            (*ptr)++;
            return 1; // Success
        }
    }

    return 0; // Parsing failure
}

static int parse_json(const char* json, cjson** data) {
    const char* ptr = json;

    skip_whitespace(&ptr);

    if (*ptr == '{') {
        // JSON Object
        cjson_object object = {NULL, 0};
        if (parse_object(&ptr, &object)) {
             fscl_json_parser_setter(data, "");
             fscl_json_parser_get_object(data)->numPairs = object.numPairs;
             fscl_json_parser_get_object(data)->pairs = object.pairs;
            return 1; // Success
        }
    } else if (*ptr == '[') {
        // JSON Array
        cjson_array array = {NULL, 0};
        if (parse_array(&ptr, &array)) {
             fscl_json_parser_setter(data, "");
             fscl_json_parser_get_array(data)->numItems = array.numItems;
             fscl_json_parser_get_array(data)->items = array.items;
            return 1; // Success
        }
    }

    return 0; // Parsing failure
}

cjson*  fscl_json_parser_create() {
    cjson* data = (cjson*)malloc(sizeof(cjson));
    if (data == NULL) {
        perror("Error creating cjson");
        return NULL;
    }

    data->json_data = NULL;
    return data;
}

void  fscl_json_parser_erase(cjson** data) {
    if (data != NULL && *data != NULL) {
         fscl_json_parser_erase_meta(data);
        free(*data);
        *data = NULL;
    }
}

int  fscl_json_parser_parse(FILE* file, cjson** data) {
    if (file == NULL || data == NULL) {
        perror("Invalid arguments");
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    (*data)->json_data = (char*)malloc(file_size + 1);
    if ((*data)->json_data == NULL) {
        perror("Error allocating memory for JSON data");
        return 0;
    }

    size_t read_size = fread((*data)->json_data, 1, file_size, file);
    if (read_size != (size_t)file_size) {
        perror("Error reading file content");
        free((*data)->json_data);
        (*data)->json_data = NULL;
        return 0;
    }

    (*data)->json_data[file_size] = '\0';

    return parse_json((*data)->json_data, data);
}

void  fscl_json_parser_setter(cjson** data, const char* update) {
    if (data != NULL && *data != NULL && update != NULL) {
        free((*data)->json_data);

        // Allocate memory for updated JSON data
        (*data)->json_data = (char*)malloc(strlen(update) + 1);
        if ((*data)->json_data == NULL) {
            perror("Error allocating memory for JSON data");
            return;
        }

        // Copy the update string
        strcpy((*data)->json_data, update);
    }
}

const char*  fscl_json_parser_getter(cjson** data) {
    if (data != NULL && *data != NULL) {
        return (*data)->json_data;
    }
    return NULL;
}

void  fscl_json_parser_erase_meta(cjson** data) {
    if (data != NULL && *data != NULL) {
        free((*data)->json_data);
        (*data)->json_data = NULL;
    }
}

cjson_object*  fscl_json_parser_get_object(cjson** data) {
    if (data != NULL && *data != NULL) {
        return (cjson_object*)((*data)->json_data);
    }
    return NULL;
}

cjson_array*  fscl_json_parser_get_array(cjson** data) {
    if (data != NULL && *data != NULL) {
        return (cjson_array*)((*data)->json_data);
    }
    return NULL;
} // end of func

// Function to create a new cini structure
void  fscl_ini_parser_create(cini** data) {
    *data = (cini*)malloc(sizeof(cini));
    (*data)->entries = NULL;
    (*data)->size = 0;
}

// Function to erase a cini structure
void  fscl_ini_parser_erase(cini** data) {
    if (*data != NULL) {
        free((*data)->entries);
        free(*data);
        *data = NULL;
    }
}

// Function to parse an INI file and populate cini structure
void  fscl_ini_parser_parse(FILE* file, cini** data) {
     fscl_ini_parser_erase(data); // Clear existing data

    *data = (cini*)malloc(sizeof(cini));

    // Initialize entries array
    (*data)->entries = NULL;
    (*data)->size = 0;

    char line[TRILO_INI_FILE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Skip comments and empty lines
        if (line[0] == ';' || line[0] == '#' || line[0] == '\n' || line[0] == '\r') {
            continue;
        }

        // Parse key-value pairs
        cini_entry entry;
        if (sscanf(line, "%[^=]=%[^\n]", entry.key, entry.value) == 2) {
            (*data)->entries = (cini_entry*)realloc((*data)->entries,
                ((*data)->size + 1) * sizeof(cini_entry));

            // Copy the entry to the array
            strcpy((*data)->entries[(*data)->size].key, entry.key);
            strcpy((*data)->entries[(*data)->size].value, entry.value);

            (*data)->size++;
        }
    }
}

// Function to update or add an entry in cini structure
void  fscl_ini_parser_setter(cini** data, const char* update) {
    char key[TRILO_INI_FILE_LENGTH];
    char value[TRILO_INI_FILE_LENGTH];

    if (sscanf(update, "%[^=]=%[^\n]", key, value) == 2) {
        // Search for existing key and update its value
        for (size_t i = 0; i < (*data)->size; ++i) {
            if (strcmp((*data)->entries[i].key, key) == 0) {
                strcpy((*data)->entries[i].value, value);
                return;
            }
        }

        // Key not found, add a new entry
        (*data)->entries = (cini_entry*)realloc((*data)->entries,
            ((*data)->size + 1) * sizeof(cini_entry));

        strcpy((*data)->entries[(*data)->size].key, key);
        strcpy((*data)->entries[(*data)->size].value, value);

        (*data)->size++;
    }
}

// Function to get the cini structure
cini*  fscl_ini_parser_getter(cini** data) {
    return *data;
} // end of func // end of func

// Function to create a ccsv structure
ccsv*  fscl_csv_parser_create() {
    ccsv* csv = (ccsv*)malloc(sizeof(ccsv));
    if (csv == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    csv->rows = NULL;
    csv->num_rows = 0;
    csv->num_columns = 0;

    return csv;
} // end of func

// Function to erase a ccsv structure
void  fscl_csv_parser_erase(ccsv** data) {
    if (data != NULL && *data != NULL) {
        // Free memory for each row
        for (size_t i = 0; i < (*data)->num_rows; ++i) {
            for (size_t j = 0; j < (*data)->num_columns; ++j) {
                free((*data)->rows[i][j]);
            }
            free((*data)->rows[i]);
        }

        // Free memory for rows array
        free((*data)->rows);

        // Free memory for ccsv structure
        free(*data);

        // Set data pointer to NULL
        *data = NULL;
    }
} // end of func

// Function to parse CSV file and populate ccsv structure
void  fscl_csv_parser_parse(FILE* file, ccsv** data) {
    char buffer[1024];  // Adjust buffer size as needed

    // Count the number of rows and columns in the CSV file
    size_t num_rows = 0;
    size_t num_columns = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char* token = strtok(buffer, ",");
        size_t current_columns = 0;

        while (token != NULL) {
            token = strtok(NULL, ",");
            current_columns++;
        }

        // Update the number of columns if it is greater than the current count
        if (current_columns > num_columns) {
            num_columns = current_columns;
        }

        num_rows++;
    }

    // Reset file position to the beginning
    fseek(file, 0, SEEK_SET);

    // Allocate memory for ccsv structure
    *data =  fscl_csv_parser_create();

    // Allocate memory for rows array
    (*data)->rows = (char***)malloc(num_rows * sizeof(char**));
    if ((*data)->rows == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < num_rows; ++i) {
        (*data)->rows[i] = (char**)malloc(num_columns * sizeof(char*));
        if ((*data)->rows[i] == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        // Initialize each element to NULL
        for (size_t j = 0; j < num_columns; ++j) {
            (*data)->rows[i][j] = NULL;
        }
    }

    // Populate the ccsv structure with data from the CSV file
    size_t row_index = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char* token = strtok(buffer, ",");
        size_t col_index = 0;

        while (token != NULL) {
            size_t len = strlen(token);
            // Remove newline character if present
            if (len > 0 && token[len - 1] == '\n') {
                token[len - 1] = '\0';
            }

            // Allocate memory for the token
            (*data)->rows[row_index][col_index] = (char*)malloc((len + 1) * sizeof(char));
            if ((*data)->rows[row_index][col_index] == NULL) {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }

            // Copy the token to the ccsv structure
            strcpy((*data)->rows[row_index][col_index], token);

            token = strtok(NULL, ",");
            col_index++;
        }

        row_index++;
    }

    (*data)->num_rows = num_rows;
    (*data)->num_columns = num_columns;
} // end of func

// Function to update a specific cell in the ccsv structure
void  fscl_csv_parser_setter(ccsv** data, size_t row, size_t col, const char* update) {
    // Check if the provided indices are valid
    if (row < (*data)->num_rows && col < (*data)->num_columns) {
        // Free the existing content of the cell
        free((*data)->rows[row][col]);

        // Allocate memory for the updated content
        size_t len = strlen(update);
        (*data)->rows[row][col] = (char*)malloc((len + 1) * sizeof(char));
        if ((*data)->rows[row][col] == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        // Copy the updated content to the cell
        strcpy((*data)->rows[row][col], update);
    } else {
        fprintf(stderr, "Invalid row or column index\n");
    }
} // end of func

// Function to retrieve the content of a specific cell in the ccsv structure
const char*  fscl_csv_parser_getter(const ccsv* data, size_t row, size_t col) {
    // Check if the provided indices are valid
    if (row < data->num_rows && col < data->num_columns) {
        return data->rows[row][col];
    } else {
        fprintf(stderr, "Invalid row or column index\n");
        return NULL;
    }
} // end of func