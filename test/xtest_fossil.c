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
#include "fossil/xcore/fossil.h" // lib source code

#include <fossil/xtest.h>   // basic test tools
#include <fossil/xassert.h> // extra asserts

// Function to create ASTNode from generic DSL code
ASTNode* create_dsl_from_code(const char* dslCode, const char* rootType) {

    // For this example, return a dummy ASTNode
    ASTNode* rootNode = (ASTNode*)malloc(sizeof(ASTNode));
    rootNode->type = rootType;
    rootNode->value = "Root Node (Generic)";
    // Initialize other fields as needed

    return rootNode;
}

// Updated test case for parsing a simple class declaration
XTEST_CASE(test_parse_simple_class_declaration) {
    const char* code = "fossil class Person {\n"
                       "    private string name;\n"
                       "    public void set_name(string n) {\n"
                       "        name = n;\n"
                       "    }\n"
                       "    public string get_name() {\n"
                       "        return name;\n"
                       "    }\n"
                       "}\n"
                       "fossil main() {\n"
                       "    Person person;\n"
                       "    person.set_name(\"John\");\n"
                       "    print(\"Person's name: \" + person.get_name());\n"
                       "}";

    ASTNode* ast = create_dsl_from_code(code, MAIN_FUNCTION_TYPE);

    TEST_ASSERT_NOT_CNULLPTR(ast);
    TEST_ASSERT_EQUAL_INT(MAIN_FUNCTION_TYPE, ast->type);

    // Validate class declaration
    ASTNode* classNode = ast->children[0];
    TEST_ASSERT_NOT_CNULLPTR(classNode);
    TEST_ASSERT_EQUAL_INT(CLASS_DECLARATION_TYPE, classNode->type);

    ASTNode* classNameNode = classNode->children[0];
    TEST_ASSERT_NOT_CNULLPTR(classNameNode);
    TEST_ASSERT_EQUAL_INT(IDENTIFIER_TYPE, classNameNode->type);

    // Validate method declarations
    ASTNode* methodNode = classNode->children[1];
    TEST_ASSERT_NOT_CNULLPTR(methodNode);
    TEST_ASSERT_EQUAL_INT(METHOD_DECLARATION_TYPE, methodNode->type);

    ASTNode* methodNameNode = methodNode->children[0];
    TEST_ASSERT_NOT_CNULLPTR(methodNameNode);
    TEST_ASSERT_EQUAL_INT(IDENTIFIER_TYPE, methodNameNode->type);

    // Add more assertions as needed to validate the AST structure

    // Clean up
    fscl_fossil_erase_node(ast);
}

// Updated test case for parsing a "Hello, World!" example
XTEST_CASE(test_parse_hello_world) {
    const char* code = "fossil main() {\n"
                       "    print(\"Hello, World!\");\n"
                       "}";

    ASTNode* ast = create_dsl_from_code(code, MAIN_FUNCTION_TYPE);

    TEST_ASSERT_NOT_CNULLPTR(ast);
    TEST_ASSERT_EQUAL_INT(MAIN_FUNCTION_TYPE, ast->type);

    // Validate print statement
    ASTNode* printNode = ast->children[0];
    TEST_ASSERT_NOT_CNULLPTR(printNode);
    TEST_ASSERT_EQUAL_INT(PRINT_STATEMENT_TYPE, printNode->type);

    ASTNode* printArgNode = printNode->children[0];
    TEST_ASSERT_NOT_CNULLPTR(printArgNode);
    TEST_ASSERT_EQUAL_INT(STRING_LITERAL_TYPE, printArgNode->type);

    // Add more assertions as needed to validate the AST structure

    // Clean up
    fscl_fossil_erase_node(ast);
}

// Updated test case for parsing a linked file with an entry point file
XTEST_CASE(test_parse_linked_file) {
    const char* code = "fossil link \"linked_file.dsl\"\n"
                       "fossil main() {\n"
                       "    print(\"Linked file content\");\n"
                       "}";

    ASTNode* ast = create_dsl_from_code(code, MAIN_FUNCTION_TYPE);

    TEST_ASSERT_NOT_CNULLPTR(ast);
    TEST_ASSERT_EQUAL_INT(MAIN_FUNCTION_TYPE, ast->type);

    // Validate link statement
    ASTNode* linkNode = ast->children[0];
    TEST_ASSERT_NOT_CNULLPTR(linkNode);
    TEST_ASSERT_EQUAL_INT(LINK_STATEMENT_TYPE, linkNode->type);

    ASTNode* linkedFileNode = linkNode->children[0];
    TEST_ASSERT_NOT_CNULLPTR(linkedFileNode);
    TEST_ASSERT_EQUAL_INT(STRING_LITERAL_TYPE, linkedFileNode->type);

    // Add more assertions as needed to validate the AST structure

    // Clean up
    fscl_fossil_erase_node(ast);
}

