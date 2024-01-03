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

XTEST_DATA(DSLDummy) {
    FossilDSL dsl;
} compiler;

XTEST_FIXTURE(dsl_fixture);
XTEST_SETUP(dsl_fixture) {
     fscl_fossil_dsl_create(&compiler.dsl, "test_output.tape");
}

XTEST_TEARDOWN(dsl_fixture) {
     fscl_fossil_dsl_erase(&compiler.dsl);
}

//
// XUNIT TEST CASES
//

XTEST_CASE_FIXTURE(dsl_fixture, test_add_function) {
     fscl_fossil_dsl_add_function(&compiler.dsl, "test_function");
    TEST_ASSERT_EQUAL_INT(0, compiler.dsl.error_code);
}

XTEST_CASE_FIXTURE(dsl_fixture, test_call_function) {
     fscl_fossil_dsl_add_function(&compiler.dsl, "test_main");
     fscl_fossil_dsl_call_function(&compiler.dsl, "test_function", NULL, 0);
    TEST_ASSERT_EQUAL_INT(0, compiler.dsl.error_code);
}

XTEST_CASE_FIXTURE(dsl_fixture, test_add_condition_header) {
     fscl_fossil_dsl_add_function(&compiler.dsl, "test_main");
     fscl_fossil_dsl_add_condition(&compiler.dsl, (FossilDSLValue){.type = NULL_TYPE}, "true_branch", "false_branch");
    TEST_ASSERT_EQUAL_INT(0, compiler.dsl.error_code);
}

//
// XUNIT-TEST RUNNER
//
XTEST_DEFINE_POOL(test_fossil_group) {
    XTEST_RUN_FIXTURE(test_add_function,         dsl_fixture);
    XTEST_RUN_FIXTURE(test_call_function,        dsl_fixture);
    XTEST_RUN_FIXTURE(test_add_condition_header, dsl_fixture);
} // end of function main
