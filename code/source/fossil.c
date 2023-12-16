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

// Initialize the DSL with a tape file
void fossil_dsl_create(FossilDSL *dsl, const char *tape_filename) {
    dsl->tape_file = fopen(tape_filename, "w");
    if (!dsl->tape_file) {
        dsl->error_code = EXIT_FAILURE;
        snprintf(dsl->error_message, sizeof(dsl->error_message), "Error opening tape file");
        return;
    }
    dsl->error_code = 0;
    dsl->error_message[0] = '\0';
    dsl->indentation_level = 0;
    dsl->debug_enabled = 0; // Debugging is disabled by default
}

// Helper function to add indentation based on the current level
void fossil_dsl_indent(FossilDSL *dsl) {
    for (int i = 0; i < dsl->indentation_level; ++i) {
        fprintf(dsl->tape_file, "    ");
    }
}

// Add a debugging statement to the tape
void fossil_dsl_debug(FossilDSL *dsl, const char *message) {
    if (dsl->debug_enabled) {
        fossil_dsl_indent(dsl);
        fprintf(dsl->tape_file, "DEBUG \"%s\"\n", message);
    }
}

// Enable debugging in the DSL
void fossil_dsl_enable_debug(FossilDSL *dsl) {
    dsl->debug_enabled = 1;
}

// Add a condition header to the tape
void fossil_dsl_add_condition_header(FossilDSL *dsl, FossilDSLValue condition, const char *true_branch, const char *false_branch) {
    fossil_dsl_indent(dsl);
    fprintf(dsl->tape_file, "CONDITION ");

    switch (condition.type) {
        case INTEGER:
            fprintf(dsl->tape_file, "INT %d", condition.int_value);
            break;
        case UNSIGNED_INT:
            fprintf(dsl->tape_file, "UINT %u", condition.unsigned_int_value);
            break;
        case FLOAT:
            fprintf(dsl->tape_file, "FLOAT %f", condition.float_value);
            break;
        case CHAR:
            fprintf(dsl->tape_file, "CHAR %c", condition.char_value);
            break;
        case STRING:
            fprintf(dsl->tape_file, "STRING %s", condition.string_value);
            break;
        case TOFU:
            fprintf(dsl->tape_file, "TOFU %p", condition.tofu_value);
            break;
        case NULL_TYPE:
            fprintf(dsl->tape_file, "NULL %d", condition.null_type);
            break;
        case BOOL:
            fprintf(dsl->tape_file, "BOOL %s", condition.bool_value ? "TRUE" : "FALSE");
            break;
        case ARRAY:
            fprintf(dsl->tape_file, "ARRAY { ");
            for (int i = 0; i < DSL_ARRAY_SIZE; ++i) {
                fprintf(dsl->tape_file, "%d", condition.array[i]);
                if (i < DSL_ARRAY_SIZE - 1) {
                    fprintf(dsl->tape_file, ", ");
                }
            }
            fprintf(dsl->tape_file, " }");
            break;
    }

    fprintf(dsl->tape_file, " THEN %s ELSE %s START\n", true_branch, false_branch);
    dsl->indentation_level++;
}

// Add a condition statement to the tape
void fossil_dsl_add_condition(FossilDSL *dsl, FossilDSLValue condition, const char *true_branch, const char *false_branch) {
    fossil_dsl_add_condition_header(dsl, condition, true_branch, false_branch);
}

// Add a function definition to the tape
void fossil_dsl_add_function(FossilDSL *dsl, const char *func_name) {
    fossil_dsl_debug(dsl, "Entering function");
    fossil_dsl_indent(dsl);
    fprintf(dsl->tape_file, "FUNCTION %s()\n", func_name);
    dsl->indentation_level++;
}

// Helper function to print a value based on its type
void fossil_dsl_print_value(FILE *tape_file, FossilDSLValue value) {
    switch (value.type) {
        case INTEGER:
            fprintf(tape_file, "INT %d", value.int_value);
            break;
        case UNSIGNED_INT:
            fprintf(tape_file, "UINT %u", value.unsigned_int_value);
            break;
        case FLOAT:
            fprintf(tape_file, "FLOAT %f", value.float_value);
            break;
        case CHAR:
            fprintf(tape_file, "CHAR %c", value.char_value);
            break;
        case STRING:
            fprintf(tape_file, "STRING %s", value.string_value);
            break;
        case TOFU:
            fprintf(tape_file, "TOFU %p", value.tofu_value);
            break;
        case NULL_TYPE:
            fprintf(tape_file, "NULL %d", value.null_type);
            break;
        case BOOL:
            fprintf(tape_file, "BOOL %s", value.bool_value? "TRUE" : "FALSE");
            break;
        case ARRAY:
            fprintf(tape_file, "ARRAY { ");
            for (int i = 0; i < DSL_ARRAY_SIZE; ++i) {
                fprintf(tape_file, "%d", value.array[i]);
                if (i < DSL_ARRAY_SIZE - 1) {
                    fprintf(tape_file, ", ");
                }
            }
            fprintf(tape_file, " }");
            break;
    }
}

// Helper function to add a binary operation to the tape
void fossil_dsl_add_binary_operation(FossilDSL *dsl, const char *operation, const char *type, FossilDSLValue operand1, FossilDSLValue operand2) {
    fossil_dsl_indent(dsl);
    fprintf(dsl->tape_file, "%s_%s(", operation, type);
    fossil_dsl_print_value(dsl->tape_file, operand1);
    fprintf(dsl->tape_file, ", ");
    fossil_dsl_print_value(dsl->tape_file, operand2);
    fprintf(dsl->tape_file, ")\n");
}

// Add a bitwise operation to the tape
void fossil_dsl_add_bitwise_operation(FossilDSL *dsl, const char *operation, FossilDSLValue operand1, FossilDSLValue operand2) {
    fossil_dsl_add_binary_operation(dsl, "BITWISE", operation, operand1, operand2);
}

// Add a loop header to the tape
void fossil_dsl_add_loop_header(FossilDSL *dsl, const char *loop_variable, int start_value, int end_value) {
    fossil_dsl_indent(dsl);
    fprintf(dsl->tape_file, "LOOP %s FROM %d TO %d START\n", loop_variable, start_value, end_value);
    dsl->indentation_level++;
}

// Add a loop to the tape
void fossil_dsl_add_loop(FossilDSL *dsl, const char *loop_variable, int start_value, int end_value) {
    fossil_dsl_add_loop_header(dsl, loop_variable, start_value, end_value);
}

// Helper function to close the current block in the tape
void fossil_dsl_close_block(FossilDSL *dsl) {
    dsl->indentation_level--;
    fossil_dsl_indent(dsl);
    fprintf(dsl->tape_file, "END\n");
}

// Finalize and close the tape file
void fossil_dsl_erase(FossilDSL *dsl) {
    fossil_dsl_debug(dsl, "End of program");
    if (dsl->tape_file) {
        fclose(dsl->tape_file);
    }
}
