/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.home.blog>
*/
#include "trilobite/xcore/observer.h" // lib source code

#include <trilobite/xtest.h>   // basic test tools
#include <trilobite/xassert.h> // extra asserts

//
// XUNIT TEST CASES
//
XTEST_CASE(test_create_and_add_observer) {
    csubject subject;
    tscl_observe_create(&subject);

    cobserver observer;
    observer.update = NULL;  // Update function is not needed for this test

    tscl_observe_add_observer(&subject, &observer);

    TEST_ASSERT_EQUAL_INT(1, subject.numObservers);

    tscl_observe_erase_all(&subject);
}

// Test case for clearing all observers
XTEST_CASE(test_erase_all_observers) {
    csubject subject;
    tscl_observe_create(&subject);

    cobserver observer;
    observer.update = NULL;

    tscl_observe_add_observer(&subject, &observer);

    TEST_ASSERT_EQUAL_INT(1, subject.numObservers);

    tscl_observe_erase_all(&subject);

    TEST_ASSERT_EQUAL_INT(0, subject.numObservers);
}

//
// XUNIT-TEST RUNNER
//
XTEST_GROUP_DEFINE(test_observe_group) {
    XTEST_RUN_UNIT(test_create_and_add_observer, runner);
    XTEST_RUN_UNIT(test_erase_all_observers,  runner);
} // end of function main
