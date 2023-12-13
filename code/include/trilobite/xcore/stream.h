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
#ifndef TSCL_STREAM_H
#define TSCL_STREAM_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

enum {
    MAX_FILENAME_LENGTH = 256,
    MAX_BUFFER_SIZE     = 1024
};

typedef struct cstream {
    FILE *file;
    char filename[MAX_FILENAME_LENGTH];
} cstream; // end struct

/**
 * Opens a file with the specified filename and mode.
 *
 * @param stream A pointer to the cstream structure to be initialized.
 * @param filename The name of the file to be opened.
 * @param mode The file access mode (e.g., "r" for read, "w" for write).
 * @return 0 if the file is successfully opened, -1 on failure.
 */
int stream_open(cstream *stream, const char *filename, const char *mode);

/**
 * Closes the currently open file associated with the cstream structure.
 *
 * @param stream A pointer to the cstream structure to be closed.
 */
void stream_close(cstream *stream);

/**
 * Reads data from the currently open file into the provided buffer.
 *
 * @param stream A pointer to the cstream structure representing the open file.
 * @param buffer A pointer to the destination buffer where data will be read into.
 * @param size The size, in bytes, of each element to be read.
 * @param count The number of elements to read.
 * @return The total number of elements successfully read.
 */
size_t stream_read(cstream *stream, void *buffer, size_t size, size_t count);

/**
 * Writes data from the provided buffer to the currently open file.
 *
 * @param stream A pointer to the cstream structure representing the open file.
 * @param buffer A pointer to the source buffer containing the data to be written.
 * @param size The size, in bytes, of each element to be written.
 * @param count The number of elements to write.
 * @return The total number of elements successfully written.
 */
size_t stream_write(cstream *stream, const void *buffer, size_t size, size_t count);

/**
 * Appends data from the provided buffer to the end of the currently open file.
 *
 * @param stream A pointer to the cstream structure representing the open file.
 * @param buffer A pointer to the source buffer containing the data to be appended.
 * @param size The size, in bytes, of each element to be appended.
 * @param count The number of elements to append.
 * @return 0 if the data is successfully appended, -1 on failure.
 */
int stream_append(cstream *stream, const void *buffer, size_t size, size_t count);

/**
 * Moves the file pointer within the currently open file to a specified position.
 *
 * @param stream A pointer to the cstream structure representing the open file.
 * @param offset The offset in bytes from the origin.
 * @param origin The starting point for the offset (SEEK_SET, SEEK_CUR, or SEEK_END).
 * @return 0 if the seek operation is successful, -1 on failure.
 */
int stream_seek(cstream *stream, long offset, int origin);

/**
 * Saves the currently open file with a new filename.
 *
 * @param stream A pointer to the cstream structure representing the open file.
 * @param new_filename The new name under which the file will be saved.
 * @return 0 if the file is successfully saved with the new name, -1 on failure.
 */
int stream_save(cstream *stream, const char *new_filename);

/**
 * Copies a file from the source location to a destination location.
 *
 * @param source_filename The name of the source file to be copied.
 * @param destination_filename The name of the destination file where the source file will be copied.
 * @return 0 if the file is successfully copied, -1 on failure.
 */
int stream_copy(const char *source_filename, const char *destination_filename);

/**
 * Creates a backup of the specified file with the given backup suffix.
 *
 * @param filename The name of the file to create a backup of.
 * @param backup_suffix The suffix to be added to the filename to create the backup filename.
 * @return 0 if the backup is successfully created, -1 on failure.
 */
int stream_backup(const char *filename, const char *backup_suffix);

/**
 * Checks if a file exists.
 *
 * @param filename The name of the file to check.
 * @return 1 if the file exists, 0 otherwise.
 */
int stream_file_exists(const char *filename);

/**
 * Gets the size of the currently open file.
 *
 * @param stream A pointer to the cstream structure representing the open file.
 * @return The size of the file in bytes, or -1 on failure.
 */
long stream_get_size(cstream *stream);

/**
 * Deletes a file.
 *
 * @param filename The name of the file to delete.
 * @return 0 if the file is successfully deleted, -1 on failure.
 */
int stream_delete(const char *filename);

#ifdef __cplusplus
}
#endif

#endif
