/*  ----------------------------------------------------------------------------
    File: demo_ini.c

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
#include <trilobite/xcore/ini.h>
#include <stdio.h>

// Structure to store energy data
typedef struct {
    double consumption;
    double production;
} EnergyData;

// Function to print energy data
void printEnergyData(const EnergyData* data) {
    printf("Energy Consumption: %.2f kWh\n", data->consumption);
    printf("Renewable Energy Production: %.2f kWh\n", data->production);
}

int main() {
    // Read initial energy data from the configuration file
    FILE* configFile = fopen("energy_config.ini", "r");
    if (configFile == NULL) {
        perror("Error opening configuration file");
        return 1;
    }

    cini* iniData;
     tscl_ini_parser_create(&iniData);
     tscl_ini_parser_parse(configFile, &iniData);
    fclose(configFile);

    // Extract initial energy data
    EnergyData energy;
    energy.consumption = atof( tscl_ini_parser_get_value(iniData, "Energy", "Consumption"));
    energy.production = atof( tscl_ini_parser_get_value(iniData, "Energy", "Production"));

    // Display initial energy data
    printf("Initial Energy Data:\n");
    printEnergyData(&energy);

    // Simulate a period of energy consumption and renewable energy production
    // For simplicity, let's just update the values directly in memory
    energy.consumption += 10.5;  // Simulate 10.5 kWh of additional consumption
    energy.production += 5.2;    // Simulate 5.2 kWh of additional renewable energy production

    // Update the configuration file with the new energy data
     tscl_ini_parser_set_value(iniData, "Energy", "Consumption", energy.consumption);
     tscl_ini_parser_set_value(iniData, "Energy", "Production", energy.production);

    // Save the updated configuration to a new file
    FILE* updatedConfigFile = fopen("updated_energy_config.ini", "w");
    if (updatedConfigFile == NULL) {
        perror("Error opening updated configuration file");
         tscl_ini_parser_erase(&iniData);
        return 1;
    }

     tscl_ini_parser_save(updatedConfigFile, iniData);
    fclose(updatedConfigFile);

    // Display updated energy data
    printf("\nUpdated Energy Data:\n");
    printEnergyData(&energy);

    // Cleanup
     tscl_ini_parser_erase(&iniData);

    return 0;
} // end of func
