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
#include "fossil/xcore/fossil.h"
#include <stdlib.h>
#include <string.h>

// Initialize the DSL with a tape file
void  fscl_fossil_dsl_create(FossilDSL *dsl, const char *tape_filename) {
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
void  fscl_fossil_dsl_indent(FossilDSL *dsl) {
    for (int i = 0; i < dsl->indentation_level; ++i) {
        fprintf(dsl->tape_file, "    ");
    }
}

// Add a debugging statement to the tape
void  fscl_fossil_dsl_debug(FossilDSL *dsl, const char *message) {
    if (dsl->debug_enabled) {
         fscl_fossil_dsl_indent(dsl);
        fprintf(dsl->tape_file, "DEBUG \"%s\"\n", message);
    }
}

// Enable debugging in the DSL
void  fscl_fossil_dsl_enable_debug(FossilDSL *dsl) {
    dsl->debug_enabled = 1;
}

// Add a condition header to the tape
void  fscl_fossil_dsl_add_condition_header(FossilDSL *dsl, FossilDSLValue condition, const char *true_branch, const char *false_branch) {
     fscl_fossil_dsl_indent(dsl);
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
            fprintf(dsl->tape_file, "NULL %p", condition.null_type);
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
void  fscl_fossil_dsl_add_condition(FossilDSL *dsl, FossilDSLValue condition, const char *true_branch, const char *false_branch) {
     fscl_fossil_dsl_add_condition_header(dsl, condition, true_branch, false_branch);
}

// Call a function in the tape
void  fscl_fossil_dsl_call_function(FossilDSL *dsl, const char *func_name, FossilDSLValue *arguments, int num_arguments) {
    // Check for valid arguments and handle the function call
    if (dsl == NULL || func_name == NULL) {
        fprintf(stderr, "Error: Invalid arguments for function call\n");
        return;
    }

    // Print the function call to the tape
    fprintf(dsl->tape_file, "%s(", func_name);

    // Print function arguments
    for (int i = 0; i < num_arguments; ++i) {
         fscl_fossil_dsl_print_value(dsl->tape_file, arguments[i]);

        // Add a comma for multiple arguments
        if (i < num_arguments - 1) {
            fprintf(dsl->tape_file, ", ");
        }
    }

    // Close the function call
    fprintf(dsl->tape_file, "):\n");

    // Add indentation for the function block
     fscl_fossil_dsl_indent(dsl);
}

// Add a function definition to the tape
void  fscl_fossil_dsl_add_function(FossilDSL *dsl, const char *func_name) {
     fscl_fossil_dsl_debug(dsl, "Entering function");
     fscl_fossil_dsl_indent(dsl);
    fprintf(dsl->tape_file, "FUNCTION %s()\n", func_name);
    dsl->indentation_level++;
}

// Helper function to print a value based on its type
void  fscl_fossil_dsl_print_value(FILE *tape_file, FossilDSLValue value) {
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
            fprintf(tape_file, "NULL %p", value.null_type);
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
void  fscl_fossil_dsl_add_binary_operation(FossilDSL *dsl, const char *operation, const char *type, FossilDSLValue operand1, FossilDSLValue operand2) {
     fscl_fossil_dsl_indent(dsl);
    fprintf(dsl->tape_file, "%s_%s(", operation, type);
     fscl_fossil_dsl_print_value(dsl->tape_file, operand1);
    fprintf(dsl->tape_file, ", ");
     fscl_fossil_dsl_print_value(dsl->tape_file, operand2);
    fprintf(dsl->tape_file, ")\n");
}

// Add a bitwise operation to the tape
void  fscl_fossil_dsl_add_bitwise_operation(FossilDSL *dsl, const char *operation, FossilDSLValue operand1, FossilDSLValue operand2) {
     fscl_fossil_dsl_add_binary_operation(dsl, "BITWISE", operation, operand1, operand2);
}

// Add a loop header to the tape
void  fscl_fossil_dsl_add_loop_header(FossilDSL *dsl, const char *loop_variable, int start_value, int end_value) {
     fscl_fossil_dsl_indent(dsl);
    fprintf(dsl->tape_file, "LOOP %s FROM %d TO %d START\n", loop_variable, start_value, end_value);
    dsl->indentation_level++;
}

// Add a loop to the tape
void  fscl_fossil_dsl_add_loop(FossilDSL *dsl, const char *loop_variable, int start_value, int end_value) {
     fscl_fossil_dsl_add_loop_header(dsl, loop_variable, start_value, end_value);
}

// Helper function to close the current block in the tape
void  fscl_fossil_dsl_close_block(FossilDSL *dsl) {
    dsl->indentation_level--;
     fscl_fossil_dsl_indent(dsl);
    fprintf(dsl->tape_file, "END\n");
}

// Finalize and close the tape file
void  fscl_fossil_dsl_erase(FossilDSL *dsl) {
     fscl_fossil_dsl_debug(dsl, "End of program");
    if (dsl->tape_file) {
        fclose(dsl->tape_file);
    }
}
