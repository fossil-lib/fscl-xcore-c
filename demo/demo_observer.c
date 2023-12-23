/*  ----------------------------------------------------------------------------
    File: demo_reader.c

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
#include <trilobite/xcore/observer.h>
#include <stdio.h>
#include <stdbool.h>

// Example usage
void exampleObserverUpdate(void* data) {
    printf("Observer notified with data: %s\n", (const char*)data);
}

int main() {
    // Create a subject
    csubject subject;
    tscl_observe_create(&subject);

    // Create an observer
    cobserver observer;
    observer.update = exampleObserverUpdate;

    // Add the observer to the subject
    tscl_observe_add_observer(&subject, &observer);

    // Notify observers of an event
    const char* eventData = "Event Occurred";
    tscl_observe_notify(&subject, (void*)eventData);

    // Additional functionality
    if (tscl_observe_has_observers(&subject)) {
        printf("Subject has observers.\n");
    }

    // Erase all observers
    tscl_observe_erase_all(&subject);

    // Erase the subject
    tscl_observe_erase(&subject);

    return 0;
} // end of func
