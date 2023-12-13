/*  ----------------------------------------------------------------------------
    File: demo_json.c

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
#include <trilobite/xcore/json.h>
#include <stdio.h>

void present_question(cjson_object* question) {
    printf("%s\n", json_parser_getter(&question->pairs[0].value));  // Print the question

    cjson_array* options = json_parser_get_array(&question->pairs[1].value);
    for (size_t i = 0; i < options->numItems; ++i) {
        printf("%zu. %s\n", i + 1, options->items[i]);  // Print options
    }

    printf("Your answer: ");
} // end of func

int main() {
    // Load the quiz data from a file
    FILE* quizFile = fopen("quiz_game.json", "r");
    if (quizFile == NULL) {
        perror("Error opening quiz file");
        return 1;
    }

    cjson* quizData = json_parser_create();
    if (!json_parser_parse(quizFile, &quizData)) {
        perror("Error parsing quiz file");
        fclose(quizFile);
        json_parser_erase(&quizData);
        return 1;
    }

    fclose(quizFile);

    // Extract quiz array
    cjson_object* quizObject = json_parser_get_object(&quizData);
    cjson_array* quizArray = json_parser_get_array(&quizObject->pairs[0].value);

    // Loop through each question in the quiz
    for (size_t i = 0; i < quizArray->numItems; ++i) {
        cjson_object* question = json_parser_get_object(&quizArray->items[i]);

        present_question(question);

        int userAnswer;
        scanf("%d", &userAnswer);

        // Check the user's answer
        const char* correctAnswer = json_parser_getter(&question->pairs[2].value);
        if (userAnswer >= 1 && userAnswer <= (int)options->numItems) {
            if (strcmp(options->items[userAnswer - 1], correctAnswer) == 0) {
                printf("Correct!\n");
            } else {
                printf("Incorrect. The correct answer is: %s\n", correctAnswer);
            }
        } else {
            printf("Invalid answer choice\n");
        }

        printf("\n");
    }

    // Clean up
    json_parser_erase(&quizData);

    return 0;
} // end of func
