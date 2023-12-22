/*
   under:   trilobite stdlib
   author:  Michael Gene Brockus (Dreamer)
   gmail:   <michaelbrockus@gmail.com>
   website: <https://trilobite.home.blog>
*/
#include "trilobite/xcore/stream.h" // lib source code

#include <trilobite/xtest.h>   // basic test tools
#include <trilobite/xassert.h> // extra asserts
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
    
    TEST_ASSERT_EQUAL_INT(0, tscl_stream_open(&io.stream, "testfile.txt", "w"));
    TEST_ASSERT_NOT_NULL_PTR(io.stream.file);
    tscl_stream_close(&io.stream);
    TEST_ASSERT_NULL_PTR(io.stream.file);
}

XTEST_CASE(stream_let_write_and_read_file) {
    const char *filename = "testfile.txt";
    const char *content = "This is a test.";

    // Write data to the file
    TEST_ASSERT_EQUAL_INT(0, tscl_stream_open(&io.stream, filename, "w"));
    size_t bytes_written = tscl_stream_write(&io.stream, content, strlen(content), 1);
    tscl_stream_close(&io.stream);
    TEST_ASSERT_EQUAL_INT(strlen(content), bytes_written);

    // Read data from the file
    char buffer[1024];
    TEST_ASSERT_EQUAL_INT(0, tscl_stream_open(&io.stream, filename, "r"));
    size_t bytes_read = tscl_stream_read(&io.stream, buffer, sizeof(buffer), 1);
    tscl_stream_close(&io.stream);
    TEST_ASSERT_EQUAL_INT(strlen(content), bytes_read);
    TEST_ASSERT_EQUAL_STRING(content, buffer);
}

// Test case for appending to a file
XTEST_CASE(stream_let_append_file) {
    const char *filename = "testfile.txt";
    char *content1 = "This is content1.";
    char *content2 = "This is content2.";

    // Append data to the file
    TEST_ASSERT_EQUAL_INT(0, tscl_stream_open(&io.stream, filename, "w"));
    size_t bytes_written1 = tscl_stream_write(&io.stream, content1, strlen(content1), 1);
    tscl_stream_close(&io.stream);
    TEST_ASSERT_EQUAL_INT(strlen(content1), bytes_written1);

    TEST_ASSERT_EQUAL_INT(0, tscl_stream_open(&io.stream, filename, "a"));
    size_t bytes_written2 = tscl_stream_write(&io.stream, content2, strlen(content2), 1);
    tscl_stream_close(&io.stream);
    TEST_ASSERT_EQUAL_INT(strlen(content2), bytes_written2);

    // Read data from the file and verify content
    char buffer[1024];
    TEST_ASSERT_EQUAL_INT(0, tscl_stream_open(&io.stream, filename, "r"));
    size_t bytes_read = tscl_stream_read(&io.stream, buffer, sizeof(buffer), 1);
    tscl_stream_close(&io.stream);
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
    TEST_ASSERT_EQUAL_INT(0, tscl_stream_open(&io.stream, filename, "w"));
    size_t bytes_written = tscl_stream_write(&io.stream, content, strlen(content), 1);
    tscl_stream_close(&io.stream);
    TEST_ASSERT_EQUAL_INT(strlen(content), bytes_written);

    // Save the file with a new name
    TEST_ASSERT_EQUAL_INT(0, tscl_stream_save(&io.stream, new_filename));

    // Read data from the new file and verify content
    char buffer[1024];
    TEST_ASSERT_EQUAL_INT(0, tscl_stream_open(&io.stream, new_filename, "r"));
    size_t bytes_read = tscl_stream_read(&io.stream, buffer, sizeof(buffer), 1);
    tscl_stream_close(&io.stream);
    TEST_ASSERT_EQUAL_INT(strlen(content), bytes_read);
    TEST_ASSERT_EQUAL_STRING(content, buffer);
}

//
// XUNIT-TEST RUNNER
//
XTEST_GROUP_DEFINE(test_stream_group) {
    XTEST_RUN_UNIT(stream_let_open_and_close_file,  runner);
    XTEST_RUN_UNIT(stream_let_append_file,          runner);
    XTEST_RUN_UNIT(stream_let_write_and_read_file,  runner);
    XTEST_RUN_UNIT(stream_let_save_and_reopen_file, runner);
} // end of function main
