#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>
#include <stdio.h>

typedef uint8_t bool;

typedef enum {
    INTEGER = 0,
    LONG_INTEGER,
    LONGLONG_INTEGER,
    UNSIGNED_INTEGER,
    LONG_UNSIGNED_INTEGER,
    LONGLONG_UNSIGNED_INTEGER,
    FLOAT,
    DOUBLE,
    LONG_DOUBLE,
    CHAR,
    STRING,
    ROMAN,
    ZECKENDORF,
    TO_LOWER_INTEGER_BASE,
    TO_UPPER_INTEGER_BASE,
    UNDEFINED_FLAG,
} flag_t;

typedef struct {
    const char* flag_name;
    flag_t flag_value;
} Status;

typedef enum {
    SUCCESS = 0,
    INVALID_ARG = -1,
    MEM_ALLOC = -2,
    ZERO_NUMBER = -3,
    INVALID_CASE = -4
} Code;

int overfscanf(FILE* stream, const char* format, ...);

int oversscanf(char* buff, const char* format, ...);


#endif //FUNCTIONS_H
