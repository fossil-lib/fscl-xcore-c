/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.home.blog>
*/
#include "trilobite/xcore/lambda.h" // lib source code

#include <trilobite/xtest.h>   // basic test tools
#include <trilobite/xmock.h>   // handy mock utilites
#include <trilobite/xassert.h> // extra asserts

//
// XMOCK STUBS
//
XMOCK_FUNC_DEF(void, lambda_function, void* data) {
    int* value = (int*)data;
    (*value)++;
} // end of stub

// Mock lambda function for the additional test cases
XMOCK_FUNC_DEF(void, different_lambda_function, void* data) {
    int* intData = (int*)data;
    // Increment the data by a different value
    (*intData) += 5;
}


//
// XUNIT TEST CASES
//

// Test case for lambda_init
XTEST_CASE(lambda_let_lambda_init) {
    clambda lambda;
    
    // Initialize the lambda with the xmock_lambda_function
    lambda_init(&lambda, xmock_lambda_function);

    // Ensure that the lambda's function pointer is set correctly
    TEST_ASSERT_EQUAL_PTR(xmock_lambda_function, lambda.func);
}

// Test case for lambda_invoke
XTEST_CASE(lambda_let_lambda_invoke) {
    clambda lambda;
    int data = 42;
    
    // Initialize the lambda with the xmock_lambda_function
    lambda_init(&lambda, xmock_lambda_function);

    // Invoke the lambda with the data
    lambda_invoke(&lambda, (void*)&data);

    // Ensure that the lambda function has modified the data
    TEST_ASSERT_EQUAL_INT(43, data);
}

// Additional Test case for lambda_init
XTEST_CASE(lambda_let_lambda_init_additional) {
    clambda lambda;
    
    // Initialize the lambda with a different function
    lambda_init(&lambda, xmock_different_lambda_function);

    // Ensure that the lambda's function pointer is set correctly
    TEST_ASSERT_EQUAL_PTR(xmock_different_lambda_function, lambda.func);
}

// Additional Test case for lambda_invoke
XTEST_CASE(lambda_let_lambda_invoke_additional) {
    clambda lambda;
    int data = 100;
    
    // Initialize the lambda with a different function
    lambda_init(&lambda, xmock_different_lambda_function);

    // Invoke the lambda with the data
    lambda_invoke(&lambda, (void*)&data);

    // Ensure that the lambda function has modified the data in a different way
    TEST_ASSERT_EQUAL_INT(105, data);
}

// Test case for lambda_invoke with a lambda having a NULL function pointer
XTEST_CASE(lambda_let_lambda_invoke_null_function) {
    clambda lambda;
    int data = 77;
    
    // Initialize the lambda with a NULL function pointer
    lambda_init(&lambda, NULL);

    // Invoke the lambda with the data
    lambda_invoke(&lambda, (void*)&data);

    // Ensure that the lambda function has not modified the data
    TEST_ASSERT_EQUAL_INT(77, data);
}


//
// XUNIT-TEST RUNNER
//
XTEST_GROUP_DEFINE(test_lambda_group) {
    XTEST_RUN_UNIT(lambda_let_lambda_init,   runner);
    XTEST_RUN_UNIT(lambda_let_lambda_invoke, runner);
    XTEST_RUN_UNIT(lambda_let_lambda_init_additional,      runner);
    XTEST_RUN_UNIT(lambda_let_lambda_invoke_additional,    runner);
    XTEST_RUN_UNIT(lambda_let_lambda_invoke_null_function, runner);
} // end of function main
