#include <math.h>
#include <limits.h>

#include "approximate_values/functions.h"

#define MAX_ITERS (int64_t)1e9

long double bin_pow(long double a, int64_t b) {
    long double result = 1.0L;
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


long double bisection_method(long double epsilon, long double a, long double b,
                             long double (*func)(const long double)) {
    if (func(a) * func(b) > 0) {
        return NAN;
    }
    long double mid, f_mid;
    while ((b - a) / 2.0 >= epsilon) {
        mid = (a + b) / 2;

        f_mid = func(mid);
        if (my_abs(f_mid) == 0) {
            return mid;
        }
        if (func(a) * f_mid < 0) {
            b = mid;
        }
        else {
            a = mid;
        }
    }
    return (a + b) / 2;
}

int64_t get_fact(int64_t n) {
    int64_t result = 1;
    for (int64_t i = 2; i <= n; ++i) {
        // проверка на переполнение
        result *= i;
        if (result < 0) {
            return LLONG_MIN;
        }
    }
    return result;
}

long double get_exponent_from_limit(const long double epsilon) {
    int64_t n = 1;
    long double prev_result, result = 1.0L + 1.0L / n;
    do {
        prev_result = result;
        ++n;
        result = bin_pow(1.0L + 1.0L / n, n);
    }
    while (my_abs(result - prev_result) >= epsilon && n < MAX_ITERS);
    return result;
}

long double get_exponent_from_row(const long double epsilon) {
    long double prev_result, result = 1;
    long double fact = 1;
    int64_t n = 1;
    do {
        fact = fact * n++;
        prev_result = result;
        result += 1.0 / fact;
    }
    while (my_abs(result - prev_result) >= epsilon && n < MAX_ITERS);
    return result;
}

long double func_exp(const long double x) {
    return log(x) - 1.0;
}

long double get_exponent_from_equation(const long double epsilon) {
    return bisection_method(epsilon, 2, 3, func_exp);
}

long double get_pi_from_limit(const long double epsilon) {
    // result = 4 при n = 1
    long double prev_result, result = 4.0L;
    int64_t n = 1;
    do {
        // формула выводится путем преобразований отношения a_n+1 / a_n
        prev_result = result;
        result *= 4.0L * n * (n + 1.0L) / ((2.0L * n + 1.0L) * (2.0L * n + 1.0L));
        ++n;
    }
    while (my_abs(result - prev_result) >= epsilon && n < MAX_ITERS);
    return result;
}

long double get_pi_from_row(const long double epsilon) {
    int64_t n = 1;
    long double sum = 0, prev_result, result = 0;
    do {
        sum += (long double)((n - 1) % 2 == 0 ? 1 : -1) / (long double)(2 * n - 1);
        prev_result = result;
        result = 4 * sum;
        ++n;
    }
    while (my_abs(result - prev_result) >= epsilon && n < MAX_ITERS);
    return result;
}

long double func_pi(const long double x) {
    // cos(x) + 1.0 - нет смены знака на интервале [3, 4], поэтому используем эквивалентную функцию
    // cos(x) + 1.0 == 2 * cos^2(x / 2.0) - формула двойного угла
    return cos(x / 2.0);
}

long double get_pi_from_equation(const long double epsilon) {
    return bisection_method(epsilon, 3, 4, func_pi);
}

long double get_ln2_from_limit(const long double epsilon) {
    long double prev_result, result = 1; // при n = 1
    int64_t n = 2;
    do {
        prev_result = result;
        result = n * (powl(2, 1.0L / (long double)n) - 1.0L);
        ++n;
    }
    while (my_abs(result - prev_result) >= epsilon && n < MAX_ITERS);
    return result;
}

long double get_ln2_from_row(const long double epsilon) {
    long double prev_result, result = 0;
    int64_t n = 1;
    do {
        prev_result = result;
        result += ((n - 1) % 2 == 0 ? 1.0L : -1.0L) / n;
        ++n;
    }
    while (my_abs(result - prev_result) >= epsilon && n < MAX_ITERS);
    return result;
}

long double func_ln2(const long double x) {
    return exp(x) - 2.0;
}

long double get_ln2_from_equation(const long double epsilon) {
    // e^x = 2 --> x = ln2
    return bisection_method(epsilon, 0, 1, func_ln2);
}

long double get_sqrt2_from_limit(const long double epsilon) {
    long double prev_result, result = -0.5;
    int64_t n = 1;
    do {
        prev_result = result;
        result = result - result * result / 2 + 1;
        ++n;
    }
    while (my_abs(result - prev_result) >= epsilon && n < MAX_ITERS);
    return result;
}

long double get_sqrt2_from_row(const long double epsilon) {
    long double prev_result, result = 1;
    int64_t n = 2;
    do {
        prev_result = result;
        result *= pow(2, pow(2, (double)-n));
        ++n;
    }
    while (my_abs(result - prev_result) >= epsilon && n < MAX_ITERS);
    return result;
}

long double func_sqrt2(const long double x) {
    return x * x - 2.0;
}

long double get_sqrt2_from_equation(const long double epsilon) {
    return bisection_method(epsilon, 1, 2, func_sqrt2);
}


// O(n^2)
long double get_gamma_from_limit(const long double epsilon) {
    long double prev_result, result = 0;
    int64_t m = 2;

    long double term, binom, log_fact_k;
    int64_t fact_m, fact_k, fact_mk;

    do {
        term = 0;
        fact_m = get_fact(m);
        if (fact_m == LLONG_MIN) {
            break;
        }

        for (int64_t k = 1; k <= m; ++k) {
            fact_k = get_fact(k);
            fact_mk = get_fact(m - k);

            binom = (long double)fact_m / (fact_mk * fact_k);
            log_fact_k = logl(fact_k);

            term += binom * (k % 2 == 0 ? 1.0L : -1.0L) / (long double)k * log_fact_k;
        }
        prev_result = result;
        result = term;
        ++m;
    }
    while (my_abs(result - prev_result) >= epsilon && m < MAX_ITERS);
    return result;
}


long double get_gamma_from_row(const long double epsilon) {
    long double PI = acos(-1.0);
    long double prev_result, result = -PI * PI / 6.0L, part, diff;

    int64_t n = 2, count_stable = 0, max_stable = 3;
    // так как ряд очень медленно сходится получаем результат только когда ряд изменения незначительные несколько раз
    do {
        part = floorl(sqrtl(n));

        prev_result = result;
        result += 1.0L / (part * part) - 1.0L / n;

        diff = my_abs(result - prev_result);
        if (diff < epsilon) {
            ++count_stable;
            if (count_stable > max_stable) {
                break;
            }
        }
        else {
            count_stable = 0;
        }
        ++n;
    }
    while (n < MAX_ITERS);
    return result;
}

long double func_gamma(const long double x, const long double lim) {
    return expl(-x) - lim;
}

// Проверка на простоту
uint8_t is_prime(int32_t n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// Вычисление произведения для данного t
long double compute_product(int32_t t) {
    long double product = 1.0L;
    for (int32_t p = 2; p <= t; p++) {
        if (is_prime(p)) {
            product *= (p - 1.0L) / p;
        }
    }
    return log(t) * product;
}

long double bisection_method_gamma(int32_t t, long double epsilon, long double a, long double b,
                             long double (*func)(const long double, const long double)) {


    long double product = compute_product(t);
    if (func(a, product) * func(b, product) > 0) {
        return NAN;
    }
    long double mid, f_mid;
    while ((b - a) / 2.0 >= epsilon) {
        mid = (a + b) / 2;

        f_mid = func(mid, product);
        if (my_abs(f_mid) == 0) {
            return mid;
        }
        if (func(a, product) * f_mid < 0) {
            b = mid;
        }
        else {
            a = mid;
        }
    }
    return (a + b) / 2;
}

long double get_gamma_from_equation(int32_t t, const long double epsilon) {
    return bisection_method_gamma(t, epsilon, 0, 1, func_gamma);

}
