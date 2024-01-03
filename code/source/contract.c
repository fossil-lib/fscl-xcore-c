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
#include "fossil/xcore/contract.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ccontract *fscl_contract_create(bool (*pre_condition)(), void (*post_condition)()) {
    ccontract *contract = (ccontract *)malloc(sizeof(ccontract));
    if (contract != NULL) {
        contract->pre_condition = pre_condition;
        contract->post_condition = post_condition;
    }
    return contract;
}

bool fscl_contract_check_pre(ccontract *contract) {
    if (contract != NULL && contract->pre_condition != NULL) {
        return contract->pre_condition();
    }
    return true;
}

bool fscl_contract_check_post(ccontract *contract) {
    if (contract != NULL && contract->post_condition != NULL) {
        contract->post_condition();
    }
    return true;
}

bool fscl_contract_assert(bool condition, const char *message) {
    if (!condition) {
        fprintf(stderr, "[ERROR] Contract Violation: %s\n", message);
        return false;
    }
    return true;
}

bool fscl_contract_require_not_null(const void *ptr, const char *param_name) {
    return fscl_contract_assert(ptr != NULL, param_name);
}

bool fscl_contract_require_positive(int value, const char *param_name) {
    return fscl_contract_assert(value > 0, param_name);
}

bool fscl_contract_require_non_negative(int value, const char *param_name) {
    return fscl_contract_assert(value >= 0, param_name);
}

bool fscl_contract_require_within_range(int value, int min, int max, const char *param_name) {
    return fscl_contract_assert(value >= min && value <= max, param_name);
}

bool fscl_contract_require_within_double_range(double value, double min, double max, const char *param_name) {
    return fscl_contract_assert(value >= min && value <= max, param_name);
}

bool fscl_contract_require_string_length(const char *str, size_t min_length, size_t max_length, const char *param_name) {
    size_t length = (str != NULL) ? strlen(str) : 0;
    return fscl_contract_assert(length >= min_length && length <= max_length, param_name);
}

bool fscl_contract_require_pointer_equality(const void *ptr1, const void *ptr2, const char *param_name) {
    return fscl_contract_assert(ptr1 == ptr2, param_name);
}

bool fscl_contract_require_string_equality(const char *str1, const char *str2, const char *param_name) {
    return fscl_contract_assert(strcmp(str1, str2) == 0, param_name);
}

bool fscl_contract_require_array_length(const void *array, size_t expected_length, size_t element_size, const char *param_name) {
    size_t actual_length = (array != NULL) ? (strlen(array) / element_size) : 0;
    return fscl_contract_assert(actual_length == expected_length, param_name);
}

bool fscl_contract_require_custom_condition(bool (*custom_condition)(), const char *param_name) {
    return fscl_contract_assert(custom_condition(), param_name);
}
