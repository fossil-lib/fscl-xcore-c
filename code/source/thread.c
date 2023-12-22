/*  ----------------------------------------------------------------------------
    File: thread.c

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
#include "trilobite/xcore/thread.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
// Windows-specific cthread implementation
#include <windows.h>

// Define a structure to hold thread data
struct CThreadData {
    CThreadFunc func;
    void* arg;
};

// The thread start routine that will be passed to CreateThread
DWORD WINAPI cthreadStartRoutine(LPVOID lpParameter) {
    // Cast the parameter back to the thread data structure
    struct CThreadData* data = (struct CThreadData*)lpParameter;

    // Call the thread function with the provided argument
    DWORD result = data->func(data->arg);

    // Free the memory allocated for the thread data
    free(data);

    // Return the result of the thread function
    return result;
} // end of func

// Function to create a new thread
HANDLE tscl_thread_create(CThreadFunc func, void* arg) {
    if (!func) return NULL;  // Add error checking for function pointer

    // Allocate memory for the thread data
    struct CThreadData* data = malloc(sizeof(struct CThreadData));
    if (!data) return NULL;  // Add error checking for memory allocation

    // Set the function and argument in the thread data structure
    data->func = func;
    data->arg = arg;

    // Create a new thread using CreateThread
    return CreateThread(NULL, 0, cthreadStartRoutine, data, 0, NULL);
} // end of func

void tscl_thread_join(cthread handle) {
    if (handle) {
        WaitForSingleObject(handle, INFINITE);
    }
} // end of func

void tscl_thread_erase(cthread handle) {
    if (handle) {
        CloseHandle(handle);
    }
} // end of func

void tscl_thread_sleep(unsigned int milliseconds) {
    Sleep(milliseconds);
} // end of func

void tscl_thread_yield() {
    SwitchToThread();
} // end of func

void tscl_thread_detach(cthread handle) {
    // Detaching not applicable on Windows
    // You may need to manage thread detachment differently based on your requirements
} // end of func

unsigned long tscl_thread_get_id() {
    return GetCurrentThreadId();
} // end of func

#else
// POSIX-specific cthread implementation
#include <pthread.h>
#include <unistd.h>

cthread tscl_thread_create(CThreadFunc func, void* arg) {
    if (!func) {
        return (cthread)NULL;
    }
    pthread_t thread;
    if (pthread_create(&thread, NULL, (void* (*)(void*))func, arg) != 0) {
        return (cthread)NULL;  // Add error checking for thread creation
    }
    return thread;
} // end of func

void tscl_thread_join(cthread handle) {
    if (handle) {
        pthread_join((cthread)handle, NULL);
    }
} // end of func

void tscl_thread_erase(cthread handle) {
    // No specific cleanup needed for POSIX threads
} // end of func

void tscl_thread_sleep(unsigned int milliseconds) {
    sleep(milliseconds * 1000);  // usleep takes microseconds
} // end of func

void tscl_thread_yield() {
    sched_yield();
} // end of func

void tscl_thread_detach(cthread handle) {
    if (handle) {
        pthread_detach((cthread)handle);
    }
} // end of func

unsigned long tscl_thread_get_id() {
    return (unsigned long)pthread_self();
} // end of func

#endif  // _WIN32

// Create a thread pool with the specified number of threads.
cthread_pool tscl_thread_pool_create(int num_threads) {
    cthread_pool pool;
    pool.threads = (cthread*)malloc(num_threads * sizeof(cthread));
    pool.num_threads = num_threads;

    for (int i = 0; i < num_threads; ++i) {
        pool.threads[i] = tscl_thread_create(NULL, NULL);
    }

    return pool;
} // end of func

// Execute a task asynchronously using a thread from the pool.
void tscl_thread_pool_execute(cthread_pool pool, CThreadFunc func, void* arg) {
    int thread_index = rand() % pool.num_threads; // Choose a random thread for simplicity

    tscl_thread_erase(pool.threads[thread_index]); // Ensure the thread is in a clean state

    pool.threads[thread_index] = tscl_thread_create(func, arg);
} // end of func

// Wait for all tasks in the thread pool to complete.
void tscl_thread_pool_wait(cthread_pool pool) {
    for (int i = 0; i < pool.num_threads; ++i) {
        thread_join(pool.threads[i]);
    }
} // end of func

// Destroy the thread pool.
void tscl_thread_pool_erase(cthread_pool pool) {
    for (int i = 0; i < pool.num_threads; ++i) {
        tscl_thread_erase(pool.threads[i]);
    }

    free(pool.threads);
} // end of func

void tscl_mutex_create(cmutex* mutex) {
    #ifdef _WIN32
    mutex->mutex = CreateMutex(NULL, FALSE, NULL);
    #else
    pthread_mutex_init(&(mutex->mutex), NULL);
    #endif
} // end of func

void tscl_mutex_lock(cmutex* mutex) {
    #ifdef _WIN32
    WaitForSingleObject(mutex->mutex, INFINITE);
    #else
    pthread_mutex_lock(&(mutex->mutex));
    #endif
} // end of func

void tscl_mutex_unlock(cmutex* mutex) {
    #ifdef _WIN32
    ReleaseMutex(mutex->mutex);
    #else
    pthread_mutex_unlock(&(mutex->mutex));
    #endif
} // end of func

void tscl_mutex_erase(cmutex* mutex) {
    #ifdef _WIN32
    CloseHandle(mutex->mutex);
    #else
    pthread_mutex_destroy(&(mutex->mutex));
    #endif
} // end of func
