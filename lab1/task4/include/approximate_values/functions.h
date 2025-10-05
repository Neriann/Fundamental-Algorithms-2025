#ifndef TASK4_FUNCTIONS_H
#define TASK4_FUNCTIONS_H

#include <stdint.h>

long double bin_pow(long double a, int64_t b);

long double my_abs(const long double a);

long double bisection_method(long double epsilon, long double a, long double b, long double (*func)(const long double));

long double bisection_method_gamma(int32_t t, long double epsilon, long double a, long double b,
                             long double (*func)(const long double, const long double));

int64_t get_fact(const int64_t n);

long double get_exponent_from_limit(const long double epsilon);

long double get_exponent_from_row(const long double epsilon);

long double func_exp(const long double x);

long double get_exponent_from_equation(const long double epsilon);

long double func_pi(const long double x);

long double get_pi_from_limit(const long double epsilon);

long double get_pi_from_row(const long double epsilon);

long double get_pi_from_equation(const long double epsilon);

long double get_ln2_from_limit(const long double epsilon);

long double get_ln2_from_row(const long double epsilon);

long double func_ln2(const long double x);

long double get_ln2_from_equation();

long double get_sqrt2_from_limit(const long double epsilon);

long double get_sqrt2_from_row(const long double epsilon);

long double func_sqrt2(const long double x);

long double get_sqrt2_from_equation();

long double get_gamma_from_limit(const long double epsilon);

long double get_gamma_from_row(const long double epsilon);

long double func_gamma(const long double x, const long double lim);

uint8_t is_prime(int32_t n);

long double compute_product(int32_t n);

long double get_gamma_from_equation(int32_t t, const long double epsilon);

#endif //TASK4_FUNCTIONS_H
