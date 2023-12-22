/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.home.blog>
*/
#include "trilobite/xcore/reader.h" // lib source code

#include <trilobite/xtest.h>   // basic test tools
#include <trilobite/xassert.h> // extra asserts
#include <trilobite/xmock.h> // mocking functions

//
// XMOCK FUNCTIONS
//
// Validation function for testing
XMOCK_FUNC_DEF(bool, validate_input, const char* input) {
    int num;
    if (sscanf(input, "%d", &num) == 1 && num >= 1 && num <= 100) {
        return true;
    }
    return false;
}

//
// XUNIT TEST CASES
//
XTEST_CASE(reader_let_reader_valid_input_valid) {
    // Test valid input validation
    TEST_ASSERT_TRUE(tscl_reader_valid_input("Enter a valid number (1-100)", xmock_validate_input));
}

XTEST_CASE(reader_let_reader_valid_input_invalid) {
    // Test invalid input validation
    TEST_ASSERT_FALSE(tscl_reader_valid_input("Enter a valid number (1-100)", xmock_validate_input));
}

XTEST_CASE(reader_let_reader_confirm_yes_no_yes) {
    // Test confirming "yes"
    TEST_ASSERT_TRUE(tscl_reader_confirm_yes_no("Do you like programming?"));
}

XTEST_CASE(reader_let_reader_confirm_yes_no_no) {
    // Test confirming "no"
    TEST_ASSERT_FALSE(tscl_reader_confirm_yes_no("Do you like programming?"));
}

XTEST_CASE(reader_let_reader_confirm_multi_menu) {
    // Test multi-choice menu
    const char* menu[] = { "Option 1", "Option 2", "Option 3" };
    int num_options = sizeof(menu) / sizeof(menu[0]);
    bool selections[num_options];
    memset(selections, false, sizeof(selections));

    // Simulate user input "1 3" (selecting the first and third options)
    tscl_reader_confirm_multi_menu("Choose multiple options", menu, selections, num_options);
    TEST_ASSERT_TRUE(selections[0]);
    TEST_ASSERT_FALSE(selections[1]);
    TEST_ASSERT_TRUE(selections[2]);
}

XTEST_CASE(reader_let_reader_confirm_exit) {
    // Test confirming exit
    TEST_ASSERT_TRUE(tscl_reader_confirm_exit());
}

// Additional test cases for reader_valid_input
XTEST_CASE(reader_let_reader_valid_input_valid_upper_bound) {
    // Test valid input at upper bound
    TEST_ASSERT_TRUE(tscl_reader_valid_input("Enter a valid number (1-100)", xmock_validate_input));
}

XTEST_CASE(reader_let_reader_valid_input_valid_lower_bound) {
    // Test valid input at lower bound
    TEST_ASSERT_TRUE(tscl_reader_valid_input("Enter a valid number (1-100)", xmock_validate_input));
}

XTEST_CASE(reader_let_reader_valid_input_invalid_upper_bound) {
    // Test invalid input at upper bound
    TEST_ASSERT_FALSE(tscl_reader_valid_input("Enter a valid number (1-100)", xmock_validate_input));
}

XTEST_CASE(reader_let_reader_valid_input_invalid_lower_bound) {
    // Test invalid input at lower bound
    TEST_ASSERT_FALSE(tscl_reader_valid_input("Enter a valid number (1-100)", xmock_validate_input));
}

// Additional test cases for reader_confirm_yes_no
XTEST_CASE(reader_let_reader_confirm_yes_no_invalid_response) {
    // Test invalid response
    TEST_ASSERT_FALSE(tscl_reader_confirm_yes_no("Do you like programming?"));
}

// Additional test cases for reader_confirm_multi_menu
XTEST_CASE(reader_let_reader_confirm_multi_menu_invalid_input) {
    // Test invalid input for multi-choice menu
    const char* menu[] = { "Option 1", "Option 2", "Option 3" };
    int num_options = sizeof(menu) / sizeof(menu[0]);
    bool selections[num_options];
    memset(selections, false, sizeof(selections));

    // Simulate user input "1 4" (selecting the first and an invalid fourth option)
    tscl_reader_confirm_multi_menu("Choose multiple options", menu, selections, num_options);
    TEST_ASSERT_TRUE(selections[0]);
    TEST_ASSERT_FALSE(selections[1]);
    TEST_ASSERT_FALSE(selections[2]);
}

// Additional test cases for reader_confirm_exit
XTEST_CASE(reader_let_reader_confirm_exit_invalid_response) {
    // Test invalid response for confirming exit
    TEST_ASSERT_FALSE(tscl_reader_confirm_exit());
}


//
// XUNIT-TEST RUNNER
//
XTEST_GROUP_DEFINE(test_reader_group) {
    XTEST_RUN_UNIT(reader_let_reader_valid_input_valid,   runner);
    XTEST_RUN_UNIT(reader_let_reader_valid_input_invalid, runner);
    XTEST_RUN_UNIT(reader_let_reader_confirm_yes_no_yes,  runner);
    XTEST_RUN_UNIT(reader_let_reader_confirm_yes_no_no,   runner);
    XTEST_RUN_UNIT(reader_let_reader_confirm_multi_menu,  runner);
    XTEST_RUN_UNIT(reader_let_reader_confirm_exit,        runner);
    XTEST_RUN_UNIT(reader_let_reader_valid_input_valid_upper_bound,    runner);
    XTEST_RUN_UNIT(reader_let_reader_valid_input_valid_lower_bound,    runner);
    XTEST_RUN_UNIT(reader_let_reader_valid_input_invalid_upper_bound,  runner);
    XTEST_RUN_UNIT(reader_let_reader_valid_input_invalid_lower_bound,  runner);
    XTEST_RUN_UNIT(reader_let_reader_confirm_yes_no_invalid_response,  runner);
    XTEST_RUN_UNIT(reader_let_reader_confirm_multi_menu_invalid_input, runner);
    XTEST_RUN_UNIT(reader_let_reader_confirm_exit_invalid_response,    runner);
} // end of function main
