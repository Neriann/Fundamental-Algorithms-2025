#include "functions.h"

#include <stdbool.h>
#include <stdlib.h>

#define N 1e8


// вмещает примерно 5e6 простых чисел
Code generate_primes(PrimeNumbers* primes) {
    bool* is_composite = calloc(N + 1, sizeof(bool));
    if (!is_composite) {
        return ALLOCATE_ERROR;
    }
    for (int32_t i = 2; 1LL * i * i <= N; ++i) {
        if (!is_composite[i]) {
            for (int32_t j = i * i; j <= N; j += i) {
                is_composite[j] = 1;
            }
        }
    }
    size_t primes_size = 0;
    for (int32_t i = 2; i <= N; ++i) {
        if (!is_composite[i]) {
            ++primes_size;
        }
    }
    primes->size = primes_size;
    primes->values = malloc(primes->size * sizeof(int32_t));
    if (!primes->values) {
        free(is_composite);
        is_composite = NULL;
        return ALLOCATE_ERROR;
    }
    size_t id = 0;
    for (int32_t num = 2; num <= N; ++num) {
        if (!is_composite[num]) {
            primes->values[id++] = num;
        }
    }
    free(is_composite);
    return SUCCESS;
}

PrimeNthNumber find_nth_prime(const int32_t n, const PrimeNumbers* primes) {
    PrimeNthNumber solution = {SUCCESS, 0};
    if (n <= 0) {
        solution.code = UNNATURAL_NUMBER;
        return solution;
    }
    if (n >= primes->size) {
        solution.code = TOO_BIG_NUMBER;
        return solution;
    }
    solution.value = primes->values[n - 1];
    return solution;
}
