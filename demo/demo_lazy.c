/*  ----------------------------------------------------------------------------
    File: demo_lazy.c

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
#include "trilobite/xcore/lazy.h" // lib source code
#include <stdio.h>

int main() {
    // Create lazy types for different data types
    clazy intLazy = tscl_lazy_create(CLAZY_INT);
    printf("Result (int): %d\n", tscl_lazy_force_int(&intLazy));
    tscl_lazy_destroy(&intLazy);

    clazy boolLazy = tscl_lazy_create(CLAZY_BOOL);
    printf("Result (bool): %s\n", tscl_lazy_force_bool(&boolLazy) ? "true" : "false");
    tscl_lazy_destroy(&boolLazy);

    clazy charLazy = tscl_lazy_create(CLAZY_CHAR);
    printf("Result (char): %c\n", tscl_lazy_force_char(&charLazy));
    tscl_lazy_destroy(&charLazy);

    clazy stringLazy = tscl_lazy_create(CLAZY_STRING);
    printf("Result (string): %s\n", tscl_lazy_force_string(&stringLazy));
    tscl_lazy_destroy(&stringLazy);

    clazy nullLazy = tscl_lazy_create(CLAZY_NULL);
    // No evaluation needed for null type
    tscl_lazy_destroy(&nullLazy);

    // Create and force a lazy sequence
    clazy sequenceLazy = tscl_lazy_sequence();
    for (int i = 0; i < 5; ++i) {
        printf("Sequence Element: %d\n", tscl_lazy_sequence_force(&sequenceLazy, i));
    }
    tscl_lazy_destroy(&sequenceLazy);

    return 0;
} // end of func
