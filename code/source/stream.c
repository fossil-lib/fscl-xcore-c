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
#include "fossil/xcore/stream.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define CHACHA20_BLOCK_SIZE 64

#define ROTL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define QR(a, b, c, d) \
    a += b; \
    d ^= a; \
    d = ROTL(d, 16); \
    c += d; \
    b ^= c; \
    b = ROTL(b, 12); \
    a += b; \
    d ^= a; \
    d = ROTL(d, 8); \
    c += d; \
    b ^= c; \
    b = ROTL(b, 7);

// Function to open a file
int fscl_stream_open(cstream *stream, const char *filename, const char *mode) {
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
void fscl_stream_close(cstream *stream) {
    if (stream->file != NULL) {
        fclose(stream->file);
        stream->file = NULL;
    }
} // end of func

// Function to read from a file
size_t fscl_stream_read(cstream *stream, void *buffer, size_t size, size_t count) {
    if (stream->file == NULL) {
        fprintf(stderr, "File not open.\n");
        return 0;
    }
    return fread(buffer, size, count, stream->file);
} // end of func

// Function to write to a file
size_t fscl_stream_write(cstream *stream, const void *buffer, size_t size, size_t count) {
    if (stream->file == NULL) {
        fprintf(stderr, "File not open.\n");
        return 0;
    }

    return fwrite(buffer, size, count, stream->file);
} // end of func

// Function to append to a file
int fscl_stream_append(cstream *stream, const void *buffer, size_t size, size_t count) {
    if (stream->file == NULL) {
        fprintf(stderr, "File not open.\n");
        return -1;
    }

    fseek(stream->file, 0, SEEK_END);
    return fwrite(buffer, size, count, stream->file);
} // end of func

// Function to seek within a file
int fscl_stream_seek(cstream *stream, long offset, int origin) {
    if (stream->file == NULL) {
        fprintf(stderr, "File not open.\n");
        return -1;
    }

    return fseek(stream->file, offset, origin);
} // end of func

// Function to save the file with a new name
int fscl_stream_save(cstream *stream, const char *new_filename) {
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

    return fscl_stream_open(stream, new_filename, "r");
} // end of func

// Function to copy a file to a new location
int fscl_stream_copy(const char *source_filename, const char *destination_filename) {
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
int fscl_stream_backup(const char *filename, const char *backup_suffix) {
    char backup_filename[MAX_FILENAME_LENGTH + 10];  // Length of backup_suffix + maximum integer length
    snprintf(backup_filename, MAX_FILENAME_LENGTH + 10, "%s%s", filename, backup_suffix);

    if (fscl_stream_copy(filename, backup_filename) != 0) {
        fprintf(stderr, "Failed to create backup for %s.\n", filename);
        return -1;
    }

    return 0;
} // end of func

int fscl_stream_file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;  // File exists
    }
    return 0;  // File does not exist
} // end of func

long fscl_stream_get_size(cstream *stream) {
    if (stream && stream->file) {
        fseek(stream->file, 0, SEEK_END);
        long size = ftell(stream->file);
        rewind(stream->file);
        return size;
    }
    return -1;  // Error
} // end of func

int fscl_stream_delete(const char *filename) {
    if (remove(filename) == 0) {
        return 0;  // File deleted successfully
    }
    return -1;  // Error
} // end of func

void chacha20_block(struct stream_lock *lock, uint8_t *output) {
    int i;
    uint32_t x[16];

    for (i = 0; i < 16; ++i) {
        x[i] = lock->state[i];
    }

    for (i = 0; i < 10; ++i) {
        QR(x[0], x[4], x[8], x[12]);
        QR(x[1], x[5], x[9], x[13]);
        QR(x[2], x[6], x[10], x[14]);
        QR(x[3], x[7], x[11], x[15]);
        QR(x[0], x[5], x[10], x[15]);
        QR(x[1], x[6], x[11], x[12]);
        QR(x[2], x[7], x[8], x[13]);
        QR(x[3], x[4], x[9], x[14]);
    }

    for (i = 0; i < 16; ++i) {
        x[i] += lock->state[i];
    }

    for (i = 0; i < 16; ++i) {
        output[i * 4 + 0] = x[i] & 0xFF;
        output[i * 4 + 1] = (x[i] >> 8) & 0xFF;
        output[i * 4 + 2] = (x[i] >> 16) & 0xFF;
        output[i * 4 + 3] = (x[i] >> 24) & 0xFF;
    }

    lock->state[12]++;
    if (lock->state[12] == 0) {
        lock->state[13]++;
    }
}

void chacha20_init(struct stream_lock *lock, const uint8_t *key, const uint8_t *nonce) {
    lock->state[0] = 0x61707865;
    lock->state[1] = 0x3320646e;
    lock->state[2] = 0x79622d32;
    lock->state[3] = 0x6b206574;

    for (int i = 0; i < 8; ++i) {
        lock->state[4 + i] = ((uint32_t *)key)[i];
    }

    lock->state[12] = 0;
    lock->state[13] = 0;
    lock->state[14] = ((uint32_t *)nonce)[0];
    lock->state[15] = ((uint32_t *)nonce)[1];
}

stream_lock* fscl_stream_lock_create(const uint8_t *key, const uint8_t *nonce) {
    stream_lock *lock = (stream_lock *)malloc(sizeof(stream_lock));
    if (lock == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    chacha20_init(lock, key, nonce);

    return lock;
}

void fscl_stream_lock_erase(stream_lock *lock) {
    free(lock);
}

void fscl_stream_encrypt(stream_lock *lock, const uint8_t *input, uint8_t *output, size_t length) {
    size_t blocks = length / CHACHA20_BLOCK_SIZE;

    for (size_t i = 0; i < blocks; ++i) {
        chacha20_block(lock, output + i * CHACHA20_BLOCK_SIZE);
        for (size_t j = 0; j < CHACHA20_BLOCK_SIZE; ++j) {
            output[i * CHACHA20_BLOCK_SIZE + j] ^= input[i * CHACHA20_BLOCK_SIZE + j];
        }
    }

    size_t remaining = length % CHACHA20_BLOCK_SIZE;
    if (remaining > 0) {
        uint8_t block[CHACHA20_BLOCK_SIZE];
        chacha20_block(lock, block);
        for (size_t i = 0; i < remaining; ++i) {
            output[blocks * CHACHA20_BLOCK_SIZE + i] ^= input[blocks * CHACHA20_BLOCK_SIZE + i] ^ block[i];
        }
    }
}

void fscl_stream_decrypt(stream_lock *lock, const uint8_t *input, uint8_t *output, size_t length) {
    // For ChaCha20, decryption is the same as encryption
    fscl_stream_encrypt(lock, input, output, length);
}

// Function to generate a random key for a stream lock
void fscl_stream_lock_generate_key(uint8_t *key) {
    // Seed the random number generator with the current time
    srand((unsigned int)time(NULL));

    // Generate a random key
    for (size_t i = 0; i < 32; ++i) {
        key[i] = rand() % 256;
    }
}
