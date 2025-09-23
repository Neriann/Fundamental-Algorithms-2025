#ifndef ASSERT_BASE_H
#define ASSERT_BASE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT_MSG(expr) \
do { \
    if (!(expr)) { \
        fprintf(stderr, "[FAIL] Assertion failed: %s\nFile: %s, Line: %d\n", \
                #expr, __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    } else { \
        fprintf(stdout, "[OK] Test was (%s) successful\n", #expr); \
    } \
} while (0)

#endif
