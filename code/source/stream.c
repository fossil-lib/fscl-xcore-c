/*  ----------------------------------------------------------------------------
    File: stream.c

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
#include "trilobite/xcore/stream.h"
#include <string.h>

// Function to open a file
int stream_open(cstream *stream, const char *filename, const char *mode) {
    if (strlen(filename) >= MAX_FILENAME_LENGTH) {
        fprintf(stderr, "Filename too long.\n");
        return -1;
    }

    stream->file = fopen(filename, mode);
    if (stream->file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return -1;
    }

    strcpy(stream->filename, filename);
    return 0;
} // end of func

// Function to close a file
void stream_close(cstream *stream) {
    if (stream->file != NULL) {
        fclose(stream->file);
        stream->file = NULL;
    }
} // end of func

// Function to read from a file
size_t stream_read(cstream *stream, void *buffer, size_t size, size_t count) {
    if (stream->file == NULL) {
        fprintf(stderr, "File not open.\n");
        return 0;
    }
    return fread(buffer, size, count, stream->file);
} // end of func

// Function to write to a file
size_t stream_write(cstream *stream, const void *buffer, size_t size, size_t count) {
    if (stream->file == NULL) {
        fprintf(stderr, "File not open.\n");
        return 0;
    }

    return fwrite(buffer, size, count, stream->file);
} // end of func

// Function to append to a file
int stream_append(cstream *stream, const void *buffer, size_t size, size_t count) {
    if (stream->file == NULL) {
        fprintf(stderr, "File not open.\n");
        return -1;
    }

    fseek(stream->file, 0, SEEK_END);
    return fwrite(buffer, size, count, stream->file);
} // end of func

// Function to seek within a file
int stream_seek(cstream *stream, long offset, int origin) {
    if (stream->file == NULL) {
        fprintf(stderr, "File not open.\n");
        return -1;
    }

    return fseek(stream->file, offset, origin);
} // end of func

// Function to save the file with a new name
int stream_save(cstream *stream, const char *new_filename) {
    if (strlen(new_filename) >= MAX_FILENAME_LENGTH) {
        fprintf(stderr, "New filename too long.\n");
        return -1;
    }

    if (stream->file == NULL) {
        fprintf(stderr, "File not open.\n");
        return -1;
    }

    fclose(stream->file);

    if (rename(stream->filename, new_filename) != 0) {
        fprintf(stderr, "Failed to save file as %s.\n", new_filename);
        return -1;
    }

    return stream_open(stream, new_filename, "r");
} // end of func

// Function to copy a file to a new location
int stream_copy(const char *source_filename, const char *destination_filename) {
    FILE *source_file = fopen(source_filename, "rb");
    if (source_file == NULL) {
        fprintf(stderr, "Failed to open source file: %s\n", source_filename);
        return -1;
    }

    FILE *destination_file = fopen(destination_filename, "wb");
    if (destination_file == NULL) {
        fprintf(stderr, "Failed to open destination file: %s\n", destination_filename);
        fclose(source_file);
        return -1;
    }

    char buffer[MAX_BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, MAX_BUFFER_SIZE, source_file)) > 0) {
        size_t bytesWritten = fwrite(buffer, 1, bytesRead, destination_file);
        if (bytesWritten != bytesRead) {
            fprintf(stderr, "Failed to write to destination file.\n");
            fclose(source_file);
            fclose(destination_file);
            return -1;
        }
    }

    fclose(source_file);
    fclose(destination_file);

    return 0;
} // end of func

// Function to create a backup of a file
int stream_backup(const char *filename, const char *backup_suffix) {
    char backup_filename[MAX_FILENAME_LENGTH + 10];  // Length of backup_suffix + maximum integer length
    snprintf(backup_filename, MAX_FILENAME_LENGTH + 10, "%s%s", filename, backup_suffix);

    if (stream_copy(filename, backup_filename) != 0) {
        fprintf(stderr, "Failed to create backup for %s.\n", filename);
        return -1;
    }

    return 0;
} // end of func

int stream_file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;  // File exists
    }
    return 0;  // File does not exist
} // end of func

long stream_get_size(cstream *stream) {
    if (stream && stream->file) {
        fseek(stream->file, 0, SEEK_END);
        long size = ftell(stream->file);
        rewind(stream->file);
        return size;
    }
    return -1;  // Error
} // end of func

int stream_delete(const char *filename) {
    if (remove(filename) == 0) {
        return 0;  // File deleted successfully
    }
    return -1;  // Error
} // end of func
