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
#ifndef FSCL_THREAD_H
#define FSCL_THREAD_H

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
// Classic Thread Management
// =================================================================

/**
 * Create a new thread.
 *
 * @param func The function to be executed by the thread.
 * @param arg  The argument to be passed to the thread function.
 * @return     A handle to the created thread.
 */
cthread fscl_thread_create(CThreadFunc func, void* arg);

/**
 * Wait for a thread to finish execution.
 *
 * @param handle The handle of the thread to join.
 */
void fscl_thread_join(cthread handle);

/**
 * Erase a thread and free associated resources.
 *
 * @param handle The handle of the thread to erase.
 */
void fscl_thread_erase(cthread handle);

/**
 * Sleep the current thread for a specified number of milliseconds.
 *
 * @param milliseconds The duration of sleep in milliseconds.
 */
void fscl_thread_sleep(unsigned int milliseconds);

/**
 * Yield the execution of the current thread to another thread.
 */
void fscl_thread_yield();

/**
 * Detach a thread, allowing it to run independently.
 *
 * @param handle The handle of the thread to detach.
 */
void fscl_thread_detach(cthread handle);

/**
 * Get the ID of the current thread.
 *
 * @return The ID of the current thread.
 */
unsigned long fscl_thread_get_id();

// =================================================================
// Thread Pool Management
// =================================================================

/**
 * Create a new thread pool with a specified number of threads.
 *
 * @param num_threads The number of threads in the pool.
 * @return            A handle to the created thread pool.
 */
cthread_pool fscl_thread_pool_create(int num_threads);

/**
 * Execute a task in the thread pool.
 *
 * @param pool The thread pool in which to execute the task.
 * @param func The function to be executed by a thread in the pool.
 * @param arg  The argument to be passed to the thread function.
 */
void fscl_thread_pool_execute(cthread_pool pool, CThreadFunc func, void* arg);

/**
 * Wait for all tasks in the thread pool to finish execution.
 *
 * @param pool The thread pool to wait for.
 */
void fscl_thread_pool_wait(cthread_pool pool);

/**
 * Erase a thread pool and free associated resources.
 *
 * @param pool The thread pool to erase.
 */
void fscl_thread_pool_erase(cthread_pool pool);

// =================================================================
// Mutex Thread Management
// =================================================================

/**
 * Create a new mutex.
 *
 * @param mutex Pointer to the cmutex structure to store the created mutex.
 */
void fscl_mutex_create(cmutex* mutex);

/**
 * Lock a mutex, preventing other threads from accessing the protected resource.
 *
 * @param mutex Pointer to the cmutex structure to be locked.
 */
void fscl_mutex_lock(cmutex* mutex);

/**
 * Unlock a locked mutex, allowing other threads to access the protected resource.
 *
 * @param mutex Pointer to the cmutex structure to be unlocked.
 */
void fscl_mutex_unlock(cmutex* mutex);

/**
 * Erase a mutex and free associated resources.
 *
 * @param mutex Pointer to the cmutex structure to be erased.
 */
void fscl_mutex_erase(cmutex* mutex);

#ifdef __cplusplus
}
#endif

#endif
