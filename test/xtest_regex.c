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
#include "fossil/xcore/regex.h" // lib source code

#include <fossil/xtest.h>   // basic test tools
#include <fossil/xassert.h> // extra asserts

//
// XUNIT TEST CASES
//

// Test case for initializing error with a message
XTEST_CASE(test_regex_match_and_extract_normal) {
    cregex my_regex;
    const char *pattern = "a.*b";
    const char *text = "@A123b!";

    // Initialize regex
    TEST_ASSERT_EQUAL_INT(0, fscl_regex_create(&my_regex, pattern));

    // Match and extract substring
    const char *matched_substring = fscl_regex_match_and_extract(&my_regex, text);

    TEST_ASSERT_NOT_CNULLPTR(matched_substring);
    TEST_ASSERT_EQUAL_STRING("A123b", matched_substring);

    // Reset regex for reuse
    fscl_regex_reset(&my_regex);

    // Match again with a different text
    const char *new_text = "xyab";
    TEST_ASSERT_TRUE(fscl_regex_match(&my_regex, new_text));

    // Clean up
    TEST_ASSERT_EQUAL_STRING("xyab", fscl_regex_get_matched_substring(&my_regex));
}

XTEST_CASE(test_regex_match_and_extract_no_match) {
    cregex my_regex;
    const char *pattern_no_match = "x.*y";
    TEST_ASSERT_TRUE(fscl_regex_create(&my_regex, pattern_no_match) == 0);
    TEST_ASSERT_FALSE(fscl_regex_match(&my_regex, "abc") == 1);
}

XTEST_CASE(test_regex_match_and_extract_empty_pattern) {
    cregex my_regex;
    const char *empty_pattern = "";
    TEST_ASSERT_TRUE(fscl_regex_create(&my_regex, empty_pattern) == 0);
    TEST_ASSERT_TRUE(fscl_regex_match(&my_regex, "abc") == 1);
}

XTEST_CASE(test_regex_match_and_extract_single_char_pattern) {
    cregex my_regex;
    const char *single_char_pattern = "a";
    TEST_ASSERT_TRUE(fscl_regex_create(&my_regex, single_char_pattern) == 0);
    TEST_ASSERT_TRUE(fscl_regex_match(&my_regex, "abc") == 1);
}

XTEST_CASE(test_regex_match_and_extract_star_pattern) {
    cregex my_regex;
    const char *star_pattern = "*";
    TEST_ASSERT_TRUE(fscl_regex_create(&my_regex, star_pattern) == 0);
    TEST_ASSERT_TRUE(fscl_regex_match(&my_regex, "abc") == 1);
}

XTEST_CASE(test_regex_match_and_extract_dot_star_pattern) {
    cregex my_regex;
    const char *dot_star_pattern = ".*";
    TEST_ASSERT_TRUE(fscl_regex_create(&my_regex, dot_star_pattern) == 0);
    TEST_ASSERT_TRUE(fscl_regex_match(&my_regex, "abc") == 1);
}

//
// XUNIT-TEST RUNNER
//
XTEST_DEFINE_POOL(test_regex_group) {
    XTEST_RUN_UNIT(test_regex_match_and_extract_normal);
    XTEST_RUN_UNIT(test_regex_match_and_extract_no_match);
    XTEST_RUN_UNIT(test_regex_match_and_extract_empty_pattern);
    XTEST_RUN_UNIT(test_regex_match_and_extract_single_char_pattern);
    XTEST_RUN_UNIT(test_regex_match_and_extract_star_pattern);
    XTEST_RUN_UNIT(test_regex_match_and_extract_dot_star_pattern);
} // end of function main
