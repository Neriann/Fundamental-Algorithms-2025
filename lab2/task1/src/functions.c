#include <stdarg.h>
#include <stddef.h>

#include "functions.h"


void real_to_fraction(double real, uint32_t* numerator, uint32_t* denominator) {
    size_t i = 0;
    while (real * *denominator != *numerator && i < 19) {
        // 19 - лимит знаков для double + 1 на запас
        *denominator *= 10;
        *numerator = (int32_t)(real * *denominator);
        ++i;
    }
}


uint32_t gcd(uint32_t a, uint32_t b) {
    while (b) {
        uint32_t tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

Code factorize(uint32_t num, uint32_t base) {
    for (uint32_t d = 2; d * d <= num; ++d) {
        if (num % d == 0) {
            if (base % d != 0) {
                return FAILURE;
            }
            while (num % d == 0) {
                num /= d;
            }
        }
    }
    if (num > 1 && base % num != 0) {
        return FAILURE;
    }
    return SUCCESS;
}


Code is_final_value(Solution* result, int32_t count, ...) {
    if (count <= 0) {
        return INVALID_ARG;
    }
    if (count % 2 != 0) {
        return INVALID_ARG;
    }
    if (!result) {
        return INVALID_ARG;
    }
    va_list args;
    va_start(args, count);

    for (size_t i = 0; i < count / 2; ++i) {
        double real = va_arg(args, double);
        int32_t base = va_arg(args, int32_t);
        if (real == -1.0 || base == -1) {
            return INVALID_ARG;
        }
        if (real < 0 || real > 1) {
            result->code = INVALID_ARG;
        } else if (base < 2 || base > 36) {
            result->code = INVALID_ARG;
        }else {
            uint32_t numerator = 1, denominator = 1;
            real_to_fraction(real, &numerator, &denominator);
            uint32_t g = gcd(numerator, denominator);
            numerator /= g;
            denominator /= g;
            result->code = factorize(denominator, base);
            result->real = real;
            result->base = base;
        }
        ++result;
    }
    va_end(args);
    return SUCCESS;
}
