/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.home.blog>
*/
#include "trilobite/xcore/fossil.h" // lib source code

#include <trilobite/xtest.h>   // basic test tools
#include <trilobite/xassert.h> // extra asserts

XTEST_DATA(DSLDummy) {
    FossilDSL *dsl;
} compiler;

XTEST_FIXTURE(dsl_fixture);
XTEST_SETUP(dsl_fixture) {
    fossil_dsl_create(&compiler.dsl, "test_output.tape");
}

XTEST_TEARDOWN(dsl_fixture) {
    fossil_dsl_erase(&compiler.dsl);
}

//
// XUNIT TEST CASES
//

XTEST_CASE_FIXTURE(dsl_fixture, test_add_function) {
    fossil_dsl_add_function(&compiler.dsl, "test_function");
    TEST_ASSERT_EQUAL_INT(0, compiler.dsl.error_code);
}

XTEST_CASE_FIXTURE(dsl_fixture, test_call_function) {
    fossil_dsl_add_function(&compiler.dsl, "test_main");
    fossil_dsl_call_function(&compiler.dsl, "test_function", NULL, 0);
    TEST_ASSERT_EQUAL_INT(0, compiler.dsl.error_code);
}

XTEST_CASE_FIXTURE(dsl_fixture, test_add_condition_header) {
    fossil_dsl_add_function(&compiler.dsl, "test_main");
    fossil_dsl_add_condition(&compiler.dsl, (FossilDSLValue){.type = NULL_TYPE}, "true_branch", "false_branch");
    TEST_ASSERT_EQUAL_INT(0, compiler.dsl.error_code);
}

//
// XUNIT-TEST RUNNER
//
XTEST_GROUP_DEFINE(test_fossil_group) {
    XTEST_RUN_FIXTURE(test_add_function,         dsl_fixture, runner);
    XTEST_RUN_FIXTURE(test_call_function,        dsl_fixture, runner);
    XTEST_RUN_FIXTURE(test_add_condition_header, dsl_fixture, runner);
} // end of function main
