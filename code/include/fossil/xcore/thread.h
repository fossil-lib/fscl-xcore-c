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
//  Classic Thread Management
// =================================================================
cthread fscl_thread_create(CThreadFunc func, void* arg);
void fscl_thread_join(cthread handle);
void fscl_thread_erase(cthread handle);
void fscl_thread_sleep(unsigned int milliseconds);
void fscl_thread_yield();
void fscl_thread_detach(cthread handle);
unsigned long fscl_thread_get_id();

// =================================================================
//  Thread Pool Management
// =================================================================
cthread_pool fscl_thread_pool_create(int num_threads);
void fscl_thread_pool_execute(cthread_pool pool, CThreadFunc func, void* arg);
void fscl_thread_pool_wait(cthread_pool pool);
void fscl_thread_pool_erase(cthread_pool pool);

// =================================================================
// Mutex thread managment
// =================================================================
void fscl_mutex_create(cmutex* mutex);
void fscl_mutex_lock(cmutex* mutex);
void fscl_mutex_unlock(cmutex* mutex);
void fscl_mutex_erase(cmutex* mutex);

#ifdef __cplusplus
}
#endif

#endif
