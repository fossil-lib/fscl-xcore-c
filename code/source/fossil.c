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

// Global variables for custom names
char OPEN_BRACE_KEYWORD = '{';
char CLOSE_BRACE_KEYWORD = '}';
char* FUNCTION_KEYWORD = "fossil";

// Global variable to track parse error
static ParseError parseError = NO_ERROR;

// Function to convert an integer to a string
char* fscl_fossil_itoa(int value) {
    // Determine the length of the string
    int length = snprintf(NULL, 0, "%d", value);
    
    // Allocate memory for the string (including the null terminator)
    char* str = (char*)malloc(length + 1);
    
    // Check if memory allocation was successful
    if (str == NULL) {
        return NULL; // Memory allocation failed
    }
    
    // Convert the integer to a string
    snprintf(str, length + 1, "%d", value);
    
    return str;
}

// Custom strdup function
char* fscl_fossil_strdup(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    // Calculate the length of the string
    size_t length = strlen(str);

    // Allocate memory for the new string
    char* duplicate = (char*)malloc(length + 1); // +1 for the null terminator

    if (duplicate == NULL) {
        // Memory allocation failed
        return NULL;
    }

    // Copy the string to the new memory
    strcpy(duplicate, str);

    return duplicate;
}

// Function to mark a node as erroneous
void mark_error(ASTNode* node) {
    if (node != NULL) {
        node->error_flag = 1;
    }
}

