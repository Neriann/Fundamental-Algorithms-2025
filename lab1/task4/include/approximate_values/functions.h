#ifndef TASK4_FUNCTIONS_H
#define TASK4_FUNCTIONS_H

#include <stdint.h>
#include "primes/functions.h"

long double bin_pow(long double a, int64_t b);

long double my_abs(const long double a);

long double get_fact(const long double n);

long double get_exponent_from_limit(const long double epsilon);

long double get_exponent_from_row(const long double epsilon);

long double get_exponent_from_equation();

long double get_pi_from_limit(const long double epsilon);

long double get_pi_from_row(const long double epsilon);

long double get_pi_from_equation();

long double get_ln2_from_limit(const long double epsilon);

long double get_ln2_from_row(const long double epsilon);

long double get_ln2_from_equation();

long double get_sqrt2_from_limit(const long double epsilon);

long double get_sqrt2_from_row(const long double epsilon);

long double get_sqrt2_from_equation();

long double get_gamma_from_limit(const long double epsilon);

long double get_gamma_from_row(const long double epsilon);

long double get_gamma_from_equation(const long double epsilon, const PrimeNumbers* primes);

#endif //TASK4_FUNCTIONS_H
