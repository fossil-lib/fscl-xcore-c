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
#ifndef FSCL_FOSSIL_H
#define FSCL_FOSSIL_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Basic DSL Node Types
typedef enum {
    DSL_NODE_CONSTANT,
    DSL_NODE_VARIABLE,
    DSL_NODE_ASSIGNMENT,
    DSL_NODE_BINARY_OPERATION,
    DSL_NODE_SWITCH,
    DSL_NODE_TRY_CATCH,
    DSL_NODE_ARRAY,
    DSL_NODE_STRUCT,
    DSL_NODE_ENUM,
    DSL_NODE_CONCURRENT,
    DSL_NODE_LAMBDA,
    DSL_NODE_PATTERN_MATCHING,
    DSL_NODE_ERROR_HANDLING,
    DSL_NODE_OPTIMIZATION,
    DSL_NODE_DOCUMENTATION,
    DSL_NODE_UNIT_TEST,
    DSL_NODE_INTEROPERABILITY,
    DSL_NODE_DEBUGGING,
    DSL_NODE_CODE_PROFILING,
    DSL_NODE_USER_INTERFACE,
    DSL_NODE_MAIN,
    DSL_NODE_INCLUDE,
    DSL_NODE_BOOL  // New node type for boolean values
    // Add more node types as needed
} DSLNodeType;

// DSL Node Structure
typedef struct DSLNode {
    DSLNodeType type;
    union {
        int constant_value;
        char* variable_name;
        struct {
            char* variable_name;
            struct DSLNode* expression;
        } assignment;
        struct {
            char operator;
            struct DSLNode* left;
            struct DSLNode* right;
        } binary_operation;
        struct {
            struct DSLNode* expression;
            struct DSLNode* cases;
            struct DSLNode* default_case;
        } switch_node;
        struct {
            struct DSLNode* try_block;
            struct DSLNode* catch_block;
        } try_catch_node;
        struct {
            struct DSLNode* elements;
        } array_node;
        struct {
            char* struct_name;
            struct DSLNode* fields;
        } struct_node;
        struct {
            char* enum_name;
            struct DSLNode* values;
        } enum_node;
        // Add more node structures for new features
        struct {
            struct DSLNode* body;
        } main_node;
        struct {
            char* filename;
        } include_node;
        struct {
            int bool_value;
        } bool_node;
    } data;
    struct DSLNode* next;
    // Add introspection or other necessary fields
} DSLNode;

// =================================================================
// DSL functions
// =================================================================

// Create DSL Node Functions
DSLNode* fscl_fossil_create_constant_node(int value);
DSLNode* fscl_fossil_create_variable_node(const char* name, DSLNode* next);
DSLNode* fscl_fossil_create_assignment_node(const char* variable_name, DSLNode* expression);
DSLNode* fscl_fossil_create_binary_operation_node(char operator, DSLNode* left, DSLNode* right);
DSLNode* fscl_fossil_create_switch_node(DSLNode* expression, DSLNode* cases, DSLNode* default_case);
DSLNode* fscl_fossil_create_try_catch_node(DSLNode* try_block, DSLNode* catch_block);
DSLNode* fscl_fossil_create_array_node(DSLNode* elements);
DSLNode* fscl_fossil_create_struct_node(const char* struct_name, DSLNode* fields);
DSLNode* fscl_fossil_create_enum_node(const char* enum_name, DSLNode* values);
DSLNode* fscl_fossil_create_main_node(DSLNode* body);
DSLNode* fscl_fossil_create_include_node(const char* filename);
DSLNode* fscl_fossil_create_bool_node(int bool_value);  // New function for creating boolean nodes

// Execution and Evaluation Functions
int fscl_fossil_evaluate(DSLNode* node);
void fscl_fossil_serialize_to_tape_file(DSLNode* root, const char* filename);
void fscl_fossil_execute_tape_file(const char* filename);

// Introspection Functions
void fscl_fossil_introspect_dsl(DSLNode* node, int depth);

// Freeing DSL Nodes
void fscl_fossil_free_dsl_nodes(DSLNode* node);

// Helper Functions
DSLNode* fscl_fossil_create_sequence_node(DSLNode* first, ...);
void fscl_fossil_print_indent(int depth);

#ifdef __cplusplus
}
#endif

#endif
