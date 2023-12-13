/*  ----------------------------------------------------------------------------
    File: demo_lambda.c

    Description:
    This demo file serves as a showcase of the Trilobite Stdlib in action. It provides
    example code snippets and usage scenarios to help users understand how to leverage
    the library's features and functions in their own projects.

    Author: Michael Gene Brockus (Dreamer)
    Email: michaelbrockus@gmail.com
    Website: [Trilobite Coder Blog](https://trilobite.home.blog)

    Project: Trilobite Stdlib

    License: Apache License 2.0
    SPDX Identifier: Apache-2.0

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0.

    Unless required by applicable law or agreed to in writing, software distributed under the License
    is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
    or implied. See the License for the specific language governing permissions and limitations
    under the License.

    Please review the full text of the Apache License 2.0 for the complete terms and conditions.

    (Apache License 2.0: http://www.apache.org/licenses/LICENSE-2.0)
    ----------------------------------------------------------------------------
*/
#include "trilobite/xcore/lambda.h" // lib source code

// Lambda function that prints an integer
void print_integer_lambda(void* data) {
    int* value = (int*)data;
    printf("Lambda invoked with value: %d\n", *value);
} // end of func

int main() {
    clambda lambda;
    int data = 42;

    // Initialize the lambda with the print_integer_lambda function
    lambda_init(&lambda, print_integer_lambda);

    // Invoke the lambda with an integer data
    lambda_invoke(&lambda, (void*)&data);

    return 0;
} // end of func
