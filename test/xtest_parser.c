/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.home.blog>
*/
#include "trilobite/xcore/parser.h" // lib source code

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

XTEST_CASE(test_create_and_erase_csv) {
    ccsv* csv =  tscl_csv_parser_create();
    TEST_ASSERT_NOT_NULL_PTR(csv);

     tscl_csv_parser_erase(&csv);
    TEST_ASSERT_NULL_PTR(csv);
}

XTEST_CASE(test_update_and_get_cell) {
    ccsv* csv =  tscl_csv_parser_create();
    FILE* csv_file = fopen("eco_products.csv", "r");
    TEST_ASSERT_NOT_NULL_PTR(csv_file);

     tscl_csv_parser_parse(csv_file, &csv);

    // Check the initial stock value of "Reusable Water Bottle"
    const char* initial_stock =  tscl_csv_parser_getter(csv, 1, 3);
    TEST_ASSERT_EQUAL_STRING("100", initial_stock);

    // Update the stock value of "Reusable Water Bottle"
     tscl_csv_parser_setter(&csv, 1, 3, "80");

    // Check if the stock value has been updated
    const char* updated_stock =  tscl_csv_parser_getter(csv, 1, 3);
    TEST_ASSERT_EQUAL_STRING("80", updated_stock);

     tscl_csv_parser_erase(&csv);
    fclose(csv_file);
}

XTEST_CASE(test_tscl_ini_parser_parse) {
    FILE* file = fopen("test_config.ini", "r");
    TEST_ASSERT_NOT_NULL_PTR(file);

    cini* iniData;
     tscl_ini_parser_create(&iniData);
    TEST_ASSERT_NOT_NULL_PTR(iniData);

    // Test parsing of a sample INI file
     tscl_ini_parser_parse(file, &iniData);

    // Clean up
    fclose(file);
     tscl_ini_parser_erase(&iniData);
}

//
// XUNIT-TEST RUNNER
//
XTEST_GROUP_DEFINE(test_parser_group) {
    XTEST_RUN_UNIT(test_tscl_json_parser_basic,         runner);
    XTEST_RUN_UNIT(test_tscl_json_parser_invalid_file,  runner);
    XTEST_RUN_UNIT(test_tscl_json_parser_invalid_json,  runner);
    XTEST_RUN_UNIT(test_tscl_json_parser_getter_setter, runner);
    XTEST_RUN_UNIT(test_create_and_erase_csv, runner);
    XTEST_RUN_UNIT(test_update_and_get_cell,  runner);
    XTEST_RUN_UNIT(test_tscl_ini_parser_parse,  runner);
} // end of function main
