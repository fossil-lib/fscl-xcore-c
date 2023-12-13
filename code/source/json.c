/*  ----------------------------------------------------------------------------
    File: json.c

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
#include "trilobite/xcore/json.h"
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
            json_parser_setter(data, "");
            json_parser_get_object(data)->numPairs = object.numPairs;
            json_parser_get_object(data)->pairs = object.pairs;
            return 1; // Success
        }
    } else if (*ptr == '[') {
        // JSON Array
        cjson_array array = {NULL, 0};
        if (parse_array(&ptr, &array)) {
            json_parser_setter(data, "");
            json_parser_get_array(data)->numItems = array.numItems;
            json_parser_get_array(data)->items = array.items;
            return 1; // Success
        }
    }

    return 0; // Parsing failure
}

cjson* json_parser_create() {
    cjson* data = (cjson*)malloc(sizeof(cjson));
    if (data == NULL) {
        perror("Error creating cjson");
        return NULL;
    }

    data->json_data = NULL;
    return data;
}

void json_parser_erase(cjson** data) {
    if (data != NULL && *data != NULL) {
        json_parser_erase_meta(data);
        free(*data);
        *data = NULL;
    }
}

int json_parser_parse(FILE* file, cjson** data) {
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

void json_parser_setter(cjson** data, const char* update) {
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

const char* json_parser_getter(cjson** data) {
    if (data != NULL && *data != NULL) {
        return (*data)->json_data;
    }
    return NULL;
}

void json_parser_erase_meta(cjson** data) {
    if (data != NULL && *data != NULL) {
        free((*data)->json_data);
        (*data)->json_data = NULL;
    }
}

cjson_object* json_parser_get_object(cjson** data) {
    if (data != NULL && *data != NULL) {
        return (cjson_object*)((*data)->json_data);
    }
    return NULL;
}

cjson_array* json_parser_get_array(cjson** data) {
    if (data != NULL && *data != NULL) {
        return (cjson_array*)((*data)->json_data);
    }
    return NULL;
} // end of func
