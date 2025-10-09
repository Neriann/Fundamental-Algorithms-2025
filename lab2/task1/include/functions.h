#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>

typedef enum {
    SUCCESS = 0,
    FAILURE,
    INVALID_ARG,
} Code;

typedef struct {
    double real;
    uint64_t base;
    Code code;
} Solution;

uint64_t gcd(uint64_t a, uint64_t b);

void real_to_fraction(double real, uint64_t* numerator, uint64_t* denominator);

Code factorize(uint64_t num, uint64_t base);

Code is_final_value(Solution* result, int32_t base, int32_t count, ...);

#endif //FUNCTIONS_H
