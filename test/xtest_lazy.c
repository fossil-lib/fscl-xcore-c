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
#include "fossil/xcore/lazy.h" // lib source code

#include <fossil/xtest.h>   // basic test tools
#include <fossil/xassert.h> // extra asserts

//
// XUNIT TEST CASES
//
XTEST_CASE(test_lazy_int) {
    clazy intLazy = fscl_lazy_create(CLAZY_INT);
    TEST_ASSERT_EQUAL_INT(42, fscl_lazy_force_int(&intLazy));
    fscl_lazy_erase(&intLazy);
}

XTEST_CASE(test_lazy_bool) {
    clazy boolLazy = fscl_lazy_create(CLAZY_BOOL);
    TEST_ASSERT_FALSE(fscl_lazy_force_bool(&boolLazy));  // Default is false
    fscl_lazy_erase(&boolLazy);
}

XTEST_CASE(test_lazy_char) {
    clazy charLazy = fscl_lazy_create(CLAZY_CHAR);
    TEST_ASSERT_EQUAL_CHAR('\0', fscl_lazy_force_char(&charLazy));
    fscl_lazy_erase(&charLazy);
}

XTEST_CASE(test_lazy_string) {
    clazy stringLazy = fscl_lazy_create(CLAZY_STRING);
    TEST_ASSERT_CNULLPTR(fscl_lazy_force_string(&stringLazy));  // Default is NULL
    fscl_lazy_erase(&stringLazy);
}

XTEST_CASE(test_lazy_sequence) {
    clazy sequenceLazy = fscl_lazy_sequence();
    for (int i = 0; i < 5; ++i) {
        TEST_ASSERT_EQUAL_INT(i, fscl_lazy_sequence_force(&sequenceLazy, i));
    }
    fscl_lazy_erase(&sequenceLazy);
}

//
// XUNIT-TEST RUNNER
//
XTEST_DEFINE_POOL(test_lazy_group) {
    XTEST_RUN_UNIT(test_lazy_int);
    XTEST_RUN_UNIT(test_lazy_bool);
    XTEST_RUN_UNIT(test_lazy_char);
    XTEST_RUN_UNIT(test_lazy_string);
    XTEST_RUN_UNIT(test_lazy_sequence);
} // end of function main
