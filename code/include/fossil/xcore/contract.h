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
#ifndef FSCL_CONTRACT_H
#define FSCL_CONTRACT_H

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
ccontract *fscl_contract_create(bool (*pre_condition)(), void (*post_condition)());

// =================================================================
// addintal functions
// =================================================================
bool fscl_contract_check_pre(ccontract *contract);
bool fscl_contract_check_post(ccontract *contract);
bool fscl_contract_assert(bool condition, const char *message);
bool fscl_contract_require_not_null(const void *ptr, const char *param_name);
bool fscl_contract_require_positive(int value, const char *param_name);
bool fscl_contract_require_non_negative(int value, const char *param_name);
bool fscl_contract_require_within_range(int value, int min, int max, const char *param_name);
bool fscl_contract_require_within_double_range(double value, double min, double max, const char *param_name);
bool fscl_contract_require_string_length(const char *str, size_t min_length, size_t max_length, const char *param_name);
bool fscl_contract_require_pointer_equality(const void *ptr1, const void *ptr2, const char *param_name);
bool fscl_contract_require_string_equality(const char *str1, const char *str2, const char *param_name);
bool fscl_contract_require_array_length(const void *array, size_t expected_length, size_t element_size, const char *param_name);
bool fscl_contract_require_custom_condition(bool (*custom_condition)(), const char *param_name);

#ifdef __cplusplus
}
#endif

#endif
