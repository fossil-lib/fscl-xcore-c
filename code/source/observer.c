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
#include "fossil/xcore/observer.h"
#include <stdlib.h>
#include <string.h>

// Function to initialize a subject
void fscl_observe_create(csubject* subject) {
    subject->observers = NULL;
    subject->numObservers = 0;
}

// Function to add an observer to the subject
void fscl_observe_add_observer(csubject* subject, cobserver* observer) {
    subject->observers = (cobserver**)realloc(subject->observers, (subject->numObservers + 1) * sizeof(cobserver*));
    subject->observers[subject->numObservers++] = observer;
}

// Function to remove an observer from the subject
void fscl_observe_remove_observer(csubject* subject, cobserver* observer) {
    for (int i = 0; i < subject->numObservers; ++i) {
        if (subject->observers[i] == observer) {
            // Shift remaining elements to fill the gap
            for (int j = i; j < subject->numObservers - 1; ++j) {
                subject->observers[j] = subject->observers[j + 1];
            }
            // Resize the array
            subject->observers = (cobserver**)realloc(subject->observers, (subject->numObservers - 1) * sizeof(cobserver*));
            subject->numObservers--;
            break;
        }
    }
}

// Function to notify all observers of an event
void fscl_observe_notify(csubject* subject, void* data) {
    for (int i = 0; i < subject->numObservers; ++i) {
        if (subject->observers[i]->update != NULL) {
            subject->observers[i]->update(data);
        }
    }
}

// Function to clear all observers
void fscl_observe_erase_all(csubject* subject) {
    free(subject->observers);
    subject->observers = NULL;
    subject->numObservers = 0;
}

// Function to check if the subject has observers
int fscl_observe_has_observers(csubject* subject) {
    return subject->numObservers > 0;
}

// Function to perform subject cleanup
void fscl_observe_erase(csubject* subject) {
    free(subject->observers);
    subject->observers = NULL;
    subject->numObservers = 0;
    // Additional cleanup steps, if needed
}

// Function to update all observers with data
void fscl_observe_update_all(csubject* subject, void* data) {
    for (int i = 0; i < subject->numObservers; ++i) {
        if (subject->observers[i]->update != NULL) {
            subject->observers[i]->update(data);
        }
    }
}
