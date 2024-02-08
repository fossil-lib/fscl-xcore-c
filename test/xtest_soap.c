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
#include "fossil/xcore/soap.h" // lib source code

#include <fossil/xtest.h>   // basic test tools
#include <fossil/xassert.h> // extra asserts

//
// XUNIT-CASES: list of test cases testing project features
//

XTEST_CASE(test_fscl_soap_sanitize) {
    char input[] = "This is a test with curse1 and racist_phrase1.";
    char expected[] = "This is a test with *** and ***.";

    fscl_soap_sanitize(input);

    TEST_ASSERT_EQUAL_CSTRING(expected, input);
}

XTEST_CASE(test_fscl_soap_is_offensive) {
    TEST_ASSERT_TRUE(fscl_soap_is_offensive("curse1"));
    TEST_ASSERT_TRUE(fscl_soap_is_offensive("racist_phrase2"));
    TEST_ASSERT_FALSE(fscl_soap_is_offensive("non_offensive_word"));
}

XTEST_CASE(test_fscl_soap_count_offensive) {
    char input[] = "This is a test with curse1 and racist_phrase1.";
    TEST_ASSERT_EQUAL_INT(2, fscl_soap_count_offensive(input));
}

XTEST_CASE(test_fscl_soap_strdup) {
    const char *original = "Test String";
    char *duplicate = fscl_soap_strdup(original);

    TEST_ASSERT_NOT_CNULLPTR(duplicate);
    TEST_ASSERT_EQUAL_CSTRING(original, duplicate);

    free(duplicate); // Clean up the allocated memory
}

//
// XUNIT-TEST RUNNER
//
XTEST_DEFINE_POOL(test_soap_group) {
    XTEST_RUN_UNIT(test_fscl_soap_sanitize);
    XTEST_RUN_UNIT(test_fscl_soap_is_offensive);
    XTEST_RUN_UNIT(test_fscl_soap_count_offensive);
    XTEST_RUN_UNIT(test_fscl_soap_strdup);
} // end of function main
