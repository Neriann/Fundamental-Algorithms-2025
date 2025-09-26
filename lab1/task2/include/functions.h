#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stddef.h>
#include <stdint.h>


typedef enum {
  UNNATURAL_NUMBER = 0,
  TOO_BIG_NUMBER,
  ALLOCATE_ERROR,
  SUCCESS
} Code;

typedef struct {
  int32_t* values;
  size_t size;
} PrimeNumbers;

typedef struct {
  Code code;
  int32_t value;
} PrimeNthNumber;

Code generate_primes(PrimeNumbers* primes);

PrimeNthNumber find_nth_prime(const int32_t n, const PrimeNumbers* primes);

void clear_prime_cache();

#endif // FUNCTIONS_H
