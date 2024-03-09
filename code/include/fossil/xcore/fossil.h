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
    FOSSIL_INT,
    FOSSIL_INT8,
    FOSSIL_INT16,
    FOSSIL_INT32,
    FOSSIL_INT64,
    FOSSIL_UINT,
    FOSSIL_UINT8,
    FOSSIL_UINT16,
    FOSSIL_UINT32,
    FOSSIL_UINT64,
    FOSSIL_FLOAT,
    FOSSIL_STRING,
    FOSSIL_ARRAY,
    FOSSIL_MAP,
    FOSSIL_BOOL,
    FOSSIL_TOFU,
    FOSSIL_CHAR,
    FOSSIL_HEX,
    FOSSIL_OCT,
    FOSSIL_NULL_TYPE,
    FOSSIL_PLACEHOLDER,
    FOSSIL_DATETIME,      // New: Datetime type
    FOSSIL_COMEDY_ERROR,  // New: Comedy error type
    FOSSIL_ERROR
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
    NO_ERRORS,
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

/**
 * Read the content of a DSL file and return it as a string.
 *
 * @param filename The name of the DSL file to be read.
 * @return         A dynamically allocated string containing the file content.
 */
char* fscl_fossil_read_dsl(const char* filename);

/**
 * Create a new AST node with specified attributes.
 *
 * @param type          The type of the AST node.
 * @param data_type     The data type associated with the node.
 * @param operator_type The operator type for operator nodes.
 * @param value         The value associated with the node.
 * @return              A pointer to the created AST node.
 */
ASTNode* fscl_fossil_create_node(NodeType type, DataType data_type, OperatorType operator_type, char* value);

/**
 * Add a child node to the specified parent AST node.
 *
 * @param parent The parent AST node.
 * @param child  The child AST node to be added.
 */
void fscl_fossil_add_child(ASTNode* parent, ASTNode* child);

/**
 * Add multiple children to the specified parent AST node.
 *
 * @param parent       The parent AST node.
 * @param num_children The number of children to be added.
 * @param ...          Variable arguments representing the child nodes.
 */
void fscl_fossil_add_children(ASTNode* parent, size_t num_children, ...);

/**
 * Print the AST in a readable format with specified depth.
 *
 * @param root  The root AST node.
 * @param depth The initial depth for indentation.
 */
void fscl_fossil_print_ast(ASTNode* root, int depth);

/**
 * Erase an AST node and its children from memory.
 *
 * @param node The AST node to be erased.
 */
void fscl_fossil_erase_node(ASTNode* node);

/**
 * Create a new variable node with visibility attribute.
 *
 * @param data_type     The data type associated with the variable.
 * @param variable_name The name of the variable.
 * @param is_public     Visibility attribute indicating public or private.
 * @return              A pointer to the created variable node.
 */
ASTNode* fscl_fossil_create_variable_with_visibility(DataType data_type, char* variable_name, int is_public);

/**
 * Create a new constant node with DATETIME type.
 *
 * @param datetime_value The value associated with the DATETIME constant.
 * @return               A pointer to the created DATETIME constant node.
 */
ASTNode* fscl_fossil_create_datetime_constant(char* datetime_value);

/**
 * Create a new variable node.
 *
 * @param data_type     The data type associated with the variable.
 * @param variable_name The name of the variable.
 * @return              A pointer to the created variable node.
 */
ASTNode* fscl_fossil_create_variable(DataType data_type, char* variable_name);

/**
 * Create a new function node.
 *
 * @param return_type   The return data type of the function.
 * @param function_name The name of the function.
 * @return              A pointer to the created function node.
 */
ASTNode* fscl_fossil_create_function(DataType return_type, char* function_name);

/**
 * Create a new constant node.
 *
 * @param data_type      The data type associated with the constant.
 * @param constant_value The value associated with the constant.
 * @return               A pointer to the created constant node.
 */
ASTNode* fscl_fossil_create_constant(DataType data_type, char* constant_value);

/**
 * Create a new unary operation node.
 *
 * @param data_type     The data type associated with the operation.
 * @param operator_type The type of unary operator.
 * @param operand_value The value of the operand.
 * @return              A pointer to the created unary operation node.
 */
ASTNode* fscl_fossil_create_unary_op(DataType data_type, OperatorType operator_type, char* operand_value);

