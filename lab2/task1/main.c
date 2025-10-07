#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

int main() {
    int32_t count = 6;
    double real = 0.125;
    int32_t base = 4;
    // ...
    if (count <= 0) {
        printf("Count must be greater than 0\n");
        return 1;
    }
    if (count % 2 != 0) {
        printf("Count must be even\n");
        return 1;
    }
    Solution* result = (Solution*)malloc(count / 2 * sizeof(Solution));
    if (!result) {
        printf("Memory allocation failed\n");
        return 1;
    }
    Code code = is_final_value(result, count, real, base, real, 15, real, 20 /* ... */);
    if (code == INVALID_ARG) {
        printf("Invalid argument\n");
        return 1;
    }
    const Solution* p = result;
    for (int i = 0; i < count / 2; ++i) {
        if (p->code == SUCCESS) {
            printf("The number %lf is finite in %d integer system\n", p->real, p->base);
        } else if (p->code == FAILURE) {
            printf("The number %lf is not finite in %d integer system\n", p->real, p->base);
        } else {
            printf("The number %lf and base %d - invalid argument\n", p->real, p->base);
        }
        ++p;
    }
    free(result);
    return 0;
}
