/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.home.blog>
*/
#include "trilobite/xcore/ini.h" // lib source code

#include <trilobite/xtest.h>   // basic test tools
#include <trilobite/xassert.h> // extra asserts

//
// XUNIT TEST CASES
//

// Test case for  tscl_ini_parser_parse
XTEST_CASE(test_ tscl_ini_parser_parse) {
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
XTEST_GROUP_DEFINE(test_ini_group) {
    XTEST_RUN_UNIT(test_ tscl_ini_parser_parse,  runner);
} // end of function main
