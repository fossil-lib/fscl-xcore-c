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

// =================================================================
// // Function to execute the DSL script based on the AST
// void fscl_fossil_execute_script(ASTNode* root) {
//     // Implementation of script execution logic
//     // This will depend on the DSL semantics and how you want to interpret the AST
//     // You may need to traverse the AST and execute corresponding actions for each node
//     // You might use other helper functions for specific actions
//
//     if (root == NULL || root->error_flag) {
//         return;
//     }
//
//     // Execute actions based on the root node type
//     switch (root->type) {
//         case PLACEHOLDER_NODE:
//             // Placeholder node, no action needed
//             break;
//         case FUNCTION:
//             // Execute function logic
//             printf("Executing function: %s\n", root->value);
//             // Add function execution logic here
//             break;
//         case CLASS:
//             // Execute class logic
//             printf("Executing class: %s\n", root->value);
//             // Add class execution logic here
//             break;
//         default:
//             // Handle other node types as needed
//             break;
//     }
//
//     // Recursively execute actions for children
//     for (size_t i = 0; i < root->num_children; ++i) {
//         fscl_fossil_execute_script(root->children[i]);
//     }
// }
//
// int main() {
//     // Parse DSL file and get AST
//     ASTNode* ast = fscl_fossil_parse_dsl_file("example.dsl");
//
//     if (ast != NULL) {
//         // Print the AST
//         fscl_fossil_print_ast(ast, 0);
//
//         // Execute the DSL script based on the AST
//         fscl_fossil_execute_script(ast);
//
//         // Erase the AST to free memory
//         fscl_fossil_erase_node(ast);
//     } else {
//         // Print parsing error message
//         printf("Parsing Error: %s\n", getParseErrorMessage());
//     }
//
//     return 0;
// }
// =================================================================

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

// Enumeration for node types
typedef enum {
    MAIN_FUNCTION_TYPE,
    CLASS_DECLARATION_TYPE,
    METHOD_DECLARATION_TYPE,
    IDENTIFIER_TYPE,
    PRINT_STATEMENT_TYPE,
    STRING_LITERAL_TYPE,
    LINK_STATEMENT_TYPE,
    IMPORT_STATEMENT_TYPE,
    TAPE_PROGRAM_TYPE,
    PROJECT_STATEMENT_TYPE,
    STATEMENT_TYPE,
    ACTION_STATEMENT_TYPE,
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
    PLACEHOLDER_NODE,
    PUBLIC,   // New: Public member visibility
    PRIVATE,  // New: Private member visibility
    INHERITANCE,      // New: Inheritance
    ENCAPSULATION     // New: Encapsulation
} NodeType;

// Enumeration for data types
typedef enum {
    INT,
    INT8,
    INT16,
    INT32,
    INT64,
    UINT,
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
    NULL_TYPE,
    PLACEHOLDER,
    DATETIME,      // New: Datetime type
    COMEDY_ERROR,  // New: Comedy error type
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
    int is_public;
    struct ASTNode** children;
    size_t num_children;
    struct ASTNode** public_members;
    struct ASTNode** private_members;
    size_t num_public_members;
    size_t num_private_members;
    struct ASTNode* parent_class;  // For INHERITANCE
    size_t encapsulated_member_index;  // For ENCAPSULATION
} ASTNode;

// Define ParseError type
typedef enum {
    NO_ERROR,
    UNKNOWN_KEYWORD_ERROR,
    PARSING_ERROR,
    // Add more error types as needed
} ParseError;

// Global variables for custom names
extern char OPEN_BRACE_KEYWORD;
extern char CLOSE_BRACE_KEYWORD;
extern char* FUNCTION_KEYWORD;

// =================================================================
// DSL functions
// =================================================================

// Function to read the content of a DSL file
char* fscl_fossil_read_dsl(const char* filename);

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

// Function to create a new variable node with visibility
ASTNode* fscl_fossil_create_variable_with_visibility(DataType data_type, char* variable_name, int is_public);

// Function to create a new constant node with DATETIME type
ASTNode* fscl_fossil_create_datetime_constant(char* datetime_value);

// Function to create a new variable node
ASTNode* fscl_fossil_create_variable(DataType data_type, char* variable_name);

// Function to create a new function node
ASTNode* fscl_fossil_create_function(DataType return_type, char* function_name);

// Function to create a new constant node
ASTNode* fscl_fossil_create_constant(DataType data_type, char* constant_value);

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

// Function to skip whitespace in the code
void fscl_fossil_skip_whitespace(const char* code, size_t* index);

// Function to parse an identifier in the code
char* fscl_fossil_parse_identifier(const char* code, size_t* index);

// Function to parse a data type in the code
DataType fscl_fossil_parse_data_type(const char* code, size_t* index);

// Function to parse a statement into ASTNode
ASTNode* fscl_fossil_parse_statement(const char* statement);

// Function to parse a function declaration
ASTNode* fscl_fossil_parse_function_declaration(const char* code, size_t* index, const char* entryPoint);

// Function to create a new class node with details
ASTNode* fscl_fossil_create_class(char* class_name);

// Function to add a member to a class with visibility and details
void fscl_fossil_add_class_member(ASTNode* classNode, ASTNode* member, int is_public);

// Function to parse a class declaration
ASTNode* fscl_fossil_parse_class_declaration(const char* code, size_t* index);

// Function to parse a DSL file into an AST
ASTNode* fscl_fossil_parse_dsl_file(const char* filename);

#ifdef __cplusplus
}
#endif

#endif
