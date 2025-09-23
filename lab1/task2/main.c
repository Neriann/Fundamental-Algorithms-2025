#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

extern const int32_t N;

void solve() {
    int32_t n;
    scanf("%d", &n);

    int32_t res = find_nth_prime(n);
    if (res == UNNATURAL_NUMBER) {
        printf("The number %d isn't natural\n", n);
        return;
    }
    printf("%d\n", res);
}

int main() {
    int32_t t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
}
