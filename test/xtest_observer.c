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
#include "fossil/xcore/observer.h" // lib source code

#include <fossil/xtest.h>   // basic test tools
#include <fossil/xassert.h> // extra asserts

//
// XUNIT TEST CASES
//
XTEST_CASE(test_create_and_add_observer) {
    csubject subject;
    fscl_observe_create(&subject);

    cobserver observer;
    observer.update = NULL;  // Update function is not needed for this test

    fscl_observe_add_observer(&subject, &observer);

    TEST_ASSERT_EQUAL_INT(1, subject.numObservers);

    fscl_observe_erase_all(&subject);
}

// Test case for clearing all observers
XTEST_CASE(test_erase_all_observers) {
    csubject subject;
    fscl_observe_create(&subject);

    cobserver observer;
    observer.update = NULL;

    fscl_observe_add_observer(&subject, &observer);

    TEST_ASSERT_EQUAL_INT(1, subject.numObservers);

    fscl_observe_erase_all(&subject);

    TEST_ASSERT_EQUAL_INT(0, subject.numObservers);
}

//
// XUNIT-TEST RUNNER
//
XTEST_DEFINE_POOL(test_observe_group) {
    XTEST_RUN_UNIT(test_create_and_add_observer);
    XTEST_RUN_UNIT(test_erase_all_observers);
} // end of function main
