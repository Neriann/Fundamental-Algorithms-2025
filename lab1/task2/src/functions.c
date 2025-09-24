#include "functions.h"

#include <stdlib.h>

const int32_t N = 1e8;

static int32_t* prime_numbers = NULL;
static int32_t prime_numbers_size = 0;

// вмещает примерно 5e6 простых чисел
void generate_primes() {
    if (prime_numbers) {
        return;
    }
    bool* is_composite = calloc(N + 1, sizeof(bool));
    if (!is_composite) {
        return;
    }
    for (int32_t i = 2; 1LL * i * i <= N; ++i) {
        if (!is_composite[i]) {
            for (int32_t j = i * i; j <= N; j += i) {
                is_composite[j] = 1;
            }
        }
    }
    int32_t prime_count = 0;
    for (int32_t i = 2; i <= N; ++i) {
        if (!is_composite[i]) {
            ++prime_count;
        }
    }
    prime_numbers_size = prime_count;
    prime_numbers = malloc(prime_numbers_size * sizeof(int32_t));
    if (!prime_numbers) {
        free(is_composite);
        is_composite = NULL;
        return;
    }
    size_t id = 0;
    for (int32_t num = 2; num <= N; ++num) {
        if (!is_composite[num]) {
            prime_numbers[id++] = num;
        }
    }
    free(is_composite);
}

int32_t find_nth_prime(const int32_t n) {
    if (n <= 0) {
        return UNNATURAL_NUMBER;
    }
    generate_primes();
    if (n >= prime_numbers_size) {
        return TOO_BIG_NUMBER;
    }
    if (!prime_numbers) {
        return ALLOCATE_ERROR;
    }
    return prime_numbers[n - 1];
}

void clear_prime_cache() {
    free(prime_numbers);
    prime_numbers = NULL;
}
