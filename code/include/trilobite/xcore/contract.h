/*
   This C header file is part of the Trilobite Stdlib, a collection of utility functions and
   standard data structures for enhancing software development projects. Feel free to use
   and modify these utilities to streamline your software development process.

   Project: Trilobite Stdlib
   Author: Michael Gene Brockus (Dreamer)
   Email: michaelbrockus@gmail.com
   Website: [Trilobite Coder Blog](https://trilobite.home.blog)

   Trilobite Stdlib is designed to provide a robust set of functionalities that can be
   incorporated into various projects. The utilities included in this library aim to optimize
   and standardize common operations, ensuring efficient and reliable code.

   This header file is a part of a broader initiative to support developers in creating secure,
   efficient, and scalable software. Contributions, suggestions, and feedback are welcomed,
   as we strive to continuously improve and expand the capabilities of Trilobite Stdlib.

   License: Apache License 2.0
   SPDX Identifier: Apache-2.0

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software distributed under the License
   is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
   or implied. See the License for the specific language governing permissions and limitations
   under the License.

   The above copyright notice and this permission notice shall be included in all copies or
   substantial portions of the Software.

   Please review the full text of the Apache License 2.0 for the complete terms and conditions.

   (Apache License 2.0: http://www.apache.org/licenses/LICENSE-2.0)
*/
#ifndef TSCL_CONTRACT_H
#define TSCL_CONTRACT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>

// Define the contract type
typedef struct {
    bool (*pre_condition)();
    void (*post_condition)();
} ccontract;

// =================================================================
// create and erase
// =================================================================
ccontract *tscl_contract_create(bool (*pre_condition)(), void (*post_condition)());

// =================================================================
// addintal functions
// =================================================================
bool tscl_contract_check_pre(ccontract *contract);
bool tscl_contract_check_post(ccontract *contract);
bool tscl_contract_assert(bool condition, const char *message);
bool tscl_contract_require_not_null(const void *ptr, const char *param_name);
bool tscl_contract_require_positive(int value, const char *param_name);
bool tscl_contract_require_non_negative(int value, const char *param_name);
bool tscl_contract_require_within_range(int value, int min, int max, const char *param_name);
bool tscl_contract_require_within_double_range(double value, double min, double max, const char *param_name);
bool tscl_contract_require_string_length(const char *str, size_t min_length, size_t max_length, const char *param_name);
bool tscl_contract_require_pointer_equality(const void *ptr1, const void *ptr2, const char *param_name);
bool tscl_contract_require_string_equality(const char *str1, const char *str2, const char *param_name);
bool tscl_contract_require_array_length(const void *array, size_t expected_length, size_t element_size, const char *param_name);
bool tscl_contract_require_custom_condition(bool (*custom_condition)(), const char *param_name);

#ifdef __cplusplus
}
#endif

#endif