// Updated test case for parsing a DSL program using a custom library
XTEST_CASE(test_parse_using_library) {
    const char* code = "fossil import \"custom_library.dsl\"\n"
                       "fossil main() {\n"
                       "    custom_function();\n"
                       "}";

    ASTNode* ast = create_dsl_from_code(code, MAIN_FUNCTION_TYPE);

    TEST_ASSERT_NOT_CNULLPTR(ast);
    TEST_ASSERT_EQUAL_INT(MAIN_FUNCTION_TYPE, ast->type);

    // Validate import statement
    ASTNode* importNode = ast->children[0];
    TEST_ASSERT_NOT_CNULLPTR(importNode);
    TEST_ASSERT_EQUAL_INT(IMPORT_STATEMENT_TYPE, importNode->type);

    ASTNode* importedLibraryNode = importNode->children[0];
    TEST_ASSERT_NOT_CNULLPTR(importedLibraryNode);
    TEST_ASSERT_EQUAL_INT(STRING_LITERAL_TYPE, importedLibraryNode->type);

    // Add more assertions as needed to validate the AST structure

    // Clean up
    fscl_fossil_erase_node(ast);
}

// Updated test case for parsing Tape Language DSL
XTEST_CASE(test_parse_tape_language_dsl) {
    const char* tapeLanguageCode = "fossil tape_program() {\n"
                                  "    move_forward(10);\n"
                                  "    turn_left(90);\n"
                                  "    move_forward(5);\n"
                                  "    turn_right(45);\n"
                                  "    move_backward(8);\n"
                                  "}";

    ASTNode* ast = create_dsl_from_code(tapeLanguageCode, TAPE_PROGRAM_TYPE);

    TEST_ASSERT_NOT_CNULLPTR(ast);
    TEST_ASSERT_EQUAL_INT(TAPE_PROGRAM_TYPE, ast->type);

    // Validate move and turn statements
    for (int i = 0; i < 5; ++i) {
        ASTNode* actionNode = ast->children[i];
        TEST_ASSERT_NOT_CNULLPTR(actionNode);
        TEST_ASSERT_EQUAL_INT(ACTION_STATEMENT_TYPE, actionNode->type);

        // Add more assertions as needed to validate the AST structure
    }

    // Clean up
    fscl_fossil_erase_node(ast);
}

// Updated test case for parsing Updated Meson Build System DSL
XTEST_CASE(test_parse_meson_build_system_dsl) {
    const char* mesonBuildSystemCode = "fossil project('my_project', 'c')\n"
                                       "executable('my_executable', sources: ['source.c'], dependencies: ['libraryA', 'libraryB'])\n"
                                       "library('libraryA', sources: ['file1.c', 'file2.c'])\n"
                                       "library('libraryB', sources: ['file3.c', 'file4.c'])";

    ASTNode* ast = create_dsl_from_code(mesonBuildSystemCode, PROJECT_STATEMENT_TYPE);

    TEST_ASSERT_NOT_CNULLPTR(ast);
    TEST_ASSERT_EQUAL_INT(PROJECT_STATEMENT_TYPE, ast->type);

    // Validate project, executable, and library statements
    for (int i = 0; i < 4; ++i) {
        ASTNode* statementNode = ast->children[i];
        TEST_ASSERT_NOT_CNULLPTR(statementNode);
        TEST_ASSERT_EQUAL_INT(STATEMENT_TYPE, statementNode->type);

        // Add more assertions as needed to validate the AST structure
    }

    // Clean up
    fscl_fossil_erase_node(ast);
}


//
// XUNIT-TEST RUNNER
//
XTEST_DEFINE_POOL(test_fossil_group) {
    // Updated test cases
    XTEST_RUN_UNIT(test_parse_simple_class_declaration);
    XTEST_RUN_UNIT(test_parse_hello_world);
    XTEST_RUN_UNIT(test_parse_linked_file);
    XTEST_RUN_UNIT(test_parse_using_library);
    XTEST_RUN_UNIT(test_parse_tape_language_dsl);
    XTEST_RUN_UNIT(test_parse_meson_build_system_dsl);
} // end of function main
