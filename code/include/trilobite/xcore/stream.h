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

// =================================================================
// open and close
// =================================================================
int tscl_stream_open(cstream *stream, const char *filename, const char *mode);
void tscl_stream_close(cstream *stream);

// =================================================================
// avaliable functions
// =================================================================
size_t tscl_stream_read(cstream *stream, void *buffer, size_t size, size_t count);
size_t tscl_stream_write(cstream *stream, const void *buffer, size_t size, size_t count);
int tscl_stream_append(cstream *stream, const void *buffer, size_t size, size_t count);
int tscl_stream_seek(cstream *stream, long offset, int origin);
int tscl_stream_save(cstream *stream, const char *new_filename);
int tscl_stream_copy(const char *source_filename, const char *destination_filename);
int tscl_stream_backup(const char *filename, const char *backup_suffix);
int tscl_stream_file_exists(const char *filename);
long tscl_stream_get_size(cstream *stream);
int tscl_stream_delete(const char *filename);

#ifdef __cplusplus
}
#endif

#endif
