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
// Open and Close
// =================================================================

/**
 * Open a stream for file operations.
 *
 * @param stream   Pointer to the cstream structure to store the opened stream.
 * @param filename The name of the file to be opened.
 * @param mode     The mode in which to open the file (e.g., "r" for read, "w" for write).
 * @return         0 on success, non-zero on failure.
 */
int fscl_stream_open(cstream *stream, const char *filename, const char *mode);

/**
 * Close an open stream.
 *
 * @param stream Pointer to the cstream structure to be closed.
 */
void fscl_stream_close(cstream *stream);

// =================================================================
// Available Functions
// =================================================================

/**
 * Read data from an open stream.
 *
 * @param stream Pointer to the cstream structure from which to read.
 * @param buffer Pointer to the buffer to store the read data.
 * @param size   Size of each element to be read.
 * @param count  Number of elements to read.
 * @return       The total number of elements successfully read.
 */
size_t fscl_stream_read(cstream *stream, void *buffer, size_t size, size_t count);

/**
 * Write data to an open stream.
 *
 * @param stream Pointer to the cstream structure to which to write.
 * @param buffer Pointer to the buffer containing the data to be written.
 * @param size   Size of each element to be written.
 * @param count  Number of elements to write.
 * @return       The total number of elements successfully written.
 */
size_t fscl_stream_write(cstream *stream, const void *buffer, size_t size, size_t count);

/**
 * Append data to the end of an open stream.
 *
 * @param stream Pointer to the cstream structure to which to append.
 * @param buffer Pointer to the buffer containing the data to be appended.
 * @param size   Size of each element to be appended.
 * @param count  Number of elements to append.
 * @return       0 on success, non-zero on failure.
 */
int fscl_stream_append(cstream *stream, const void *buffer, size_t size, size_t count);

/**
 * Seek to a specified position in an open stream.
 *
 * @param stream Pointer to the cstream structure to seek.
 * @param offset The offset from the specified origin.
 * @param origin The starting position for the offset (SEEK_SET, SEEK_CUR, SEEK_END).
 * @return       0 on success, non-zero on failure.
 */
int fscl_stream_seek(cstream *stream, long offset, int origin);

/**
 * Save an open stream to a new file.
 *
 * @param stream       Pointer to the cstream structure to be saved.
 * @param new_filename The name of the new file to save to.
 * @return             0 on success, non-zero on failure.
 */
int fscl_stream_save(cstream *stream, const char *new_filename);

/**
 * Copy a file from the source to the destination.
 *
 * @param source_filename      The name of the source file.
 * @param destination_filename The name of the destination file.
 * @return                     0 on success, non-zero on failure.
 */
int fscl_stream_copy(const char *source_filename, const char *destination_filename);

/**
 * Create a backup of a file with a specified backup suffix.
 *
 * @param filename      The name of the file to create a backup for.
 * @param backup_suffix The suffix to be appended to the backup file.
 * @return              0 on success, non-zero on failure.
 */
int fscl_stream_backup(const char *filename, const char *backup_suffix);

/**
 * Check if a file exists.
 *
 * @param filename The name of the file to check for existence.
 * @return         1 if the file exists, 0 if not.
 */
int fscl_stream_file_exists(const char *filename);

/**
 * Get the size of an open stream.
 *
 * @param stream Pointer to the cstream structure to get the size of.
 * @return       The size of the open stream.
 */
long fscl_stream_get_size(cstream *stream);

/**
 * Delete a file.
 *
 * @param filename The name of the file to be deleted.
 * @return         0 on success, non-zero on failure.
 */
int fscl_stream_delete(const char *filename);

// =================================================================
// ChaCha20 Functions
// =================================================================

/**
 * Create a ChaCha20 stream cipher lock.
 *
 * @param key   The key for the ChaCha20 cipher (32 bytes).
 * @param nonce The nonce for the ChaCha20 cipher (8 bytes).
 * @return      A pointer to the created stream_lock structure.
 */
stream_lock* fscl_stream_lock_create(const uint8_t *key, const uint8_t *nonce);

/**
 * Erase a ChaCha20 stream cipher lock and free associated memory.
 *
 * @param lock Pointer to the stream_lock structure to be erased.
 */
void fscl_stream_lock_erase(stream_lock *lock);

/**
 * Generate a random key for the ChaCha20 cipher.
 *
 * @param key Pointer to the buffer to store the generated key (32 bytes).
 */
void fscl_stream_lock_generate_key(uint8_t *key);

/**
 * Encrypt data using the ChaCha20 stream cipher.
 *
 * @param lock   Pointer to the stream_lock structure containing the cipher context.
 * @param input  Pointer to the input data to be encrypted.
 * @param output Pointer to the buffer to store the encrypted data.
 * @param length The length of the input data.
 */
void fscl_stream_encrypt(stream_lock *lock, const uint8_t *input, uint8_t *output, size_t length);

/**
 * Decrypt data using the ChaCha20 stream cipher.
 *
 * @param lock   Pointer to the stream_lock structure containing the cipher context.
 * @param input  Pointer to the input data to be decrypted.
 * @param output Pointer to the buffer to store the decrypted data.
 * @param length The length of the input data.
 */
void fscl_stream_decrypt(stream_lock *lock, const uint8_t *input, uint8_t *output, size_t length);

#ifdef __cplusplus
}
#endif

#endif
