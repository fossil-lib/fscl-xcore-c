/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.home.blog>
*/
#include "trilobite/xcore/contract.h" // lib source code

#include <trilobite/xtest.h>   // basic test tools
#include <trilobite/xassert.h> // extra asserts
#include <trilobite/xmock.h> // mocking functions

// Function with contracts
XMOCK_FUNC_DEF(void, example_function, int *array, size_t array_length, const char *str, void *ptr) {
    // Create contracts
    ccontract *pre_condition_contract = tscl_contract_create(example_pre_condition, NULL);
    ccontract *post_condition_contract = tscl_contract_create(NULL, example_post_condition);

    // Pre-condition checks
    tscl_contract_require_not_null(array, "array");
    tscl_contract_require_array_length(array, array_length, sizeof(int), "array");
    tscl_contract_require_not_null(str, "str");
    tscl_contract_require_string_length(str, 1, 10, "str");
    tscl_contract_require_not_null(ptr, "ptr");

    // Post-condition checks
    tscl_contract_check_pre(pre_condition_contract);

    // Your function logic here

    tscl_contract_check_post(post_condition_contract);

    // Clean up
    free(pre_condition_contract);
    free(post_condition_contract);
}

//
// XUNIT TEST CASES
//
XTEST_CASE(test_valid_basic_call) {
    int array[] = {1, 2, 3, 4, 5};
    const char *str = "Hello";
    void *ptr = malloc(sizeof(int));

    // Call the function with valid parameters
    xmock_example_function(array, 5, str, ptr);

    // Clean up
    free(ptr);
}

XTEST_CASE(test_invalid_call) {
    // Call the function with invalid parameters to demonstrate a violation
    TEST_ASSERT_FALSE(tscl_contract_require_not_null(NULL, "test_pointer"));
    TEST_ASSERT_FALSE(tscl_contract_require_string_length("TooLongString", 1, 10, "test_string"));
    TEST_ASSERT_FALSE(tscl_contract_require_array_length(NULL, 10, sizeof(int), "test_array"));
    TEST_ASSERT_FALSE(tscl_contract_require_custom_condition(NULL, "test_custom_condition"));
}

XTEST_CASE(test_valid_call) {
    int array[] = {1, 2, 3, 4, 5};
    const char *str = "Hello";
    void *ptr = malloc(sizeof(int));

    // Create contracts
    ccontract *pre_condition_contract = tscl_contract_create(NULL, NULL);
    ccontract *post_condition_contract = tscl_contract_create(NULL, NULL);

    // Pre-condition checks
    TEST_ASSERT_TRUE(tscl_contract_require_not_null(array, "array"));
    TEST_ASSERT_TRUE(tscl_contract_require_array_length(array, 5, sizeof(int), "array"));
    TEST_ASSERT_TRUE(tscl_contract_require_not_null(str, "str"));
    TEST_ASSERT_TRUE(tscl_contract_require_string_length(str, 1, 10, "str"));
    TEST_ASSERT_TRUE(tscl_contract_require_not_null(ptr, "ptr"));

    // Post-condition checks
    TEST_ASSERT_TRUE(tscl_contract_check_pre(pre_condition_contract));

    // Your function logic here

    TEST_ASSERT_TRUE(tscl_contract_check_post(post_condition_contract));

    // Clean up
    free(ptr);
    free(pre_condition_contract);
    free(post_condition_contract);
}

//
// XUNIT-TEST RUNNER
//
XTEST_GROUP_DEFINE(test_contract_group) {
    XTEST_RUN_UNIT(test_valid_basic_call,  runner);
    XTEST_RUN_UNIT(test_invalid_call,  runner);
    XTEST_RUN_UNIT(test_valid_call,  runner);
} // end of function main
