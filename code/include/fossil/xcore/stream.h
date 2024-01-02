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
#ifndef FSCL_STREAM_H
#define FSCL_STREAM_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

enum {
    MAX_FILENAME_LENGTH = 256,
    MAX_BUFFER_SIZE     = 1024
};

typedef struct stream_lock {
    uint32_t state[16];
} stream_lock;

typedef struct cstream {
    FILE *file;
    char filename[MAX_FILENAME_LENGTH];
} cstream; // end struct

// =================================================================
// open and close
// =================================================================
int fscl_stream_open(cstream *stream, const char *filename, const char *mode);
void fscl_stream_close(cstream *stream);

// =================================================================
// avaliable functions
// =================================================================
size_t fscl_stream_read(cstream *stream, void *buffer, size_t size, size_t count);
size_t fscl_stream_write(cstream *stream, const void *buffer, size_t size, size_t count);
int fscl_stream_append(cstream *stream, const void *buffer, size_t size, size_t count);
int fscl_stream_seek(cstream *stream, long offset, int origin);
int fscl_stream_save(cstream *stream, const char *new_filename);
int fscl_stream_copy(const char *source_filename, const char *destination_filename);
int fscl_stream_backup(const char *filename, const char *backup_suffix);
int fscl_stream_file_exists(const char *filename);
long fscl_stream_get_size(cstream *stream);
int fscl_stream_delete(const char *filename);

// =================================================================
// chacha20 functions
// =================================================================
stream_lock* fscl_stream_lock_create(const uint8_t *key, const uint8_t *nonce);
void fscl_stream_lock_erase(stream_lock *lock);
void fscl_stream_lock_generate_key(uint8_t *key);
void fscl_stream_encrypt(stream_lock *lock, const uint8_t *input, uint8_t *output, size_t length);
void fscl_stream_decrypt(stream_lock *lock, const uint8_t *input, uint8_t *output, size_t length);


#ifdef __cplusplus
}
#endif

#endif
