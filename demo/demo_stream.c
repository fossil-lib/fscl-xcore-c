/*  ----------------------------------------------------------------------------
    File: demo_stream.c

    Description:
    This demo file serves as a showcase of the Trilobite Stdlib in action. It provides
    example code snippets and usage scenarios to help users understand how to leverage
    the library's features and functions in their own projects.

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
#include <trilobite/xcore/stream.h>
#include <trilobite/xcore/console.h>
#include <stdio.h>
#include <string.h>

// Function to print the hexadecimal representation of data
void print_hex(const char *label, const uint8_t *data, size_t length) {
    tscl_console_out("%s: ", label);
    for (size_t i = 0; i < length; ++i) {
        tscl_console_out("%02X", data[i]);
    }
    tscl_console_out("\n");
}

// Robot log structure
typedef struct {
    char timestamp[20];
    char message[256];
} RobotLog;

int main() {
    // Example usage of robot log with file management and ChaCha20 encryption and decryption

    // File paths
    const char *logFilename = "robot_log.bin";
    const char *encryptedLogFilename = "encrypted_robot_log.bin";
    const char *decryptedLogFilename = "decrypted_robot_log.txt";

    const uint8_t nonce[8] = {0};

    // Create a random key for the stream lock
    uint8_t key[32];
    tscl_stream_lock_generate_key(key);

    // Create a stream lock with the random key
    stream_lock *lock = tscl_stream_lock_create(key, nonce);

    // Create a stream lock
    stream_lock *lock = tscl_stream_lock_create(key, nonce);
    if (lock == NULL) {
        tscl_console_err("Failed to create stream lock.\n");
        return 1;
    }

    // Open the robot log file
    cstream logFile;
    if (tscl_stream_open(&logFile, logFilename, "rb") != 0) {
        tscl_console_err("Failed to open robot log file.\n");
        tscl_stream_lock_erase(lock);
        return 1;
    }

    // Get the size of the robot log file
    long logFileSize = tscl_stream_get_size(&logFile);
    if (logFileSize <= 0) {
        tscl_console_err("Invalid robot log file size.\n");
        tscl_stream_close(&logFile);
        tscl_stream_lock_erase(lock);
        return 1;
    }

    // Allocate memory for robot log data
    RobotLog *robotLogData = (RobotLog *)malloc(logFileSize);
    if (robotLogData == NULL) {
        tscl_console_err("Failed to allocate memory.\n");
        tscl_stream_close(&logFile);
        tscl_stream_lock_erase(lock);
        return 1;
    }

    // Read data from the robot log file
    if (tscl_stream_read(&logFile, robotLogData, sizeof(RobotLog), logFileSize / sizeof(RobotLog)) != logFileSize / sizeof(RobotLog)) {
        tscl_console_err("Failed to read robot log file.\n");
        free(robotLogData);
        tscl_stream_close(&logFile);
        tscl_stream_lock_erase(lock);
        return 1;
    }

    // Close the robot log file
    tscl_stream_close(&logFile);

    // Encrypt the robot log data
    RobotLog *encryptedRobotLogData = (RobotLog *)malloc(logFileSize);
    if (encryptedRobotLogData == NULL) {
        tscl_console_err("Failed to allocate memory.\n");
        free(robotLogData);
        tscl_stream_lock_erase(lock);
        return 1;
    }
    tscl_stream_encrypt(lock, (const uint8_t *)robotLogData, (uint8_t *)encryptedRobotLogData, logFileSize);

    // Write encrypted robot log data to a file
    cstream encryptedLogFile;
    if (tscl_stream_open(&encryptedLogFile, encryptedLogFilename, "wb") != 0) {
        tscl_console_err("Failed to open encrypted robot log file.\n");
        free(robotLogData);
        free(encryptedRobotLogData);
        tscl_stream_lock_erase(lock);
        return 1;
    }

    if (tscl_stream_write(&encryptedLogFile, encryptedRobotLogData, sizeof(RobotLog), logFileSize / sizeof(RobotLog)) != logFileSize / sizeof(RobotLog)) {
        tscl_console_err("Failed to write encrypted robot log file.\n");
        free(robotLogData);
        free(encryptedRobotLogData);
        tscl_stream_close(&encryptedLogFile);
        tscl_stream_lock_erase(lock);
        return 1;
    }

    tscl_stream_close(&encryptedLogFile);

    // Decrypt the robot log data
    RobotLog *decryptedRobotLogData = (RobotLog *)malloc(logFileSize);
    if (decryptedRobotLogData == NULL) {
        tscl_console_err("Failed to allocate memory.\n");
        free(robotLogData);
        free(encryptedRobotLogData);
        tscl_stream_lock_erase(lock);
        return 1;
    }
    tscl_stream_decrypt(lock, (const uint8_t *)encryptedRobotLogData, (uint8_t *)decryptedRobotLogData, logFileSize);

    // Write decrypted robot log data to a file
    cstream decryptedLogFile;
    if (tscl_stream_open(&decryptedLogFile, decryptedLogFilename, "w") != 0) {
        tscl_console_err("Failed to open decrypted robot log file.\n");
        free(robotLogData);
        free(encryptedRobotLogData);
        free(decryptedRobotLogData);
        tscl_stream_lock_erase(lock);
        return 1;
    }

    // Print decrypted robot log data to console
    tscl_console_out("Decrypted Robot Log:\n");
    for (size_t i = 0; i < logFileSize / sizeof(RobotLog); ++i) {
        tscl_console_out("[%s] %s\n", decryptedRobotLogData[i].timestamp, decryptedRobotLogData[i].message);
        // You can also write to the decryptedLogFile if needed
        tscl_stream_write(&decryptedLogFile, &decryptedRobotLogData[i], sizeof(RobotLog), 1);
    }

    tscl_stream_close(&decryptedLogFile);

    // Clean up memory
    free(robotLogData);
    free(encryptedRobotLogData);
    free(decryptedRobotLogData);

    // Destroy the stream lock
    tscl_stream_lock_erase(lock);

    return 0;
} // end of func
