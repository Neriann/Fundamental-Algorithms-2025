#include "functions.h"

#include <stdlib.h>

const int32_t N = 1e8;

// вмещает примерно 5e6 простых чисел
bool* get_prime_numbers() {
    bool* is_composite = calloc(N + 1, sizeof(bool));
    for (int32_t i = 2; 1LL * i * i <= N; ++i) {
        if (!is_composite[i]) {
            for (int32_t j = i * i; j <= N; j += i) {
                is_composite[j] = 1;
            }
        }
    }
    return is_composite;
}

int32_t find_nth_prime(const int32_t n) {
    if (n <= 0) {
        return UNNATURAL_NUMBER;
    }
    bool* is_composite = get_prime_numbers();
    int32_t counter = 0, num = 2;
    for (;num <= N; ++num) {
        if (!is_composite[num]) {
            if (++counter == n) break;
        }
    }
    free(is_composite);
    return num;
}
