#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>
#include <stdint.h>

#define UNNATURAL_NUMBER 1
#define TOO_BIG_NUMBER 2
#define ALLOCATE_ERROR 3

void generate_primes();

int32_t find_nth_prime(const int32_t n);

void clear_prime_cache();

#endif // FUNCTIONS_H
