/*  ----------------------------------------------------------------------------
    File: demo_format.c

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
#include <trilobite/xcore/format.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Structure to represent a booking
typedef struct {
    char customer_name[50];
    cdatetime start_time;
    cdatetime end_time;
} booking;

// Function to book a time slot
bool book_time_slot(booking *bookings, int max_bookings, const char *customer_name, const cdatetime *start_time, const cdatetime *end_time) {
    // Check if the time slot is available
    for (int i = 0; i < max_bookings; ++i) {
        // Check if there's an overlap with an existing booking
        if (strcmp(bookings[i].customer_name, "") != 0 &&
            ((start_time->year < bookings[i].end_time.year) ||
             (start_time->year == bookings[i].end_time.year && start_time->month < bookings[i].end_time.month) ||
             (start_time->year == bookings[i].end_time.year && start_time->month == bookings[i].end_time.month && start_time->day < bookings[i].end_time.day) ||
             (start_time->year == bookings[i].end_time.year && start_time->month == bookings[i].end_time.month && start_time->day == bookings[i].end_time.day && start_time->hour < bookings[i].end_time.hour) ||
             (start_time->year == bookings[i].end_time.year && start_time->month == bookings[i].end_time.month && start_time->day == bookings[i].end_time.day && start_time->hour == bookings[i].end_time.hour && start_time->minute < bookings[i].end_time.minute))) {
            // There's an overlap, the time slot is not available
            printf("Sorry, the requested time slot is not available.\n");
            return false;
        }
    }

    // Find an empty slot to book
    for (int i = 0; i < max_bookings; ++i) {
        if (strcmp(bookings[i].customer_name, "") == 0) {
            // Book the time slot
            strcpy(bookings[i].customer_name, customer_name);
            memcpy(&bookings[i].start_time, start_time, sizeof(cdatetime));
            memcpy(&bookings[i].end_time, end_time, sizeof(cdatetime));
            printf("Booking successful for %s from %d-%02d-%02d %02d:%02d to %d-%02d-%02d %02d:%02d.\n",
                   customer_name, start_time->year, start_time->month, start_time->day, start_time->hour, start_time->minute,
                   end_time->year, end_time->month, end_time->day, end_time->hour, end_time->minute);
            return true;
        }
    }

    // No available slots
    printf("Sorry, no available slots for booking.\n");
    return false;
} // end of func

// Function to display booked slots
void display_booked_slots(const booking *bookings, int max_bookings) {
    printf("Booked Slots:\n");
    for (int i = 0; i < max_bookings; ++i) {
        if (strcmp(bookings[i].customer_name, "") != 0) {
            printf("%s booked from %d-%02d-%02d %02d:%02d to %d-%02d-%02d %02d:%02d.\n",
                   bookings[i].customer_name, bookings[i].start_time.year, bookings[i].start_time.month, bookings[i].start_time.day,
                   bookings[i].start_time.hour, bookings[i].start_time.minute, bookings[i].end_time.year, bookings[i].end_time.month,
                   bookings[i].end_time.day, bookings[i].end_time.hour, bookings[i].end_time.minute);
        }
    }
} // end of func

int main() {
    // Define the maximum number of bookings
    const int max_bookings = 5;

    // Array to store bookings
    booking bookings[max_bookings];

    // Initialize bookings array
    for (int i = 0; i < max_bookings; ++i) {
        strcpy(bookings[i].customer_name, "");
    }

    // Example: Book a time slot
    cdatetime start_time = {2023, 12, 8, 14, 0, 0, -1, "+0300"};
    cdatetime end_time = {2023, 12, 8, 15, 0, 0, -1, "+0300"};
    book_time_slot(bookings, max_bookings, "John Doe", &start_time, &end_time);

    // Example: Display booked slots
    display_booked_slots(bookings, max_bookings);

    return 0;
} // end of func
