/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.home.blog>
*/
#include "trilobite/xcore/thread.h" // lib source code

#include <trilobite/xtest.h>   // basic test tools
#include <trilobite/xassert.h> // extra asserts

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
    cthread thread1 = thread_create(my_thread_function, (void*)&thread1_number);
    TEST_ASSERT_TRUE(thread1);

    int thread2_number = 2;
    cthread thread2 = thread_create(my_thread_function, (void*)&thread2_number);
    TEST_ASSERT_TRUE(thread2);

    thread_join(thread1);
    thread_join(thread2);

    thread_erase(thread1);
    thread_erase(thread2);
}

//
// XUNIT-TEST RUNNER
//
XTEST_GROUP_DEFINE(test_thread_group) {
    XTEST_RUN_UNIT(test_thread_creation_and_join, runner);
} // end of function main
