#include <stdarg.h>
#include <stddef.h>
#include <math.h>

#include "functions.h"


void real_to_fraction(double real, uint64_t* numerator, uint64_t* denominator) {
    const double EPSILON = 1e-12;
    const size_t MAX_ITERATIONS = 20;

    *denominator = 1;
    *numerator = 0;

    for (size_t i = 0; i < MAX_ITERATIONS; ++i) {
        double candidate = real * (*denominator);
        double rounded = round(candidate);

        if (fabs(candidate - rounded) < EPSILON) {
            *numerator = (uint64_t)rounded;
            return;
        }

        *denominator *= 10;
    }

    // Если точное представление не найдено, используем приближенное
    *numerator = (uint64_t)round(real * (*denominator));
}


uint64_t gcd(uint64_t a, uint64_t b) {
    while (b) {
        uint64_t tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

Code factorize(uint64_t num, uint64_t base) {
    for (uint64_t d = 2; d * d <= num; ++d) {
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


Code is_final_value(Solution* result, int32_t base, int32_t count, ...) {
    if (count <= 0) {
        return INVALID_ARG;
    }
    if (!result) {
        return INVALID_ARG;
    }
    va_list args;
    va_start(args, count);

    for (size_t i = 0; i < count; ++i) {
        double real = va_arg(args, double);
        if (real == -1.0) {
            return INVALID_ARG;
        }
        if (real < 0 || real > 1) {
            result->real = real;
            result->base = base;
            result->code = INVALID_ARG;
        } else {
            uint64_t numerator, denominator;
            real_to_fraction(real, &numerator, &denominator);
            uint64_t g = gcd(numerator, denominator);
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
