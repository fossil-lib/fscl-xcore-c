/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.home.blog>
*/
#include "trilobite/xcore/fossil.h" // lib source code

#include <trilobite/xtest.h>   // basic test tools
#include <trilobite/xassert.h> // extra asserts
#include <stdio.h>
#include <string.h>

//
// XUNIT TEST CASES
//

// Test case for ini_parser_parse
XTEST_CASE(test_parse_main_function) {
    char filename[] = "program.fossil";
    // Clear any previous state
    fossil_dsl_reset();

    fossil_dsl_parse(filename);

    // Get the parsed function
    Function parsedFunction = fossil_dsl_get_parsed_function();

    // Check if the parsed function name is correct
    TEST_ASSERT_EQUAL_STRING("main", parsedFunction.name);

    // Check if the parsed parameters and return type are correct
    TEST_ASSERT_EQUAL_INT(0, parsedFunction.param_count);
    TEST_ASSERT_NULL_PTR(parsedFunction.parameters);
    TEST_ASSERT_EQUAL_STRING("int", parsedFunction.return_type);

    // Clean up
    fossil_dsl_erase_function(&parsedFunction);
}

XTEST_CASE(test_parse_library_function) {
    char filename[] = "program.fossil";
    // Clear any previous state
    fossil_dsl_reset();

    fossil_dsl_parse(filename);

    // Get the parsed function
    Function parsedFunction = fossil_dsl_get_parsed_function();

    // Check if the parsed function name is correct
    TEST_ASSERT_EQUAL_STRING("libraryFunction", parsedFunction.name);

    // Check if the parsed parameters and return type are correct
    TEST_ASSERT_EQUAL_INT(0, parsedFunction.param_count);
    TEST_ASSERT_NULL_PTR(parsedFunction.parameters);
    TEST_ASSERT_EQUAL_STRING("unit", parsedFunction.return_type);

    // Clean up
    fossil_dsl_erase_function(&parsedFunction);
}

//
// XUNIT-TEST RUNNER
//
XTEST_GROUP_DEFINE(test_fossil_group) {
    XTEST_RUN_UNIT(test_parse_main_function,  runner);
    XTEST_RUN_UNIT(test_parse_library_function,  runner);
} // end of function main
