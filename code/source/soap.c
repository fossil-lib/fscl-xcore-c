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
#include "fossil/xcore/fossil.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

// List of offensive words and phrases (you can extend this list as needed)
static const char *offensive_words[] = {
    "curse1",
    "curse2",
    "racist_phrase1",
    "racist_phrase2",
    // Add more offensive words and phrases as needed
};

// Custom strdup utility function
static char *fscl_soap_strdup(const char *str) {
    size_t len = strlen(str) + 1;
    char *dup = (char *)malloc(len);
    if (dup != NULL) {
        memcpy(dup, str, len);
    }
    return dup;
}

// Function to replace a substring in a string (case-insensitive)
static void replace_substring_case_insensitive(char *str, const char *old_substr, const char *new_substr) {
    char *position = strcasestr(str, old_substr);
    if (position != NULL) {
        memmove(position + strlen(new_substr), position + strlen(old_substr), strlen(position + strlen(old_substr)) + 1);
        strncpy(position, new_substr, strlen(new_substr));
    }
}

// Function to sanitize a string by replacing offensive words and phrases with asterisks
void fscl_soap_sanitize(char *input) {
    for (size_t i = 0; i < sizeof(offensive_words) / sizeof(offensive_words[0]); ++i) {
        while (strcasestr(input, offensive_words[i]) != NULL) {
            replace_substring_case_insensitive(input, offensive_words[i], "***");
        }
    }
}

// Function to check if a word is an offensive word or phrase
bool fscl_soap_is_offensive(const char *word) {
    for (size_t i = 0; i < sizeof(offensive_words) / sizeof(offensive_words[0]); ++i) {
        if (strcasecmp(word, offensive_words[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Function to get the number of offensive words found in a string
int fscl_soap_count_offensive(const char *input) {
    int count = 0;
    char *copy = fscl_soap_strdup(input); // Use the custom strdup function
    char *token = strtok(copy, " "); // Tokenize the string by space
    while (token != NULL) {
        if (fscl_soap_is_offensive(token)) {
            count++;
        }
        token = strtok(NULL, " ");
    }
    free(copy); // Free the memory allocated for the copy
    return count;
}
