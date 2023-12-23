/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.home.blog>
*/
#include "trilobite/xcore/regex.h" // lib source code

#include <trilobite/xtest.h>   // basic test tools
#include <trilobite/xassert.h> // extra asserts

//
// XUNIT TEST CASES
//

// Test case for initializing error with a message
XTEST_CASE(test_regex_match_and_extract_normal) {
    cregex my_regex;
    const char *pattern = "a.*b";
    const char *text = "@A123b!";

    // Initialize regex
    TEST_ASSERT_EQUAL_INT(0, tscl_regex_create(&my_regex, pattern));

    // Match and extract substring
    const char *matched_substring = tscl_regex_match_and_extract(&my_regex, text);

    TEST_ASSERT_NOT_NULL_PTR(matched_substring);
    TEST_ASSERT_EQUAL_STRING("A123b", matched_substring);

    // Reset regex for reuse
    tscl_regex_reset(&my_regex);

    // Match again with a different text
    const char *new_text = "xyab";
    TEST_ASSERT_TRUE(tscl_regex_match(&my_regex, new_text));

    // Clean up
    TEST_ASSERT_EQUAL_STRING("xyab", tscl_regex_get_matched_substring(&my_regex));
}

XTEST_CASE(test_regex_match_and_extract_no_match) {
    cregex my_regex;
    const char *pattern_no_match = "x.*y";
    TEST_ASSERT_TRUE(tscl_regex_create(&my_regex, pattern_no_match) == 0);
    TEST_ASSERT_FALSE(tscl_regex_match(&my_regex, "abc") == 1);
}

XTEST_CASE(test_regex_match_and_extract_empty_pattern) {
    cregex my_regex;
    const char *empty_pattern = "";
    TEST_ASSERT_TRUE(tscl_regex_create(&my_regex, empty_pattern) == 0);
    TEST_ASSERT_TRUE(tscl_regex_match(&my_regex, "abc") == 1);
}

XTEST_CASE(test_regex_match_and_extract_single_char_pattern) {
    cregex my_regex;
    const char *single_char_pattern = "a";
    TEST_ASSERT_TRUE(tscl_regex_create(&my_regex, single_char_pattern) == 0);
    TEST_ASSERT_TRUE(tscl_regex_match(&my_regex, "abc") == 1);
}

XTEST_CASE(test_regex_match_and_extract_star_pattern) {
    cregex my_regex;
    const char *star_pattern = "*";
    TEST_ASSERT_TRUE(tscl_regex_create(&my_regex, star_pattern) == 0);
    TEST_ASSERT_TRUE(tscl_regex_match(&my_regex, "abc") == 1);
}

XTEST_CASE(test_regex_match_and_extract_dot_star_pattern) {
    cregex my_regex;
    const char *dot_star_pattern = ".*";
    TEST_ASSERT_TRUE(tscl_regex_create(&my_regex, dot_star_pattern) == 0);
    TEST_ASSERT_TRUE(tscl_regex_match(&my_regex, "abc") == 1);
}

//
// XUNIT-TEST RUNNER
//
XTEST_GROUP_DEFINE(test_regex_group) {
    XTEST_RUN_UNIT(test_regex_match_and_extract_normal,              runner);
    XTEST_RUN_UNIT(test_regex_match_and_extract_no_match,            runner);
    XTEST_RUN_UNIT(test_regex_match_and_extract_empty_pattern,       runner);
    XTEST_RUN_UNIT(test_regex_match_and_extract_single_char_pattern, runner);
    XTEST_RUN_UNIT(test_regex_match_and_extract_star_pattern,        runner);
    XTEST_RUN_UNIT(test_regex_match_and_extract_dot_star_pattern,    runner);
} // end of function main
