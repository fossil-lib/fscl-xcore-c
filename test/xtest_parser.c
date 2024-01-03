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
#include "fossil/xcore/parser.h" // lib source code

#include <fossil/xtest.h>   // basic test tools
#include <fossil/xassert.h> // extra asserts

//
// XUNIT-CASES: list of test cases testing project features
//
XTEST_CASE(test_fscl_json_parser_basic) {
    FILE* jsonFile = fopen("basic.json", "r");
    TEST_ASSERT_NOT_CNULLPTR(jsonFile);

    cjson* jsonData =  fscl_json_parser_create();
    TEST_ASSERT_NOT_CNULLPTR(jsonData);

    TEST_ASSERT_TRUE( fscl_json_parser_parse(jsonFile, &jsonData));

    fclose(jsonFile);
     fscl_json_parser_erase(&jsonData);
}

XTEST_CASE(test_fscl_json_parser_invalid_file) {
    FILE* jsonFile = fopen("nonexistent.json", "r");
    TEST_ASSERT_CNULLPTR(jsonFile);

    cjson* jsonData =  fscl_json_parser_create();
    TEST_ASSERT_NOT_CNULLPTR(jsonData);

    TEST_ASSERT_FALSE( fscl_json_parser_parse(jsonFile, &jsonData));

    fclose(jsonFile);
     fscl_json_parser_erase(&jsonData);
}

XTEST_CASE(test_fscl_json_parser_invalid_json) {
    FILE* jsonFile = fopen("invalid.json", "r");
    TEST_ASSERT_NOT_CNULLPTR(jsonFile);

    cjson* jsonData =  fscl_json_parser_create();
    TEST_ASSERT_NOT_CNULLPTR(jsonData);

    TEST_ASSERT_FALSE( fscl_json_parser_parse(jsonFile, &jsonData));

    fclose(jsonFile);
     fscl_json_parser_erase(&jsonData);
}

XTEST_CASE(test_fscl_json_parser_getter_setter) {
    cjson* jsonData =  fscl_json_parser_create();
    TEST_ASSERT_NOT_CNULLPTR(jsonData);

    const char* testString = "{\"key\":\"value\"}";

     fscl_json_parser_setter(&jsonData, testString);
    TEST_ASSERT_EQUAL_STRING(testString,  fscl_json_parser_getter(&jsonData));

     fscl_json_parser_erase(&jsonData);
}

XTEST_CASE(test_create_and_erase_csv) {
    ccsv* csv =  fscl_csv_parser_create();
    TEST_ASSERT_NOT_CNULLPTR(csv);

     fscl_csv_parser_erase(&csv);
    TEST_ASSERT_CNULLPTR(csv);
}

XTEST_CASE(test_update_and_get_cell) {
    ccsv* csv =  fscl_csv_parser_create();
    FILE* csv_file = fopen("eco_products.csv", "r");
    TEST_ASSERT_NOT_CNULLPTR(csv_file);

     fscl_csv_parser_parse(csv_file, &csv);

    // Check the initial stock value of "Reusable Water Bottle"
    const char* initial_stock =  fscl_csv_parser_getter(csv, 1, 3);
    TEST_ASSERT_EQUAL_STRING("100", initial_stock);

    // Update the stock value of "Reusable Water Bottle"
     fscl_csv_parser_setter(&csv, 1, 3, "80");

    // Check if the stock value has been updated
    const char* updated_stock =  fscl_csv_parser_getter(csv, 1, 3);
    TEST_ASSERT_EQUAL_STRING("80", updated_stock);

     fscl_csv_parser_erase(&csv);
    fclose(csv_file);
}

XTEST_CASE(test_fscl_ini_parser_parse) {
    FILE* file = fopen("test_config.ini", "r");
    TEST_ASSERT_NOT_CNULLPTR(file);

    cini* iniData;
     fscl_ini_parser_create(&iniData);
    TEST_ASSERT_NOT_CNULLPTR(iniData);

    // Test parsing of a sample INI file
     fscl_ini_parser_parse(file, &iniData);

    // Clean up
    fclose(file);
     fscl_ini_parser_erase(&iniData);
}

//
// XUNIT-TEST RUNNER
//
XTEST_DEFINE_POOL(test_parser_group) {
    XTEST_RUN_UNIT(test_fscl_json_parser_basic);
    XTEST_RUN_UNIT(test_fscl_json_parser_invalid_file);
    XTEST_RUN_UNIT(test_fscl_json_parser_invalid_json);
    XTEST_RUN_UNIT(test_fscl_json_parser_getter_setter);
    XTEST_RUN_UNIT(test_create_and_erase_csv);
    XTEST_RUN_UNIT(test_update_and_get_cell);
    XTEST_RUN_UNIT(test_fscl_ini_parser_parse);
} // end of function main