// Function to read the content of a DSL file
char* fscl_fossil_read_dsl(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory to store the file content
    char* content = (char*)malloc(file_size + 1);
    if (content == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    // Read the content of the file
    size_t read_size = fread(content, 1, file_size, file);
    if (read_size != (size_t)file_size) {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }

    // Null-terminate the content
    content[file_size] = '\0';

    // Close the file
    fclose(file);

    return content;
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

// Function to create a new variable node with visibility
ASTNode* fscl_fossil_create_variable_with_visibility(DataType data_type, char* variable_name, int is_public) {
    ASTNode* variableNode = fscl_fossil_create_node(VARIABLE, data_type, ADD, variable_name);
    variableNode->is_public = is_public;
    return variableNode;
}

// Function to create a new constant node with DATETIME type
ASTNode* fscl_fossil_create_datetime_constant(char* datetime_value) {
    return fscl_fossil_create_node(CONSTANT, DATETIME, ADD, datetime_value);
}

// Function to create a new variable node
ASTNode* fscl_fossil_create_variable(DataType data_type, char* variable_name) {
    return fscl_fossil_create_node(VARIABLE, data_type, ADD, variable_name);
}

// Function to create a new function node
ASTNode* fscl_fossil_create_function(DataType return_type, char* function_name) {
    return fscl_fossil_create_node(FUNCTION, return_type, ADD, function_name);
}

// Function to create a new constant node
ASTNode* fscl_fossil_create_constant(DataType data_type, char* constant_value) {
    return fscl_fossil_create_node(CONSTANT, data_type, ADD, constant_value);
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

// Function to skip whitespace in the code
void fscl_fossil_skip_whitespace(const char* code, size_t* index) {
    while (isspace(code[*index])) {
        (*index)++;
    }
}

// Function to parse an identifier in the code
char* fscl_fossil_parse_identifier(const char* code, size_t* index) {
    // Implementation of identifier parsing logic
    // Adjust based on your DSL syntax
    // For simplicity, assuming an identifier is a sequence of letters and digits

    size_t start = *index;
    while (isalnum(code[*index]) || code[*index] == '_') {
        (*index)++;
    }

    // Create a copy of the identifier
    char* identifier = fscl_fossil_strdup(code + start, *index - start);

    return identifier;
}

// Function to parse a data type in the code
DataType fscl_fossil_parse_data_type(const char* code, size_t* index) {
    // Skip whitespace
    fscl_fossil_skip_whitespace(code, index);

    // Parse the identifier (assumed to represent the data type)
    char* dataTypeString = fscl_fossil_parse_identifier(code, index);

    // Convert the data type string to the corresponding enumeration
    DataType dataType = ERROR;  // Default to ERROR

    // Map data type string to the enumeration
    if (strcmp(dataTypeString, "int") == 0) {
        dataType = INT;
    } else if (strcmp(dataTypeString, "int8") == 0) {
        dataType = INT8;
    } else if (strcmp(dataTypeString, "int16") == 0) {
        dataType = INT16;
    } else if (strcmp(dataTypeString, "int32") == 0) {
        dataType = INT32;
    } else if (strcmp(dataTypeString, "int64") == 0) {
        dataType = INT64;
    } else if (strcmp(dataTypeString, "uint") == 0) {
        dataType = UINT;
    } else if (strcmp(dataTypeString, "uint8") == 0) {
        dataType = UINT8;
    } else if (strcmp(dataTypeString, "uint16") == 0) {
        dataType = UINT16;
    } else if (strcmp(dataTypeString, "uint32") == 0) {
        dataType = UINT32;
    } else if (strcmp(dataTypeString, "uint64") == 0) {
        dataType = UINT64;
    } else if (strcmp(dataTypeString, "float") == 0) {
        dataType = FLOAT;
    } else if (strcmp(dataTypeString, "string") == 0) {
        dataType = STRING;
    } else if (strcmp(dataTypeString, "array") == 0) {
        dataType = ARRAY;
    } else if (strcmp(dataTypeString, "map") == 0) {
        dataType = MAP;
    } else if (strcmp(dataTypeString, "bool") == 0) {
        dataType = BOOL;
    } else if (strcmp(dataTypeString, "tofu") == 0) {
        dataType = TOFU;
    } else if (strcmp(dataTypeString, "char") == 0) {
        dataType = CHAR;
    } else if (strcmp(dataTypeString, "hex") == 0) {
        dataType = HEX;
    } else if (strcmp(dataTypeString, "oct") == 0) {
        dataType = OCT;
    } else if (strcmp(dataTypeString, "null") == 0) {
        dataType = NULL_TYPE;
    } else if (strcmp(dataTypeString, "comedy") == 0) {
        dataType = COMEDY_ERROR;
    } else if (strcmp(dataTypeString, "placeholder") == 0) {
        dataType = PLACEHOLDER;
    } else if (strcmp(dataTypeString, "datetime") == 0) {
        dataType = DATETIME;
    } else {
        // If the type is not recognized, set it to ERROR
    }

    free(dataTypeString);  // Free the memory allocated for the data type string

    return dataType;
}

// Function to parse a statement into ASTNode
ASTNode* fscl_fossil_parse_statement(const char* statement) {
    // Implementation of statement parsing logic
    // Adjust based on your DSL syntax

    // For this example, return a dummy ASTNode
    ASTNode* statementNode = (ASTNode*)malloc(sizeof(ASTNode));
    statementNode->type = VARIABLE;
    statementNode->value = fscl_fossil_strdup(statement);
    // Initialize other fields as needed

    return statementNode;
}

// Function to parse a function declaration
ASTNode* fscl_fossil_parse_function_declaration(const char* code, size_t* index, const char* entryPoint) {
    // Skip whitespace
    fscl_fossil_skip_whitespace(code, index);

    // Parse function name
    char* functionName = fscl_fossil_parse_identifier(code, index);

    // Create function node
    ASTNode* functionNode = fscl_fossil_create_function(TOFU, functionName);

    // Parse function parameters
    if (code[*index] == '(') {
        (*index)++;  // Move past '('

        // Parse each parameter
        while (code[*index] != ')' && code[*index] != '\0') {
            // Parse parameter type
            DataType paramType = fscl_fossil_parse_data_type(code, index);

            // Parse parameter name
            char* paramName = fscl_fossil_parse_identifier(code, index);

            // Create parameter node
            ASTNode* paramNode = fscl_fossil_create_variable_with_visibility(paramType, paramName, 0);

            // Check for default value
            if (code[*index] == '=') {
                (*index)++;  // Move past '='

                // Parse default value (assuming integers for simplicity)
                int defaultValue = strtol(code + *index, NULL, 10);
                // You might need a more sophisticated way to parse default values based on your DSL

                // Create a constant node for the default value
                ASTNode* defaultValueNode = fscl_fossil_create_constant(INT8, fscl_fossil_itoa(defaultValue));
                fscl_fossil_add_child(paramNode, defaultValueNode);

                // Skip the default value in the code
                while (isdigit(code[*index])) {
                    (*index)++;
                }
            }

            // Add parameter node to function node
            fscl_fossil_add_child(functionNode, paramNode);

            // Skip whitespace and check for a comma (,)
            fscl_fossil_skip_whitespace(code, index);
            if (code[*index] == ',') {
                (*index)++;  // Move past ','
                fscl_fossil_skip_whitespace(code, index);
            }
        }

        // Skip closing parenthesis ')'
        if (code[*index] == ')') {
            (*index)++;
        } else {
            // Handle error: Missing closing parenthesis
            mark_error(functionNode);
            printf("Error: Missing closing parenthesis in function declaration.\n");
        }
    }

    // Parse function body (if any)
    if (code[*index] == OPEN_BRACE_KEYWORD) {
        (*index)++;  // Move past '{'

        // Parse statements within the function body
        while (code[*index] != CLOSE_BRACE_KEYWORD && code[*index] != '\0') {
            // Parse statement
            ASTNode* statementNode = fscl_fossil_parse_statement(code);

            // Add statement node to function node
            fscl_fossil_add_child(functionNode, statementNode);

            // Skip whitespace and check for next statement
            fscl_fossil_skip_whitespace(code, index);
        }

        // Skip closing brace '}'
        if (code[*index] == CLOSE_BRACE_KEYWORD) {
            (*index)++;
        } else {
            // Handle error: Missing closing brace
            mark_error(functionNode);
            printf("Error: Missing closing brace in function body.\n");
        }
    }

    return functionNode;
}

// Function to create a new class node with details
ASTNode* fscl_fossil_create_class(char* class_name) {
    ASTNode* classNode = fscl_fossil_create_node(CLASS, TOFU, ADD, class_name);
    
    // Initialize class-specific details
    classNode->public_members = NULL;
    classNode->private_members = NULL;
    classNode->num_public_members = 0;
    classNode->num_private_members = 0;

    return classNode;
}

// Function to add a member to a class with visibility and details
void fscl_fossil_add_class_member(ASTNode* classNode, ASTNode* member, int is_public) {
    if (classNode == NULL || member == NULL || classNode->error_flag || member->error_flag) {
        mark_error(classNode);
        mark_error(member);
        return;
    }

    member->is_public = is_public;
    fscl_fossil_add_child(classNode, member);

    // Add the member to the appropriate list based on visibility
    if (is_public) {
        classNode->public_members = (ASTNode**)realloc(classNode->public_members, (classNode->num_public_members + 1) * sizeof(ASTNode*));
        classNode->public_members[classNode->num_public_members] = member;
        classNode->num_public_members++;
    } else {
        classNode->private_members = (ASTNode**)realloc(classNode->private_members, (classNode->num_private_members + 1) * sizeof(ASTNode*));
        classNode->private_members[classNode->num_private_members] = member;
        classNode->num_private_members++;
    }
}

// Function to parse a class declaration
ASTNode* fscl_fossil_parse_class_declaration(const char* code, size_t* index) {
    // Skip whitespace
    fscl_fossil_skip_whitespace(code, index);

    // Parse class name
    char* className = fscl_fossil_parse_identifier(code, index);

    // Create class node
    ASTNode* classNode = fscl_fossil_create_class(className);

    // Parse class body
    if (code[*index] == OPEN_BRACE_KEYWORD) {
        (*index)++;  // Move past '{'

        // Parse members within the class body
        while (code[*index] != CLOSE_BRACE_KEYWORD && code[*index] != '\0') {
            // Parse member
            ASTNode* memberNode = fscl_fossil_parse_statement(code);

            // Check if the member is a variable with visibility
            if (memberNode->type == VARIABLE) {
                int isPublic = memberNode->is_public;
                free(memberNode);
                memberNode = fscl_fossil_parse_statement(code);
                fscl_fossil_add_class_member(classNode, memberNode, isPublic);
            } else {
                // Add member node to class node
                fscl_fossil_add_class_member(classNode, memberNode, 1);  // Default to public visibility
            }

            // Skip whitespace and check for next member
            fscl_fossil_skip_whitespace(code, index);
        }

        // Skip closing brace '}'
        if (code[*index] == CLOSE_BRACE_KEYWORD) {
            (*index)++;
        } else {
            // Handle error: Missing closing brace
            mark_error(classNode);
            printf("Error: Missing closing brace in class body.\n");
        }
    }

    return classNode;
}

// Function to parse a DSL file into an AST
ASTNode* fscl_fossil_parse_dsl_file(const char* filename) {
    // Read the content of the DSL file
    char* code = fscl_fossil_read_dsl(filename);

    // Initialize parsing error
    resetParseError();

    // Create a root node for the AST
    ASTNode* rootNode = fscl_fossil_create_node(PLACEHOLDER_NODE, PLACEHOLDER, ADD, NULL);

    size_t index = 0;

    // Parse DSL statements and populate the AST
    while (code[index] != '\0') {
        // Parse function declaration
        if (strncmp(code + index, FUNCTION_KEYWORD, 8) == 0) {
            ASTNode* functionNode = fscl_fossil_parse_function_declaration(code, &index, NULL);
            fscl_fossil_add_child(rootNode, functionNode);
        }
        // Parse class declaration
        else if (strncmp(code + index, "class", 5) == 0) {
            ASTNode* classNode = fscl_fossil_parse_class_declaration(code, &index);
            fscl_fossil_add_child(rootNode, classNode);
        }
        // Skip unknown statements
        else {
            // Handle unknown keyword error
            setParseError(UNKNOWN_KEYWORD_ERROR);
            printf("Error: Unknown keyword encountered during parsing.\n");
            break;
        }

        // Skip whitespace and check for next statement
        fscl_fossil_skip_whitespace(code, &index);
    }

    // Free the memory allocated for the code
    free(code);

    // Check for parsing errors
    if (parseError != NO_ERROR) {
        // Erase the partial AST in case of errors
        fscl_fossil_erase_node(rootNode);
        return NULL;
    }

    return rootNode;
}
