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
#include <string.h>
#include <stdarg.h>

// Enumeration for node types
typedef enum {
    VARIABLE,
    CONSTANT,
    FUNCTION,
    CLASS,
    STRUCT,
    UNARY_OP,
    RELATIONAL_OP,
    LOGICAL_OP,
    IF_STATEMENT,
    WHILE_LOOP,
    INCLUDE_FILE,
    LINK_LIBRARY,
    PLACEHOLDER_NODE   // New: Placeholder node type
} NodeType;

// Enumeration for data types
typedef enum {
    INT8,
    INT16,
    INT32,
    INT64,
    UINT8,
    UINT16,
    UINT32,
    UINT64,
    FLOAT,
    STRING,
    ARRAY,
    MAP,
    BOOL,
    TOFU,
    CHAR,
    HEX,
    OCT,
    NULL_TYPE,      // New: Null type
    PLACEHOLDER,    // New: Placeholder type
    ERROR
} DataType;

// Enumeration for operator types
typedef enum {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    NEGATION,
    INCREMENT,
    DECREMENT,
    EQUALS,
    NOT_EQUALS,
    LESS_THAN,
    GREATER_THAN,
    AND,
    OR
} OperatorType;

// Structure for AST nodes
typedef struct ASTNode {
    NodeType type;
    DataType data_type;
    OperatorType operator_type;
    char* value;
    int error_flag;
    struct ASTNode** children;
    size_t num_children;
} ASTNode;

// =================================================================
// DSL functions
// =================================================================

// Function to create a new AST node
ASTNode* fscl_fossil_create_node(NodeType type, DataType data_type, OperatorType operator_type, char* value);

// Function to add a child to an AST node
void fscl_fossil_add_child(ASTNode* parent, ASTNode* child);

// Function to add multiple children to an AST node
void fscl_fossil_add_children(ASTNode* parent, size_t num_children, ...);

// Function to print the AST in a readable format
void fscl_fossil_print_ast(ASTNode* root, int depth);

// Function to erase an AST node and its children
void fscl_fossil_erase_node(ASTNode* node);

// Function to create a new variable node
ASTNode* fscl_fossil_create_variable(DataType data_type, char* variable_name);

// Function to create a new constant node
ASTNode* fscl_fossil_create_constant(DataType data_type, char* constant_value);

// Function to create a new function node
ASTNode* fscl_fossil_create_function(DataType return_type, char* function_name);

// Function to create a new unary operation node
ASTNode* fscl_fossil_create_unary_op(DataType data_type, OperatorType operator_type, char* operand_value);

// Function to create a new relational operation node
ASTNode* fscl_fossil_create_relational_op(DataType data_type, OperatorType operator_type, char* operand_value);

// Function to create a new logical operation node
ASTNode* fscl_fossil_create_logical_op(DataType data_type, OperatorType operator_type, char* operand_value);

// Function to create a new if statement node
ASTNode* fscl_fossil_create_if_statement(char* condition_value);

// Function to create a new while loop node
ASTNode* fscl_fossil_create_while_loop(char* condition_value);

// Function to create a new include file node
ASTNode* fscl_fossil_create_include_file(char* file_name);

// Function to create a new link library node
ASTNode* fscl_fossil_create_link_library(char* library_name);

// Function to parse declarations from a file and add them to the AST
void fscl_fossil_parse_declarations_from_file(const char* filename, ASTNode* root);

// Function to process a DSL file and return the AST rooted at the entry point
ASTNode* fscl_fossil_process_dsl_file(const char* filename, const char* entryPoint);

#ifdef __cplusplus
}
#endif

#endif
