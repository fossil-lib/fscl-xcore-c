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
#include "fossil/xcore/stream.h" // lib source code

#include <fossil/xtest.h>   // basic test tools
#include <fossil/xassert.h> // extra asserts
#include <string.h>

//
// XUNIT TEST DATA
//
XTEST_DATA(StreamTestData) {
    cstream stream;
} io;

//
// XUNIT TEST CASES
//
XTEST_CASE(stream_let_open_and_close_file) {
    
    TEST_ASSERT_EQUAL_INT(0, fscl_stream_open(&io.stream, "testfile.txt", "w"));
    TEST_ASSERT_NOT_CNULLPTR(io.stream.file);
    fscl_stream_close(&io.stream);
    TEST_ASSERT_CNULLPTR(io.stream.file);
}

XTEST_CASE(stream_let_write_and_read_file) {
    const char *filename = "testfile.txt";
    const char *content = "This is a test.";

    // Write data to the file
    TEST_ASSERT_EQUAL_INT(0, fscl_stream_open(&io.stream, filename, "w"));
    size_t bytes_written = fscl_stream_write(&io.stream, content, strlen(content), 1);
    fscl_stream_close(&io.stream);
    TEST_ASSERT_EQUAL_INT(strlen(content), bytes_written);

    // Read data from the file
    char buffer[1024];
    TEST_ASSERT_EQUAL_INT(0, fscl_stream_open(&io.stream, filename, "r"));
    size_t bytes_read = fscl_stream_read(&io.stream, buffer, sizeof(buffer), 1);
    fscl_stream_close(&io.stream);
    TEST_ASSERT_EQUAL_INT(strlen(content), bytes_read);
    TEST_ASSERT_EQUAL_STRING(content, buffer);
}

// Test case for appending to a file
XTEST_CASE(stream_let_append_file) {
    const char *filename = "testfile.txt";
    char *content1 = "This is content1.";
    char *content2 = "This is content2.";

    // Append data to the file
    TEST_ASSERT_EQUAL_INT(0, fscl_stream_open(&io.stream, filename, "w"));
    size_t bytes_written1 = fscl_stream_write(&io.stream, content1, strlen(content1), 1);
    fscl_stream_close(&io.stream);
    TEST_ASSERT_EQUAL_INT(strlen(content1), bytes_written1);

    TEST_ASSERT_EQUAL_INT(0, fscl_stream_open(&io.stream, filename, "a"));
    size_t bytes_written2 = fscl_stream_write(&io.stream, content2, strlen(content2), 1);
    fscl_stream_close(&io.stream);
    TEST_ASSERT_EQUAL_INT(strlen(content2), bytes_written2);

    // Read data from the file and verify content
    char buffer[1024];
    TEST_ASSERT_EQUAL_INT(0, fscl_stream_open(&io.stream, filename, "r"));
    size_t bytes_read = fscl_stream_read(&io.stream, buffer, sizeof(buffer), 1);
    fscl_stream_close(&io.stream);
    TEST_ASSERT_EQUAL_INT(strlen(content1) + strlen(content2), bytes_read);

    // Combine both contents and verify
    strcat(content1, content2);
    TEST_ASSERT_EQUAL_STRING(content1, buffer);
}

// Test case for saving and reopening a file
XTEST_CASE(stream_let_save_and_reopen_file) {
    const char *filename = "testfile.txt";
    const char *new_filename = "newfile.txt";
    const char *content = "This is a test.";

    // Write data to the file
    TEST_ASSERT_EQUAL_INT(0, fscl_stream_open(&io.stream, filename, "w"));
    size_t bytes_written = fscl_stream_write(&io.stream, content, strlen(content), 1);
    fscl_stream_close(&io.stream);
    TEST_ASSERT_EQUAL_INT(strlen(content), bytes_written);

    // Save the file with a new name
    TEST_ASSERT_EQUAL_INT(0, fscl_stream_save(&io.stream, new_filename));

    // Read data from the new file and verify content
    char buffer[1024];
    TEST_ASSERT_EQUAL_INT(0, fscl_stream_open(&io.stream, new_filename, "r"));
    size_t bytes_read = fscl_stream_read(&io.stream, buffer, sizeof(buffer), 1);
    fscl_stream_close(&io.stream);
    TEST_ASSERT_EQUAL_INT(strlen(content), bytes_read);
    TEST_ASSERT_EQUAL_STRING(content, buffer);
}

//
// XUNIT-TEST RUNNER
//
XTEST_DEFINE_POOL(test_stream_group) {
    XTEST_RUN_UNIT(stream_let_open_and_close_file);
    XTEST_RUN_UNIT(stream_let_append_file);
    XTEST_RUN_UNIT(stream_let_write_and_read_file);
    XTEST_RUN_UNIT(stream_let_save_and_reopen_file);
} // end of function main
