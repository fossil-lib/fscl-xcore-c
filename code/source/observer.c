/*  ----------------------------------------------------------------------------
    File: ini.c

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
#include "trilobite/xcore/observer.h"
#include <stdlib.h>
#include <string.h>

// Function to initialize a subject
void tscl_observe_create(csubject* subject) {
    subject->observers = NULL;
    subject->numObservers = 0;
}

// Function to add an observer to the subject
void tscl_observe_add_observer(csubject* subject, cobserver* observer) {
    subject->observers = (cobserver**)realloc(subject->observers, (subject->numObservers + 1) * sizeof(cobserver*));
    subject->observers[subject->numObservers++] = observer;
}

// Function to remove an observer from the subject
void tscl_observe_remove_observer(csubject* subject, cobserver* observer) {
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
void tscl_observe_notify(csubject* subject, void* data) {
    for (int i = 0; i < subject->numObservers; ++i) {
        if (subject->observers[i]->update != NULL) {
            subject->observers[i]->update(data);
        }
    }
}

// Function to clear all observers
void tscl_observe_erase_all(csubject* subject) {
    free(subject->observers);
    subject->observers = NULL;
    subject->numObservers = 0;
}

// Function to check if the subject has observers
int tscl_observe_has_observers(csubject* subject) {
    return subject->numObservers > 0;
}

// Function to perform subject cleanup
void tscl_observe_erase(csubject* subject) {
    free(subject->observers);
    subject->observers = NULL;
    subject->numObservers = 0;
    // Additional cleanup steps, if needed
}

// Function to update all observers with data
void tscl_observe_update_all(csubject* subject, void* data) {
    for (int i = 0; i < subject->numObservers; ++i) {
        if (subject->observers[i]->update != NULL) {
            subject->observers[i]->update(data);
        }
    }
}
