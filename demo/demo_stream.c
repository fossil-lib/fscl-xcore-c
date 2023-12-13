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
#include "trilobite/xcore/stream.h" // lib source code
#include <stdio.h>
#include <string.h>

// Function to log a movement
void log_movement(cstream *stream, const char *direction, double distance) {
    char log_entry[100];
    sprintf(log_entry, "Move %s: %.2f meters\n", direction, distance);
    stream_write(stream, log_entry, 1, strlen(log_entry));
}

// Function to log an event
void log_event(cstream *stream, const char *event_description) {
    char log_entry[100];
    sprintf(log_entry, "Event: %s\n", event_description);
    stream_write(stream, log_entry, 1, strlen(log_entry));
}

int main() {
    // Example log filename
    const char *log_filename = "robot_log.txt";

    // Open the log file for writing
    cstream log_stream;
    if (stream_open(&log_stream, log_filename, "w") == -1) {
        fprintf(stderr, "Error opening log file for writing\n");
        return -1;
    }

    // Log some movements
    log_movement(&log_stream, "Forward", 2.5);
    log_movement(&log_stream, "Right", 1.0);
    log_movement(&log_stream, "Backward", 3.2);

    // Log an event
    log_event(&log_stream, "Emergency Stop");

    // Close the log file
    stream_close(&log_stream);

    // Open the log file for reading and display its content
    if (stream_open(&log_stream, log_filename, "r") == -1) {
        fprintf(stderr, "Error opening log file for reading\n");
        return -1;
    }

    const size_t buffer_size = 256;
    char read_buffer[buffer_size];
    size_t elements_read = stream_read(&log_stream, read_buffer, 1, buffer_size - 1);

    if (elements_read == 0) {
        fprintf(stderr, "Error reading data from the log file\n");
        stream_close(&log_stream);
        return -1;
    }

    // Null-terminate the read data
    read_buffer[elements_read] = '\0';

    // Close the log file
    stream_close(&log_stream);

    // Display the log content
    printf("Robot Log:\n%s", read_buffer);

    return 0;
} // end of func
