#include <stdio.h>
#include <stdlib.h>

#include "functions.h"


void solve() {
    int32_t n;
    scanf("%d", &n);

    int32_t res = find_nth_prime(n);
    if (res == UNNATURAL_NUMBER) {
        printf("The number %d isn't natural\n", n);
    } else if (res == TOO_BIG_NUMBER) {
        printf("The number %d is too big\n", n);
    }else if (res == ALLOCATE_ERROR) {
        printf("The allocated memory isn't allocated\n");
    } else {
        printf("%d\n", res);
    }
}

int main() {
    int32_t t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    clear_prime_cache();
    return 0;
}
