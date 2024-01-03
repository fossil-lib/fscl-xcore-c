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
#include "fossil/xcore/thread.h" // lib source code

#include <fossil/xtest.h>   // basic test tools
#include <fossil/xassert.h> // extra asserts

// Thread function definition
// Your thread function
cthread_task(my_thread_function, arg) {
    // Your thread function code goes here
    // Use 'arg' as the input argument
    return CTHREAD_CNULLPTR;
}

//
// XUNIT TEST CASES
//

// Test case for thread creation and join
XTEST_CASE(test_thread_creation_and_join) {
    int thread1_number = 1;
    cthread thread1 = fscl_thread_create(my_thread_function, (void*)&thread1_number);
    TEST_ASSERT_TRUE(thread1);

    int thread2_number = 2;
    cthread thread2 = fscl_thread_create(my_thread_function, (void*)&thread2_number);
    TEST_ASSERT_TRUE(thread2);

    fscl_thread_join(thread1);
    fscl_thread_join(thread2);

    fscl_thread_erase(thread1);
    fscl_thread_erase(thread2);
}

//
// XUNIT-TEST RUNNER
//
XTEST_DEFINE_POOL(test_thread_group) {
    XTEST_RUN_UNIT(test_thread_creation_and_join);
} // end of function main
