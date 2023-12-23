/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.home.blog>
*/
#include "trilobite/xcore/lazy.h" // lib source code

#include <trilobite/xtest.h>   // basic test tools
#include <trilobite/xassert.h> // extra asserts

//
// XUNIT TEST CASES
//
XTEST_CASE(test_lazy_int) {
    clazy intLazy = tscl_lazy_create(CLAZY_INT);
    TEST_ASSERT_EQUAL_INT(42, tscl_lazy_force_int(&intLazy));
    tscl_lazy_erase(&intLazy);
}

XTEST_CASE(test_lazy_bool) {
    clazy boolLazy = tscl_lazy_create(CLAZY_BOOL);
    TEST_ASSERT_FALSE(tscl_lazy_force_bool(&boolLazy));  // Default is false
    tscl_lazy_erase(&boolLazy);
}

XTEST_CASE(test_lazy_char) {
    clazy charLazy = tscl_lazy_create(CLAZY_CHAR);
    TEST_ASSERT_EQUAL_CHAR('\0', tscl_lazy_force_char(&charLazy));
    tscl_lazy_erase(&charLazy);
}

XTEST_CASE(test_lazy_string) {
    clazy stringLazy = tscl_lazy_create(CLAZY_STRING);
    TEST_ASSERT_NULL_PTR(tscl_lazy_force_string(&stringLazy));  // Default is NULL
    tscl_lazy_erase(&stringLazy);
}

XTEST_CASE(test_lazy_sequence) {
    clazy sequenceLazy = tscl_lazy_sequence();
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT_EQUAL_INT(i, tscl_lazy_sequence_force(&sequenceLazy, i));
    }
    tscl_lazy_erase(&sequenceLazy);
}

//
// XUNIT-TEST RUNNER
//
XTEST_GROUP_DEFINE(test_lazy_group) {
    XTEST_RUN_UNIT(test_lazy_int, runner);
    XTEST_RUN_UNIT(test_lazy_bool, runner);
    XTEST_RUN_UNIT(test_lazy_char, runner);
    XTEST_RUN_UNIT(test_lazy_string, runner);
    XTEST_RUN_UNIT(test_lazy_sequence, runner);
} // end of function main
