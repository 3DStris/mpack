/*
 * Copyright (c) 2015 Nicholas Fraser
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef MPACK_TEST_H
#define MPACK_TEST_H 1

#define _DEFAULT_SOURCE 1
#define _BSD_SOURCE 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "mpack/mpack.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This is basically the whole unit testing framework for mpack.
 * The reported number of "tests" is the total number of test asserts,
 * where each actual test case has several asserts.
 */

extern char* assertion;

// enable this to exit at the first error
#define TEST_EARLY_EXIT 1

#define test_assert(expr, ...) do { \
    ++tests; \
    if (expr) { \
        ++passes; \
    } else { \
        printf("TEST FAILED AT %s:%i --", __FILE__, __LINE__); \
        printf(" " __VA_ARGS__); \
        printf("\n"); \
        if (assertion) \
            printf("\nalso hit an assertion: %s\n", assertion); \
        if (TEST_EARLY_EXIT) \
            exit(EXIT_FAILURE); \
    } \
} while (0)

#define test_check_no_assertion() do { \
    test_assert(assertion == NULL, \
            "hit an assertion: %s", assertion); \
    if (assertion) { \
        free(assertion); \
        assertion = NULL; \
    } \
} while (0)

extern int tests;
extern int passes;

// if an assert is hit within mpack, the string is stored here.
extern char* assertion;

#ifdef __cplusplus
}
#endif

#endif