/**
 * Create a new relational operation node.
 *
 * @param data_type     The data type associated with the operation.
 * @param operator_type The type of relational operator.
 * @param operand_value The value of the operand.
 * @return              A pointer to the created relational operation node.
 */
ASTNode* fscl_fossil_create_relational_op(DataType data_type, OperatorType operator_type, char* operand_value);

/**
 * Create a new logical operation node.
 *
 * @param data_type     The data type associated with the operation.
 * @param operator_type The type of logical operator.
 * @param operand_value The value of the operand.
 * @return              A pointer to the created logical operation node.
 */
ASTNode* fscl_fossil_create_logical_op(DataType data_type, OperatorType operator_type, char* operand_value);

/**
 * Create a new if statement node with a specified condition.
 *
 * @param condition_value The value of the condition for the if statement.
 * @return                A pointer to the created if statement node.
 */
ASTNode* fscl_fossil_create_if_statement(char* condition_value);

/**
 * Create a new while loop node with a specified condition.
 *
 * @param condition_value The value of the condition for the while loop.
 * @return                A pointer to the created while loop node.
 */
ASTNode* fscl_fossil_create_while_loop(char* condition_value);

/**
 * Create a new include file node with the specified file name.
 *
 * @param file_name The name of the file to be included.
 * @return          A pointer to the created include file node.
 */
ASTNode* fscl_fossil_create_include_file(char* file_name);

/**
 * Create a new link library node with the specified library name.
 *
 * @param library_name The name of the library to be linked.
 * @return             A pointer to the created link library node.
 */
ASTNode* fscl_fossil_create_link_library(char* library_name);

/**
 * Skip whitespace in the code by updating the index.
 *
 * @param code  The code string to skip whitespace in.
 * @param index Pointer to the index in the code string.
 */
void fscl_fossil_skip_whitespace(const char* code, size_t* index);

/**
 * Parse an identifier in the code and update the index.
 *
 * @param code  The code string to parse.
 * @param index Pointer to the index in the code string.
 * @return      A dynamically allocated string containing the parsed identifier.
 */
char* fscl_fossil_parse_identifier(const char* code, size_t* index);

/**
 * Parse a data type in the code and update the index.
 *
 * @param code  The code string to parse.
 * @param index Pointer to the index in the code string.
 * @return      The parsed data type.
 */
DataType fscl_fossil_parse_data_type(const char* code, size_t* index);

/**
 * Parse a statement in the code and return the corresponding ASTNode.
 *
 * @param statement The statement string to parse.
 * @return          A pointer to the created ASTNode representing the statement.
 */
ASTNode* fscl_fossil_parse_statement(const char* statement);

/**
 * Parse a function declaration in the code and return the corresponding ASTNode.
 *
 * @param code      The code string to parse.
 * @param index     Pointer to the index in the code string.
 * @param entryPoint The entry point for the function.
 * @return          A pointer to the created ASTNode representing the function declaration.
 */
ASTNode* fscl_fossil_parse_function_declaration(const char* code, size_t* index, const char* entryPoint);

/**
 * Create a new class node with the specified class name.
 *
 * @param class_name The name of the class.
 * @return           A pointer to the created class node.
 */
ASTNode* fscl_fossil_create_class(char* class_name);

/**
 * Add a member to a class node with visibility and details.
 *
 * @param classNode The class ASTNode to which the member will be added.
 * @param member    The ASTNode representing the class member.
 * @param is_public Visibility attribute indicating public or private.
 */
void fscl_fossil_add_class_member(ASTNode* classNode, ASTNode* member, int is_public);

/**
 * Parse a class declaration in the code and return the corresponding ASTNode.
 *
 * @param code  The code string to parse.
 * @param index Pointer to the index in the code string.
 * @return      A pointer to the created ASTNode representing the class declaration.
 */
ASTNode* fscl_fossil_parse_class_declaration(const char* code, size_t* index);

/**
 * Parse a DSL file into an AST and return the root ASTNode.
 *
 * @param filename The name of the DSL file to be parsed.
 * @return         A pointer to the root ASTNode representing the parsed DSL file.
 */
ASTNode* fscl_fossil_parse_dsl_file(const char* filename);

#ifdef __cplusplus
}
#endif

#endif
