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
#include "fossil/xcore/error.h" // lib source code

#include <fossil/xtest.h>   // basic test tools
#include <fossil/xassert.h> // extra asserts

//
// XUNIT TEST CASES
//

// Test case 1: Check initial error state
XTEST_CASE(test_initial_error_state) {
    TEST_ASSERT_EQUAL(FSCL_CERROR_SUCCESS, FSCL_CURRENT_ERROR);
    TEST_ASSERT_EQUAL_CSTRING("No error.", fscl_error_what());
}

// Test case 2: Set and retrieve an error code
XTEST_CASE(test_set_and_retrieve_error_code) {
    fscl_error_set(FSCL_CERROR_INVALID_INPUT);
    TEST_ASSERT_EQUAL(FSCL_CERROR_INVALID_INPUT, FSCL_CURRENT_ERROR);
    TEST_ASSERT_EQUAL_CSTRING("Invalid input.", fscl_error_what());
}

// Test case 3: Log an error message
XTEST_CASE(test_error_log) {
    // Clear the last logged error
    last_logged_error[0] = '\0';
    last_logged_error_len = 0;

    // Log an error message
    fscl_error_log("Test error message");

    // Check if the error message is logged correctly
    TEST_ASSERT_EQUAL_CSTRING("Test error message", last_logged_error);
    TEST_ASSERT_EQUAL(strlen("Test error message"), last_logged_error_len);
}

// Test case 4: Set and retrieve a different error code
XTEST_CASE(test_set_and_retrieve_different_error_code) {
    fscl_error_set(FSCL_CERROR_MEMORY_ALLOCATION_FAILED);
    TEST_ASSERT_EQUAL(FSCL_CERROR_MEMORY_ALLOCATION_FAILED, FSCL_CURRENT_ERROR);
    TEST_ASSERT_EQUAL_CSTRING("Memory allocation failed.", fscl_error_what());
}

// Test case 5: Log another error message
XTEST_CASE(test_error_log_another_message) {
    // Clear the last logged error
    last_logged_error[0] = '\0';
    last_logged_error_len = 0;

    // Log another error message
    fscl_error_log("Another error message");

    // Check if the error message is logged correctly
    TEST_ASSERT_EQUAL_CSTRING("Another error message", last_logged_error);
    TEST_ASSERT_EQUAL(strlen("Another error message"), last_logged_error_len);
}

// Test case 6: Check if setting the same error code doesn't change the logged error
XTEST_CASE(test_set_same_error_code_no_change) {
    fscl_error_set(FSCL_CERROR_MEMORY_ALLOCATION_FAILED);
    TEST_ASSERT_EQUAL(FSCL_CERROR_MEMORY_ALLOCATION_FAILED, FSCL_CURRENT_ERROR);
    TEST_ASSERT_EQUAL_CSTRING("Memory allocation failed.", fscl_error_what());
    TEST_ASSERT_EQUAL_CSTRING("Another error message", last_logged_error);
    TEST_ASSERT_EQUAL(strlen("Another error message"), last_logged_error_len);
}

// Test case 7: Log an error message with memorization
XTEST_CASE(test_error_log_with_memorization) {
    // Clear the last logged error
    last_logged_error[0] = '\0';
    last_logged_error_len = 0;

    // Log an error message
    fscl_error_log("Another error message");

    // Check if the error message is not logged again
    TEST_ASSERT_EQUAL_CSTRING("", last_logged_error);
    TEST_ASSERT_EQUAL(0, last_logged_error_len);
}

// Test case 8: Log a new error message with memorization
XTEST_CASE(test_error_log_new_message_with_memorization) {
    // Clear the last logged error
    last_logged_error[0] = '\0';
    last_logged_error_len = 0;

    // Log a new error message
    fscl_error_log("New error message");

    // Check if the new error message is logged correctly
    TEST_ASSERT_EQUAL_CSTRING("New error message", last_logged_error);
    TEST_ASSERT_EQUAL(strlen("New error message"), last_logged_error_len);
}

// Test case 9: Check initial error state after logging an error
XTEST_CASE(test_initial_error_state_after_logging) {
    // Clear the last logged error
    last_logged_error[0] = '\0';
    last_logged_error_len = 0;

    // Log an error message
    fscl_error_log("Error during testing");

    // Check if the initial error state is restored
    TEST_ASSERT_EQUAL(FSCL_CERROR_SUCCESS, FSCL_CURRENT_ERROR);
    TEST_ASSERT_EQUAL_CSTRING("No error.", fscl_error_what());
    TEST_ASSERT_EQUAL_CSTRING("Error during testing", last_logged_error);
    TEST_ASSERT_EQUAL(strlen("Error during testing"), last_logged_error_len);
}

// Test case 10: Log a new error message with memorization after resetting errors
XTEST_CASE(test_error_log_after_reset_with_memorization) {
    // Clear the last logged error
    last_logged_error[0] = '\0';
    last_logged_error_len = 0;

    // Reset errors
    fscl_error_set(FSCL_CERROR_SUCCESS);

    // Log a new error message
    fscl_error_log("Error after resetting");

    // Check if the new error message is logged correctly
    TEST_ASSERT_EQUAL_CSTRING("Error after resetting", last_logged_error);
    TEST_ASSERT_EQUAL(strlen("Error after resetting"), last_logged_error_len);
}

//
// XUNIT-TEST RUNNER
//
XTEST_DEFINE_POOL(test_error_group) {
    XTEST_RUN_UNIT(test_initial_error_state);
    XTEST_RUN_UNIT(test_set_and_retrieve_error_code);
    XTEST_RUN_UNIT(test_error_log);
    XTEST_RUN_UNIT(test_set_and_retrieve_different_error_code);
    XTEST_RUN_UNIT(test_error_log_another_message);
    XTEST_RUN_UNIT(test_set_same_error_code_no_change);
    XTEST_RUN_UNIT(test_error_log_with_memorization);
    XTEST_RUN_UNIT(test_error_log_new_message_with_memorization);
    XTEST_RUN_UNIT(test_initial_error_state_after_logging);
    XTEST_RUN_UNIT(test_error_log_after_reset_with_memorization);
} // end of function main
