#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>
#include <stddef.h>

typedef enum {
    SUCCESS = 0,
    INVALID_ARG = -1,
    INVALID_BASE = -2,
    OUT_OF_RANGE = -3,
} Code;

Code to_power_of_two_system(char** result, size_t* result_size, char* buff, size_t buff_size, int64_t num, int64_t base);

#endif //FUNCTIONS_H
