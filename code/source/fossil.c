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

// Function to mark a node as erroneous
void mark_error(ASTNode* node) {
    if (node != NULL) {
        node->error_flag = 1;
    }
}

// Function to create a new AST node
ASTNode* fscl_fossil_create_node(NodeType type, DataType data_type, OperatorType operator_type, char* value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (node == NULL) {
        // Handle memory allocation error
        exit(EXIT_FAILURE);
    }

    node->type = type;
    node->data_type = data_type;
    node->operator_type = operator_type;
    node->value = value;
    node->error_flag = 0;
    node->num_children = 0;

    if (type == PLACEHOLDER_NODE) {
        // Special handling for placeholder nodes
        // You might customize this based on how you want to represent placeholders
    } else {
        // For other node types, create space for children
        node->children = (ASTNode**)malloc(sizeof(ASTNode*));
        if (node->children == NULL) {
            // Handle memory allocation error
            exit(EXIT_FAILURE);
        }
    }

    return node;
}

// Function to add a child to an AST node
void fscl_fossil_add_child(ASTNode* parent, ASTNode* child) {
    if (parent == NULL || child == NULL || parent->error_flag || child->error_flag) {
        mark_error(parent);
        mark_error(child);
        return;
    }

    parent->children = (ASTNode**)realloc(parent->children, (parent->num_children + 1) * sizeof(ASTNode*));
    if (parent->children == NULL) {
        // Handle memory allocation error
        mark_error(parent);
        return;
    }

    parent->children[parent->num_children] = child;
    parent->num_children++;
}

// Function to add multiple children to an AST node
void fscl_fossil_add_children(ASTNode* parent, size_t num_children, ...) {
    va_list args;
    va_start(args, num_children);

    for (size_t i = 0; i < num_children; ++i) {
        ASTNode* child = va_arg(args, ASTNode*);
        fscl_fossil_add_child(parent, child);
    }

    va_end(args);
}

// Function to print the AST in a readable format
void fscl_fossil_print_ast(ASTNode* root, int depth) {
    if (root == NULL || root->error_flag) {
        return;
    }

    // Print the current node
    for (int i = 0; i < depth; ++i) {
        printf("  ");
    }

    printf("Type: %d, Data Type: %d, Operator Type: %d, Value: %s\n", root->type, root->data_type, root->operator_type, root->value);

    // Recursively print children
    for (size_t i = 0; i < root->num_children; ++i) {
        fscl_fossil_print_ast(root->children[i], depth + 1);
    }
}

// Function to erase an AST node and its children
void fscl_fossil_erase_node(ASTNode* node) {
    if (node == NULL) {
        return;
    }

    for (size_t i = 0; i < node->num_children; ++i) {
        fscl_fossil_erase_node(node->children[i]);
    }

    free(node->children);
    free(node);
}

// Function to create a new variable node
ASTNode* fscl_fossil_create_variable(DataType data_type, char* variable_name) {
    return fscl_fossil_create_node(VARIABLE, data_type, ADD, variable_name);
}

// Function to create a new constant node
ASTNode* fscl_fossil_create_constant(DataType data_type, char* constant_value) {
    return fscl_fossil_create_node(CONSTANT, data_type, ADD, constant_value);
}

// Function to create a new function node
ASTNode* fscl_fossil_create_function(DataType return_type, char* function_name) {
    return fscl_fossil_create_node(FUNCTION, return_type, ADD, function_name);
}

// Function to create a new unary operation node
ASTNode* fscl_fossil_create_unary_op(DataType data_type, OperatorType operator_type, char* operand_value) {
    return fscl_fossil_create_node(UNARY_OP, data_type, operator_type, operand_value);
}

// Function to create a new relational operation node
ASTNode* fscl_fossil_create_relational_op(DataType data_type, OperatorType operator_type, char* operand_value) {
    return fscl_fossil_create_node(RELATIONAL_OP, data_type, operator_type, operand_value);
}

// Function to create a new logical operation node
ASTNode* fscl_fossil_create_logical_op(DataType data_type, OperatorType operator_type, char* operand_value) {
    return fscl_fossil_create_node(LOGICAL_OP, data_type, operator_type, operand_value);
}

// Function to create a new if statement node
ASTNode* fscl_fossil_create_if_statement(char* condition_value) {
    return fscl_fossil_create_node(IF_STATEMENT, BOOL, ADD, condition_value);
}

// Function to create a new while loop node
ASTNode* fscl_fossil_create_while_loop(char* condition_value) {
    return fscl_fossil_create_node(WHILE_LOOP, BOOL, ADD, condition_value);
}

// Function to create a new include file node
ASTNode* fscl_fossil_create_include_file(char* file_name) {
    return fscl_fossil_create_node(INCLUDE_FILE, STRING, ADD, file_name);
}

// Function to create a new link library node
ASTNode* fscl_fossil_create_link_library(char* library_name) {
    return fscl_fossil_create_node(LINK_LIBRARY, STRING, ADD, library_name);
}

// Function to set a parsing error
void setParseError(ParseError errorType) {
    parseError = errorType;
}

// Function to reset the parsing error
void resetParseError() {
    parseError = NO_ERROR;
}

// Function to get the parsing error message
const char* getParseErrorMessage() {
    switch (parseError) {
        case UNKNOWN_KEYWORD_ERROR:
            return "Unknown keyword encountered during parsing.";
        case PARSING_ERROR:
            return "Error occurred while parsing.";
        default:
            return "No error.";
    }
}

// Function to parse and create a function declaration node
ASTNode* fscl_fossil_parse_function_declaration(char* declaration) {
    char* returnType = strtok(declaration, " ");
    char* functionName = strtok(NULL, "( ");
    char* params = strtok(NULL, ")");

    if (returnType == NULL || functionName == NULL || params == NULL) {
        setParseError(PARSING_ERROR);
        return NULL;
    }

    DataType returnDataType;
    if (strcmp(returnType, "int") == 0) {
        returnDataType = INT32;
    } else if (strcmp(returnType, "float") == 0) {
        returnDataType = FLOAT;
    } else {
        setParseError(PARSING_ERROR);
        return NULL;
    }

    ASTNode* functionNode = fscl_fossil_create_function(returnDataType, functionName);

    // Parse function parameters
    char* param = strtok(params, ",");
    while (param != NULL) {
        char* paramType = strtok(param, " ");
        char* paramName = strtok(NULL, " ,");

        if (paramType == NULL || paramName == NULL) {
            setParseError(PARSING_ERROR);
            return NULL;
        }

        DataType paramDataType;
        if (strcmp(paramType, "int") == 0) {
            paramDataType = INT32;
        } else if (strcmp(paramType, "float") == 0) {
            paramDataType = FLOAT;
        } else {
            setParseError(PARSING_ERROR);
            return NULL;
        }

        ASTNode* paramNode = fscl_fossil_create_variable(paramDataType, paramName);
        fscl_fossil_add_child(functionNode, paramNode);

        param = strtok(NULL, ",");
    }

    return functionNode;
}

// Function to create a new include file node
ASTNode* fscl_fossil_create_include_file(char* file_name) {
    return fscl_fossil_create_node(INCLUDE_FILE, STRING, ADD, file_name);
}

// Function to create a new link library node
ASTNode* fscl_fossil_create_link_library(char* library_name) {
    return fscl_fossil_create_node(LINK_LIBRARY, STRING, ADD, library_name);
}

