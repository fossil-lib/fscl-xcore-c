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
#ifndef TSCL_THREAD_H
#define TSCL_THREAD_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _WIN32 // Windows-specific

#include <windows.h>

typedef DWORD(WINAPI *CThreadFunc)(LPVOID); // Define your function pointer type
typedef HANDLE cthread; // Define the thread type
#else // POSIX-specific

#include <pthread.h>

typedef void *(*CThreadFunc)(void *); // Define your function pointer type
typedef pthread_t cthread; // Define the thread type
#endif

#ifdef _WIN32
#define CTHREAD_TASK_RETURN_TYPE DWORD WINAPI
#define CTHREAD_TASK_ARG_TYPE LPVOID
#else
#define CTHREAD_TASK_RETURN_TYPE void*
#define CTHREAD_TASK_ARG_TYPE void*
#endif

#ifdef _WIN32
#define CTHREAD_CNULLPTR 0
#else
#define CTHREAD_CNULLPTR NULL
#endif

typedef struct {
    cthread* threads;
    int num_threads;
} cthread_pool;

typedef struct {
    #ifdef _WIN32
    HANDLE mutex;
    #else
    pthread_mutex_t mutex;
    #endif
} cmutex;

#define cthread_task(name, arg) CTHREAD_TASK_RETURN_TYPE name(CTHREAD_TASK_ARG_TYPE arg)

// =================================================================
//  Classic Thread Management
// =================================================================
cthread tscl_thread_create(CThreadFunc func, void* arg);
void tscl_thread_join(cthread handle);
void tscl_thread_erase(cthread handle);
void tscl_thread_sleep(unsigned int milliseconds);
void tscl_thread_yield();
void tscl_thread_detach(cthread handle);
unsigned long tscl_thread_get_id();

// =================================================================
//  Thread Pool Management
// =================================================================
cthread_pool tscl_thread_pool_create(int num_threads);
void tscl_thread_pool_execute(cthread_pool pool, CThreadFunc func, void* arg);
void tscl_thread_pool_wait(cthread_pool pool);
void tscl_thread_pool_erase(cthread_pool pool);

// =================================================================
// Mutex thread managment
// =================================================================
void tscl_mutex_create(cmutex* mutex);
void tscl_mutex_lock(cmutex* mutex);
void tscl_mutex_unlock(cmutex* mutex);
void tscl_mutex_erase(cmutex* mutex);

#ifdef __cplusplus
}
#endif

#endif
