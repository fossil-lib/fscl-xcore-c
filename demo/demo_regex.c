/*  ----------------------------------------------------------------------------
    File: demo_regex.c

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
#include "trilobite/xcore/regex.h" // lib source code
#include <stdio.h>

// Function to clean weather data
void clean_weather_data(const char *weather_data) {
    // Create cregex structures for temperature, humidity, and date patterns
    cregex temp_regex, humidity_regex, date_regex;

    // Example patterns
    const char *temp_pattern = "Temperature: ([0-9]+)\\.([0-9]+) C";
    const char *humidity_pattern = "Humidity: ([0-9]+)%";
    const char *date_pattern = "Date: ([0-9]{4}-[0-9]{2}-[0-9]{2})";

    tscl_regex_create(&temp_regex, temp_pattern);
    tscl_regex_create(&humidity_regex, humidity_pattern);
    tscl_regex_create(&date_regex, date_pattern);

    // Process weather data
    const char *current_line = weather_data;
    while (*current_line != '\0') {
        // Extract temperature
        const char *temp_value = tscl_regex_match_and_extract(&temp_regex, current_line);
        if (temp_value != NULL) {
            double temperature = atof(temp_value);
            printf("Temperature: %.2f C\n", temperature);
        }

        // Extract humidity
        const char *humidity_value = tscl_regex_match_and_extract(&humidity_regex, current_line);
        if (humidity_value != NULL) {
            int humidity = atoi(humidity_value);
            printf("Humidity: %d%%\n", humidity);
        }

        // Extract date
        const char *date_value = tscl_regex_match_and_extract(&date_regex, current_line);
        if (date_value != NULL) {
            printf("Date: %s\n", date_value);
        }

        // Move to the next line
        current_line = strchr(current_line, '\n');
        if (current_line != NULL) {
            current_line++; // Move past the newline character
        }
    }

    // Cleanup
    tscl_regex_reset(&temp_regex);
    tscl_regex_reset(&humidity_regex);
    tscl_regex_reset(&date_regex);
}

int main() {
    // Example weather data
    const char *weather_data = "Temperature: 25.5 C\nHumidity: 60%\nDate: 2023-12-08\n";

    // Clean the weather data
    clean_weather_data(weather_data);

    return 0;
} // end of func
