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
#ifndef TSCL_OBSREVER_H
#define TSCL_OBSREVER_H

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
void tscl_observe_create(csubject* subject);
void tscl_observe_erase(csubject* subject);
void tscl_observe_update_all(csubject* subject, void* data);

// =================================================================
// addintal functions
// =================================================================
void tscl_observe_add_observer(csubject* subject, cobserver* observer);
void tscl_observe_remove_observer(csubject* subject, cobserver* observer);
void tscl_observe_notify(csubject* subject, void* data);
void tscl_observe_erase_all(csubject* subject);
int tscl_observe_has_observers(csubject* subject);



#ifdef __cplusplus
}
#endif

#endif
