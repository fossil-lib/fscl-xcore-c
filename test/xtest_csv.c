/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.home.blog>
*/
#include "trilobite/xcore/csv.h" // lib source code

#include <trilobite/xtest.h>   // basic test tools
#include <trilobite/xassert.h> // extra asserts

//
// XUNIT TEST CASES
//

XTEST_CASE(test_create_and_erase_csv) {
    ccsv* csv = csv_parser_create();
    TEST_ASSERT_NOT_NULL_PTR(csv);

    csv_parser_erase(&csv);
    TEST_ASSERT_NULL_PTR(csv);
}

XTEST_CASE(test_update_and_get_cell) {
    ccsv* csv = csv_parser_create();
    FILE* csv_file = fopen("eco_products.csv", "r");
    TEST_ASSERT_NOT_NULL_PTR(csv_file);

    csv_parser_parse(csv_file, &csv);

    // Check the initial stock value of "Reusable Water Bottle"
    const char* initial_stock = csv_parser_getter(csv, 1, 3);
    TEST_ASSERT_EQUAL_STRING("100", initial_stock);

    // Update the stock value of "Reusable Water Bottle"
    csv_parser_setter(&csv, 1, 3, "80");

    // Check if the stock value has been updated
    const char* updated_stock = csv_parser_getter(csv, 1, 3);
    TEST_ASSERT_EQUAL_STRING("80", updated_stock);

    csv_parser_erase(&csv);
    fclose(csv_file);
}

//
// XUNIT-TEST RUNNER
//
XTEST_GROUP_DEFINE(test_csv_group) {
    XTEST_RUN_UNIT(test_create_and_erase_csv, runner);
    XTEST_RUN_UNIT(test_update_and_get_cell,  runner);
} // end of function main
