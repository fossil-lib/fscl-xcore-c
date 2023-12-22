/*  ----------------------------------------------------------------------------
    File: demo_thread.c

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
#include <trilobite/xcore/thread.h>
#include <trilobite/xcore/stream.h>

// Function to simulate robot movements
cthread_task(robot_movement, arg) {
    cstream *log_stream = (cstream *)arg;

    // Log robot movements
    log_to_file(log_stream, "Robot starts moving forward.\n");
    tscl_thread_sleep(1000);
    
    log_to_file(log_stream, "Robot turns right.\n");
    tscl_thread_sleep(500);
    
    log_to_file(log_stream, "Robot continues moving forward.\n");
    tscl_thread_sleep(1500);
    
    log_to_file(log_stream, "Robot moves backward.\n");
    tscl_thread_sleep(1000);
    
    log_to_file(log_stream, "Robot stops.\n");

    return CTHREAD_CNULLPTR;
} // end of func

int main() {
    // Create a log file
    cstream log_stream;
    tscl_stream_create(&log_stream, "robot_log.txt");

    // Create a thread for robot movement
    cthread robot_thread = tscl_thread_create(robot_movement, (void *)&log_stream);

    // Wait for the robot thread to finish
    tscl_thread_join(robot_thread);

    // Destroy the robot thread handle
    tscl_thread_erase(robot_thread);

    // Close the log file
    tscl_stream_close(&log_stream);

    printf("Robotics demo completed. Check 'robot_log.txt' for the log.\n");

    return 0;
} // end of func
