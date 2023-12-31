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
#include "fossil/xcore/datetime.h" // lib source code

#include <fossil/xtest.h>   // basic test tools
#include <fossil/xassert.h> // extra asserts

//
// XUNIT TEST DATA
//
XTEST_DATA(FormatTestData) {
    cdatetime datetime;
} format;

//
// XUNIT TEST CASES
//

// Test cases for datetime_get_current_parse_military function.
XTEST_CASE(datetime_let_parse_military_success) {
    const char *input = "2023-09-28 15:30:00 +0300";
    TEST_ASSERT_TRUE(fscl_datetime_get_current_parse_military(input, &format.datetime));
}

XTEST_CASE(datetime_let_parse_military_failure) {
    const char *input = "invalid_datetime_string";
    TEST_ASSERT_FALSE(fscl_datetime_get_current_parse_military(input, &format.datetime));
}

// Test cases for datetime_get_current_parse_12_hour function.
XTEST_CASE(datetime_let_parse_12_hour_success) {
    const char *input = "2023-09-28 03:30 PM +0300";
    TEST_ASSERT_TRUE(fscl_datetime_get_current_parse_12_hour(input, &format.datetime));
}

XTEST_CASE(datetime_let_parse_12_hour_failure) {
    const char *input = "invalid_datetime_string";
    TEST_ASSERT_FALSE(fscl_datetime_get_current_parse_12_hour(input, &format.datetime));
}

// Test cases for datetime_get_current_parse_human_readable function.
XTEST_CASE(datetime_let_parse_human_readable_success) {
    const char *input = "28-Sep-2023, 3:30 PM";
    TEST_ASSERT_TRUE(fscl_datetime_get_current_parse_human_readable(input, &format.datetime));
}

XTEST_CASE(datetime_let_parse_human_readable_failure) {
    const char *input = "invalid_datetime_string";
    TEST_ASSERT_FALSE(fscl_datetime_get_current_parse_human_readable(input, &format.datetime));
}

// Test case for an empty input string
XTEST_CASE(datetime_edge_parse_military_empty) {
    const char *input = "";
    TEST_ASSERT_FALSE(fscl_datetime_get_current_parse_military(input, &format.datetime));
}

// Test case for an invalid time zone
XTEST_CASE(datetime_edge_parse_military_invalid_timezone) {
    const char *input = "2023-09-28 15:30:00 invalid_timezone";
    TEST_ASSERT_FALSE(fscl_datetime_get_current_parse_military(input, &format.datetime));
}

// Test case for an invalid input format
XTEST_CASE(datetime_edge_parse_military_invalid_format) {
    const char *input = "invalid_format";
    TEST_ASSERT_FALSE(fscl_datetime_get_current_parse_military(input, &format.datetime));
}

// Test case for an empty input string
XTEST_CASE(datetime_edge_parse_12_hour_empty) {
    const char *input = "";
    TEST_ASSERT_FALSE(fscl_datetime_get_current_parse_12_hour(input, &format.datetime));
}

// Test case for an invalid time zone
XTEST_CASE(datetime_edge_parse_12_hour_invalid_timezone) {
    const char *input = "2023-09-28 03:30 PM invalid_timezone";
    TEST_ASSERT_FALSE(fscl_datetime_get_current_parse_12_hour(input, &format.datetime));
}

// Test case for an invalid input format
XTEST_CASE(datetime_edge_parse_12_hour_invalid_format) {
    const char *input = "invalid_format";
    TEST_ASSERT_FALSE(fscl_datetime_get_current_parse_12_hour(input, &format.datetime));
}

// Test case for an empty input string
XTEST_CASE(datetime_edge_parse_human_readable_empty) {
    const char *input = "";
    TEST_ASSERT_FALSE(fscl_datetime_get_current_parse_human_readable(input, &format.datetime));
}

// Test case for an invalid input format
XTEST_CASE(datetime_edge_parse_human_readable_invalid_format) {
    const char *input = "invalid_format";
    TEST_ASSERT_FALSE(fscl_datetime_get_current_parse_human_readable(input, &format.datetime));
}

// Define the test cases
XTEST_CASE(test_trilo_xcore_get_current_datetime) {
    cdatetime current_datetime;
    
    // Call the function to get the current date and time
    fscl_datetime_get_current(&current_datetime);

    // Assuming the function worked correctly, you can check individual components
    TEST_ASSERT_TRUE(current_datetime.year >= 2023);  // Replace 2023 with the current year
    TEST_ASSERT_TRUE(current_datetime.month >= 1 && current_datetime.month <= 12);
    TEST_ASSERT_TRUE(current_datetime.day >= 1 && current_datetime.day <= 31);
    TEST_ASSERT_TRUE(current_datetime.hour >= 0 && current_datetime.hour <= 23);
    TEST_ASSERT_TRUE(current_datetime.minute >= 0 && current_datetime.minute <= 59);
    TEST_ASSERT_TRUE(current_datetime.second >= 0 && current_datetime.second <= 59);
    TEST_ASSERT_EQUAL_INT(-1, current_datetime.ampm);  // Assuming ampm is set to -1 as specified in the function
    // You can add additional assertions based on your specific requirements
}

//
// XUNIT-TEST RUNNER
//
XTEST_DEFINE_POOL(test_datetiime_group) {
    XTEST_RUN_UNIT(test_trilo_xcore_get_current_datetime);
    XTEST_RUN_UNIT(datetime_let_parse_12_hour_failure);
    XTEST_RUN_UNIT(datetime_let_parse_12_hour_success);
    XTEST_RUN_UNIT(datetime_let_parse_human_readable_failure);
    XTEST_RUN_UNIT(datetime_let_parse_human_readable_success);
    XTEST_RUN_UNIT(datetime_let_parse_military_failure);
    XTEST_RUN_UNIT(datetime_let_parse_military_success);
    XTEST_RUN_UNIT(datetime_edge_parse_military_empty);
    XTEST_RUN_UNIT(datetime_edge_parse_military_invalid_timezone);
    XTEST_RUN_UNIT(datetime_edge_parse_military_invalid_format);
    XTEST_RUN_UNIT(datetime_edge_parse_12_hour_empty);
    XTEST_RUN_UNIT(datetime_edge_parse_12_hour_invalid_timezone);
    XTEST_RUN_UNIT(datetime_edge_parse_12_hour_invalid_format);
    XTEST_RUN_UNIT(datetime_edge_parse_human_readable_empty);
    XTEST_RUN_UNIT(datetime_edge_parse_human_readable_invalid_format);
} // end of function main
