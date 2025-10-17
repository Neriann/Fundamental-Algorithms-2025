#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdint.h>


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
    TO_LOWER_DECIMAL,
    TO_UPPER_DECIMAL,
    INTEGER_MEMORY,
    UNSIGNED_INTEGER_MEMORY,
    DOUBLE_MEMORY,
    FLOAT_MEMORY,
    UNDEFINED_FLAG,
} flag_t;

typedef uint8_t bool;

typedef enum {
    SUCCESS = 0,
    BUFF_OVERFLOW = -1,
    ZERO_NUMBER = -2,
    EMPTY_BUFF = -3,
    MEM_ALLOC = -4,
    INVALID_CASE = -5
} Code;

typedef struct {
    const char* flag_name;
    flag_t flag_value;
} Status;

extern Status flags[];

int64_t overfprintf(FILE* stream, const char* format, ...);

int64_t oversprintf(char* str, const char* format, ...);


#endif //FUNCTIONS_H
