/*  ----------------------------------------------------------------------------
    File: contract.c

    Description:
    This source file contains the code entry point for the Trilobite Stdlib project.
    It demonstrates the usage of various utilities and functions provided by the
    Trilobite Stdlib to enhance software development.

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
#include "trilobite/xcore/contract.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ccontract *tscl_contract_create(bool (*pre_condition)(), void (*post_condition)()) {
    ccontract *contract = (ccontract *)malloc(sizeof(ccontract));
    if (contract != NULL) {
        contract->pre_condition = pre_condition;
        contract->post_condition = post_condition;
    }
    return contract;
}

bool tscl_contract_check_pre(ccontract *contract) {
    if (contract != NULL && contract->pre_condition != NULL) {
        return contract->pre_condition();
    }
    return true;
}

bool tscl_contract_check_post(ccontract *contract) {
    if (contract != NULL && contract->post_condition != NULL) {
        contract->post_condition();
    }
    return true;
}

bool tscl_contract_assert(bool condition, const char *message) {
    if (!condition) {
        fprintf(stderr, "[ERROR] Contract Violation: %s\n", message);
        return false;
    }
    return true;
}

bool tscl_contract_require_not_null(const void *ptr, const char *param_name) {
    return tscl_contract_assert(ptr != NULL, param_name);
}

bool tscl_contract_require_positive(int value, const char *param_name) {
    return tscl_contract_assert(value > 0, param_name);
}

bool tscl_contract_require_non_negative(int value, const char *param_name) {
    return tscl_contract_assert(value >= 0, param_name);
}

bool tscl_contract_require_within_range(int value, int min, int max, const char *param_name) {
    return tscl_contract_assert(value >= min && value <= max, param_name);
}

bool tscl_contract_require_within_double_range(double value, double min, double max, const char *param_name) {
    return tscl_contract_assert(value >= min && value <= max, param_name);
}

bool tscl_contract_require_string_length(const char *str, size_t min_length, size_t max_length, const char *param_name) {
    size_t length = (str != NULL) ? strlen(str) : 0;
    return tscl_contract_assert(length >= min_length && length <= max_length, param_name);
}

bool tscl_contract_require_pointer_equality(const void *ptr1, const void *ptr2, const char *param_name) {
    return tscl_contract_assert(ptr1 == ptr2, param_name);
}

bool tscl_contract_require_string_equality(const char *str1, const char *str2, const char *param_name) {
    return tscl_contract_assert(strcmp(str1, str2) == 0, param_name);
}

bool tscl_contract_require_array_length(const void *array, size_t expected_length, size_t element_size, const char *param_name) {
    size_t actual_length = (array != NULL) ? (strlen(array) / element_size) : 0;
    return tscl_contract_assert(actual_length == expected_length, param_name);
}

bool tscl_contract_require_custom_condition(bool (*custom_condition)(), const char *param_name) {
    return tscl_contract_assert(custom_condition(), param_name);
}
