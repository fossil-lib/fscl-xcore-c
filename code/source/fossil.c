/*  ----------------------------------------------------------------------------
    File: fossil.c

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
#include "trilobite/xcore/fossil.h"
#include <stdlib.h>
#include <string.h>

// Helper function to duplicate a string
char* dsl_duplicate_string(const char* source) {
    if (source == NULL) {
        return NULL;  // Handle NULL input
    }

    size_t length = strlen(source) + 1;  // Include space for the null terminator
    char* destination = (char*)malloc(length);

    if (destination != NULL) {
        strcpy(destination, source);
    }

    return destination;
}

// Helper function to check if a file has the .fossil extension
bool has_fossil_extension(const char* filename) {
    const char* extension = ".fossil";
    size_t len_filename = strlen(filename);
    size_t len_extension = strlen(extension);

    return (len_filename > len_extension) &&
           (strcmp(filename + len_filename - len_extension, extension) == 0);
}

// Helper function to check if a function call is in the list
bool is_function_called(const char* function_name, FunctionCall* calls, size_t call_count) {
    for (size_t i = 0; i < call_count; i++) {
        if (strcmp(calls[i].function_name, function_name) == 0) {
            return true;
        }
    }
    return false;
}

// Helper function to add a function call to the list
void add_function_call(const char* function_name, const char* return_type, FunctionCall** calls, size_t* call_count) {
    (*call_count)++;
    *calls = realloc(*calls, sizeof(FunctionCall) * (*call_count));
    (*calls)[*call_count - 1].function_name = dsl_duplicate_string(function_name);
    (*calls)[*call_count - 1].return_type = dsl_duplicate_string(return_type);
}

// Global variables to store parsed function and other state
static Function parsed_function;

// Gets the parsed function after calling fossil_dsl_parse.
Function fossil_dsl_get_parsed_function(void) {
    // Create a copy of the parsed function
    Function copy;
    copy.name = dsl_duplicate_string(parsed_function.name);

    if (parsed_function.param_count > 0) {
        copy.parameters = malloc(sizeof(Parameter) * parsed_function.param_count);
        for (size_t i = 0; i < parsed_function.param_count; ++i) {
            copy.parameters[i].name = dsl_duplicate_string(parsed_function.parameters[i].name);
            copy.parameters[i].type = dsl_duplicate_string(parsed_function.parameters[i].type);
        }
    } else {
        copy.parameters = NULL;
    }

    copy.param_count = parsed_function.param_count;
    copy.return_type = dsl_duplicate_string(parsed_function.return_type);

    return copy;
}

// Resets the internal state of the DSL parser.
void fossil_dsl_reset(void) {
    // Free memory of the parsed function
    free(parsed_function.name);
    parsed_function.name = NULL;

    if (parsed_function.param_count > 0) {
        for (size_t i = 0; i < parsed_function.param_count; ++i) {
            free(parsed_function.parameters[i].name);
            free(parsed_function.parameters[i].type);
        }
        free(parsed_function.parameters);
        parsed_function.parameters = NULL;
    }

    parsed_function.param_count = 0;

    free(parsed_function.return_type);
    parsed_function.return_type = NULL;
}

// DSL parser implementation
void fossil_dsl_parse(char* input) {
    Token* tokens;
    size_t token_count;

    fossil_dsl_tokenize(input, &tokens, &token_count);

    // Initialize function structure
    Function mainFunction;
    mainFunction.name = NULL;
    mainFunction.parameters = NULL;
    mainFunction.param_count = 0;
    mainFunction.return_type = NULL;

    // Initialize function call list
    FunctionCall* function_calls = NULL;
    size_t call_count = 0;

    size_t i = 0;
    while (i < token_count) {
        // Check for function name
        if (tokens[i].type == FSL_NAME && strcmp(tokens[i].value, "main") == 0) {
            mainFunction.name = dsl_duplicate_string(tokens[i].value);
            i++;
        } else if (tokens[i].type == FSL_KEYWORD && strcmp(tokens[i].value, "(") == 0) {
            // Parse parameters
            i++; // Move past '('
            while (i < token_count && tokens[i].type != FSL_KEYWORD && strcmp(tokens[i].value, ")") != 0) {
                if (tokens[i].type == FSL_NAME) {
                    mainFunction.param_count++;
                    mainFunction.parameters = realloc(mainFunction.parameters, sizeof(Parameter) * mainFunction.param_count);
                    mainFunction.parameters[mainFunction.param_count - 1].name = dsl_duplicate_string(tokens[i].value);
                    i++; // Move past parameter name

                    if (i < token_count && tokens[i].type == FSL_COLON) {
                        i++; // Move past ':'
                        if (i < token_count && tokens[i].type == FSL_TYPE) {
                            mainFunction.parameters[mainFunction.param_count - 1].type = dsl_duplicate_string(tokens[i].value);
                            i++; // Move past parameter type
                        } else {
                            // Handle error: Expected parameter type
                            fprintf(stderr, "Error: Expected parameter type.\n");
                            break;
                        }
                    } else {
                        // Handle error: Expected ':'
                        fprintf(stderr, "Error: Expected ':'.\n");
                        break;
                    }

                } else {
                    // Handle error: Expected parameter name
                    fprintf(stderr, "Error: Expected parameter name.\n");
                    break;
                }
            }

            // Move past ')'
            i++;

        } else if (tokens[i].type == FSL_ARROW) {
            // Parse return type
            i++; // Move past '->'
            if (i < token_count && tokens[i].type == FSL_TYPE) {
                mainFunction.return_type = dsl_duplicate_string(tokens[i].value);
                i++; // Move past return type
            } else {
                // Handle error: Expected return type
                fprintf(stderr, "Error: Expected return type.\n");
                break;
            }
        } else if (tokens[i].type == FSL_NAME) {
            // Check for function calls and add to the list
            if (is_function_called(tokens[i].value, function_calls, call_count)) {
                // Function is already in the list
                i++;
                continue;
            }

            add_function_call(tokens[i].value, "unknown", &function_calls, &call_count);
            i++;
        } else {
            // Skip other tokens
            i++;
        }
    }

    // Print only the functions that are called from main
    for (size_t j = 0; j < call_count; j++) {
        for (size_t k = 0; k < token_count; k++) {
            if (tokens[k].type == FSL_NAME && strcmp(tokens[k].value, function_calls[j].function_name) == 0) {
                fossil_dsl_print_function(&mainFunction);
                break;
            }
        }
    }

    // Free memory
    fossil_dsl_erase_function(&mainFunction);
    fossil_dsl_erase_function_calls(function_calls, call_count);
    fossil_dsl_erase_tokens(tokens, token_count);
}

// Function to free allocated memory for a function
void fossil_dsl_erase_function(Function* func) {
    free(func->name);
    for (size_t i = 0; i < func->param_count; i++) {
        free(func->parameters[i].name);
        free(func->parameters[i].type);
    }
    free(func->parameters);
    free(func->return_type);
}

// Function to print a parsed function
void fossil_dsl_print_function(Function* func) {
    printf("Function Name: %s\n", func->name);
    printf("Parameters:\n");
    for (int i = 0; i < func->param_count; i++) {
        printf("  Parameter %d: Name=%s, Type=%s\n", (int)i + (int)1, func->parameters[i].name, func->parameters[i].type);
    }
    printf("Return Type: %s\n", func->return_type);
    printf("\n");
}

// Tokenization function
void fossil_dsl_tokenize(char* input, Token** tokens, size_t* token_count) {
    const char* delimiters = " \t\n";
    const char* comment_start = "/*";
    const char* comment_end = "*/";

    // Tokenize the input string
    char* token_str = strtok(input, delimiters);
    *tokens = NULL;
    *token_count = 0;

    while (token_str != NULL) {
        // Check for comments
        if (strstr(token_str, comment_start) != NULL) {
            // Skip until the end of the comment
            while (token_str != NULL && strstr(token_str, comment_end) == NULL) {
                token_str = strtok(NULL, delimiters);
            }
            // If the comment end is found, move to the next token
            if (token_str != NULL) {
                token_str = strtok(NULL, delimiters);
                continue;
            }
        }

        (*token_count)++;
        *tokens = realloc(*tokens, sizeof(Token) * (*token_count));

        // Determine the token type based on the keyword
        if (strcmp(token_str, "fossil") == 0) {
            (*tokens)[*token_count - 1].type = FSL_KEYWORD;
        } else if (strcmp(token_str, "->") == 0) {
            (*tokens)[*token_count - 1].type = FSL_ARROW;
        } else if (strcmp(token_str, "unit") == 0 || strcmp(token_str, "void") == 0) {
            (*tokens)[*token_count - 1].type = FSL_UNIT;
        } else if (strcmp(token_str, ":") == 0) {
            (*tokens)[*token_count - 1].type = FSL_COLON;
        } else if (strcmp(token_str, "int") == 0 || strcmp(token_str, "uint") == 0 || strcmp(token_str, "unsigned") == 0) {
            (*tokens)[*token_count - 1].type = FSL_TYPE;
            (*tokens)[*token_count - 1].value = dsl_duplicate_string(token_str);
        } else if (strcmp(token_str, "string") == 0 || strcmp(token_str, "char") == 0) {
            (*tokens)[*token_count - 1].type = FSL_TYPE;
            (*tokens)[*token_count - 1].value = dsl_duplicate_string(token_str);
        } else if (strcmp(token_str, "(") == 0) {
            (*tokens)[*token_count - 1].type = FSL_KEYWORD; // Opening parenthesis
        } else if (strcmp(token_str, ")") == 0) {
            (*tokens)[*token_count - 1].type = FSL_KEYWORD; // Closing parenthesis
        } else {
            // Assume it's a function name or some other identifier
            (*tokens)[*token_count - 1].type = FSL_NAME;
            (*tokens)[*token_count - 1].value = dsl_duplicate_string(token_str);
        }

        token_str = strtok(NULL, delimiters);
    }
}

// Function to free allocated memory for tokens
void fossil_dsl_erase_tokens(Token* tokens, size_t token_count) {
    for (size_t i = 0; i < token_count; i++) {
        if (tokens[i].type == FSL_TYPE || tokens[i].type == FSL_NAME) {
            free(tokens[i].value);
        }
    }

    free(tokens);
}

// Function to free allocated memory for function calls
void fossil_dsl_erase_function_calls(FunctionCall* calls, size_t call_count) {
    for (size_t i = 0; i < call_count; i++) {
        free(calls[i].function_name);
        free(calls[i].return_type);
    }
    free(calls);
}

// Function to load a custom library and add function calls to the list
void fossil_dsl_load_library(const char* library_name, FunctionCall** calls, size_t* call_count) {
    // This is a placeholder function; you can extend it to load custom libraries
    // and add functions to the list based on the library content.
    // For simplicity, we'll add a sample library with a function called "libraryFunction".

    if (strcmp(library_name, "sample") == 0) {
        add_function_call("libraryFunction", "unknown", calls, call_count);
    } else {
        fprintf(stderr, "Error: Unknown library '%s'.\n", library_name);
    }
}
