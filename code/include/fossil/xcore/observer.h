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
#ifndef FSCL_OBSREVER_H
#define FSCL_OBSREVER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>

// Structure representing an observer
typedef struct {
    void (*update)(void* data); // Function pointer for the update method
} cobserver;

// Structure representing the subject to be observed
typedef struct {
    cobserver** observers; // Array of observers
    int numObservers;      // Number of observers
} csubject;

// =================================================================
// create and erase
// =================================================================
void fscl_observe_create(csubject* subject);
void fscl_observe_erase(csubject* subject);
void fscl_observe_update_all(csubject* subject, void* data);

// =================================================================
// addintal functions
// =================================================================
void fscl_observe_add_observer(csubject* subject, cobserver* observer);
void fscl_observe_remove_observer(csubject* subject, cobserver* observer);
void fscl_observe_notify(csubject* subject, void* data);
void fscl_observe_erase_all(csubject* subject);
int fscl_observe_has_observers(csubject* subject);



#ifdef __cplusplus
}
#endif

#endif
