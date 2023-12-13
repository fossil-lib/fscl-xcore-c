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
#ifndef TSCL_MOD_H
#define TSCL_MOD_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Adds two integers.
 *
 * This function takes two integer values, 'a' and 'b', and returns their sum.
 *
 * @param a The first integer.
 * @param b The second integer.
 * @return The sum of 'a' and 'b'.
 */
int add(int a, int b);

/**
 * Subtracts one integer from another.
 *
 * This function takes two integer values, 'a' and 'b', and returns the result of
 * subtracting 'b' from 'a'.
 *
 * @param a The integer from which 'b' will be subtracted.
 * @param b The integer to subtract from 'a'.
 * @return The result of 'a' - 'b'.
 */
int subtract(int a, int b);

#ifdef __cplusplus
}
#endif

#endif
