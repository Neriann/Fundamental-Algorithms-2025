#include <stdio.h>
#include <stdlib.h>

#include "primes/functions.h"


void solve(const PrimeNumbers* primes) {
    int32_t n;
    scanf("%d", &n);

    PrimeNthNumber res = find_nth_prime(n, primes);
    if (res.code == UNNATURAL_NUMBER) {
        printf("The number %d isn't natural\n", n);
    } else if (res.code == TOO_BIG_NUMBER) {
        printf("The number %d is too big\n", n);
    }else if (res.code == ALLOCATE_ERROR) {
        printf("The allocated memory isn't allocated\n");
    } else {
        printf("%d\n", res.value);
    }
}

int main() {
    int32_t t;
    scanf("%d", &t);
    PrimeNumbers prime_numbers = {NULL, 0};
    Code code = generate_primes(&prime_numbers);
    if (code != SUCCESS) {
        return 1;
    }
    while (t--) {
        solve(&prime_numbers);
    }
    free(prime_numbers.values);
    return 0;
}
