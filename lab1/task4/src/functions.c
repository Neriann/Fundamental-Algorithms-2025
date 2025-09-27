#include <math.h>
#include <stddef.h>

// #include "primes/functions.h"
#include "approximate_values/functions.h"


#include "approximate_values/constants.h"

#define MAX_ITERS (int64_t)1e9

long double bin_pow(long double a, int64_t b) {
    long double result = 1;
    while (b) {
        if (b & 1) {
            result = result * a;
        }
        a = a * a;
        b >>= 1;
    }
    return result;
}


long double my_abs(const long double a) {
    return a < 0 ? -a : a;
}

long double get_fact(long double n) {
    long double result = 1;
    for (int64_t i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

long double get_exponent_from_limit(const long double epsilon) {
    int64_t n = 1;
    long double result;
    do {
        result = bin_pow(1 + 1.0 / (double)n, n);
        ++n;
    }
    while (my_abs(result - EXP) >= epsilon && n < MAX_ITERS);
    return result;
}

long double get_exponent_from_row(const long double epsilon) {
    long double result = 1;
    long double fact = 1;
    int64_t n = 1;
    while (my_abs(result - EXP) >= epsilon && n < MAX_ITERS) {
        fact = fact * n++;
        result += 1.0L / fact;
    }
    return result;
}

long double get_exponent_from_equation() {
    // lnx = 1 --> x = e^1
    return exp(1);
}

long double get_pi_from_limit(const long double epsilon) {
    // result = 4 при n = 1
    long double result = 4.0L;
    int64_t n = 1;
    while (my_abs(result - PI) >= epsilon && n < MAX_ITERS) {
        // формула выводится путем преобразований отношения a_n+1 / a_n
        result *= 4.0L * n * (n + 1.0L) / ((2.0L * n + 1.0L) * (2.0L * n + 1.0L));
        ++n;
    }
    return result;
}

long double get_pi_from_row(const long double epsilon) {
    long double sum = 0, result;
    int64_t n = 1;
    do {
        sum += (long double)((n - 1) % 2 == 0 ? 1 : -1) / (long double)(2 * n - 1);
        result = 4 * sum;
        ++n;
    }
    while (my_abs(result - PI) >= epsilon && n < MAX_ITERS);
    return result;
}

long double get_pi_from_equation() {
    // cosx = -1 --> x = arccos(-1)
    return acos(-1);
}

long double get_ln2_from_limit(const long double epsilon) {
    long double result = 1;
    int64_t n = 1;
    while (my_abs(result - LN_2) >= epsilon && n < MAX_ITERS) {
        result = n * (pow(2, 1.0 / (double)n) - 1.0L);
        ++n;
    }
    return result;
}

long double get_ln2_from_row(const long double epsilon) {
    long double result = 0;
    int64_t n = 1;
    while (my_abs(result - LN_2) >= epsilon && n < MAX_ITERS) {
        result += ((n - 1) % 2 == 0 ? 1.0L : -1.0L) / n;
        ++n;
    }
    return result;
}

long double get_ln2_from_equation() {
    // e^x = 2 --> x = ln2
    return log(2);
}

long double get_sqrt2_from_limit(const long double epsilon) {
    long double result = -0.5;
    int64_t n = 1;
    while (my_abs(result - SQRT_2) >= epsilon && n < MAX_ITERS) {
        result = result - result * result / 2 + 1;
        ++n;
    }
    return result;
}

long double get_sqrt2_from_row(const long double epsilon) {
    long double result = 1;
    int64_t n = 2;
    while (my_abs(result - SQRT_2) >= epsilon && n < MAX_ITERS) {
        result *= pow(2, pow(2, (double)-n));
        ++n;
    }
    return result;
}

long double get_sqrt2_from_equation() {
    // x^2 = 2 --> x = sqrt(2)
    return sqrt(2);
}




// O(n^2)
long double get_gamma_from_limit(const long double epsilon) {
    long double result = 0;
    int64_t m = 1;

    long double term, fact_m, fact_k, fact_mk, binom, log_fact_k;

    while (my_abs(result - EULER_MASCHERONI) >= epsilon && m < MAX_ITERS) {
        term = 0;
        fact_m = get_fact(m);

        for (int64_t k = 1; k <= m; ++k) {
            fact_k = get_fact(k);
            fact_mk = get_fact(m - k);

            binom = fact_m / (fact_mk * fact_k);
            log_fact_k = logl(fact_k);

            term += binom * (k % 2 == 0 ? 1.0L : -1.0L) / k * log_fact_k;
        }

        result = term;
        ++m;
    }
    return result;
}


long double get_gamma_from_row(const long double epsilon) {
    long double result = - PI * PI / 6;
    int64_t n = 2;
    while (my_abs(result - EULER_MASCHERONI) >= epsilon && n < MAX_ITERS) {
        long double part = floor(sqrt(n));
        result += 1.0L / (part * part) - 1.0L / n;
        ++n;
    }
    return result;
}

long double get_gamma_from_equation(const long double epsilon, const PrimeNumbers* primes) {
    long double result = 0, mul = 1;

    int64_t n = 1, i = 0;
    while (my_abs(result - EULER_MASCHERONI) >= epsilon && n < MAX_ITERS) {
        if (i < primes->size && primes->values[i] <= n) {
            long double p = primes->values[i];
            mul *= (p - 1) / p;
            ++i;
        }
        result = -log(log(n) * mul);
        ++n;
    }
    return result;
}
