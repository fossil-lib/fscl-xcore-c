/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.home.blog>
*/
#include "trilobite/xcore/json.h" // lib source code

#include <trilobite/xtest.h>   // basic test tools
#include <trilobite/xassert.h> // extra asserts

//
// XUNIT-CASES: list of test cases testing project features
//
XTEST_CASE(test_tscl_json_parser_basic) {
    FILE* jsonFile = fopen("basic.json", "r");
    TEST_ASSERT_NOT_NULL_PTR(jsonFile);

    cjson* jsonData =  tscl_json_parser_create();
    TEST_ASSERT_NOT_NULL_PTR(jsonData);

    TEST_ASSERT_TRUE( tscl_json_parser_parse(jsonFile, &jsonData));

    fclose(jsonFile);
     tscl_json_parser_erase(&jsonData);
}

XTEST_CASE(test_tscl_json_parser_invalid_file) {
    FILE* jsonFile = fopen("nonexistent.json", "r");
    TEST_ASSERT_NULL_PTR(jsonFile);

    cjson* jsonData =  tscl_json_parser_create();
    TEST_ASSERT_NOT_NULL_PTR(jsonData);

    TEST_ASSERT_FALSE( tscl_json_parser_parse(jsonFile, &jsonData));

    fclose(jsonFile);
     tscl_json_parser_erase(&jsonData);
}

XTEST_CASE(test_tscl_json_parser_invalid_json) {
    FILE* jsonFile = fopen("invalid.json", "r");
    TEST_ASSERT_NOT_NULL_PTR(jsonFile);

    cjson* jsonData =  tscl_json_parser_create();
    TEST_ASSERT_NOT_NULL_PTR(jsonData);

    TEST_ASSERT_FALSE( tscl_json_parser_parse(jsonFile, &jsonData));

    fclose(jsonFile);
     tscl_json_parser_erase(&jsonData);
}

XTEST_CASE(test_tscl_json_parser_getter_setter) {
    cjson* jsonData =  tscl_json_parser_create();
    TEST_ASSERT_NOT_NULL_PTR(jsonData);

    const char* testString = "{\"key\":\"value\"}";

     tscl_json_parser_setter(&jsonData, testString);
    TEST_ASSERT_EQUAL_STRING(testString,  tscl_json_parser_getter(&jsonData));

     tscl_json_parser_erase(&jsonData);
}

//
// XUNIT-TEST RUNNER
//
XTEST_GROUP_DEFINE(test_json_group) {
    XTEST_RUN_UNIT(test_tscl_json_parser_basic,         runner);
    XTEST_RUN_UNIT(test_tscl_json_parser_invalid_file,  runner);
    XTEST_RUN_UNIT(test_tscl_json_parser_invalid_json,  runner);
    XTEST_RUN_UNIT(test_tscl_json_parser_getter_setter, runner);
} // end of function main
