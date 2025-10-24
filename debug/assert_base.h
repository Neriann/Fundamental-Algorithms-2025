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
} while (0);

#define _ASSERT_MSG(expr, fmt, ...) \
do { \
    if (!(expr)) { \
        fprintf(stderr, "[FAIL] Assertion failed: %s\n", #expr); \
        fprintf(stderr, "Message: " fmt "\n", ##__VA_ARGS__); \
        fprintf(stderr, "File: %s, Line: %d\n", __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    } else { \
        fprintf(stdout, "[OK] Test passed: %s with " fmt "\n", #expr, ##__VA_ARGS__); \
    } \
} while (0);

#endif
