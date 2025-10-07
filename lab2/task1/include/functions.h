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
    uint32_t base;
    Code code;
} Solution;

uint32_t gcd(uint32_t a, uint32_t b);

void real_to_fraction(double real, uint32_t* numerator, uint32_t* denominator);

Code factorize(uint32_t num, uint32_t base);

Code is_final_value(Solution* result, int32_t count, ...);

#endif //FUNCTIONS_H
