#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

int main() {
    int32_t count;
    int32_t base;
    scanf("%d %d", &count, &base);

    double real1, real2, real3, real4 = 1.0/3.0; // типо count = 3
    scanf("%lf %lf %lf", &real1, &real2, &real3);

    // ...
    if (count <= 0) {
        printf("Count must be greater than 0\n");
        return 1;
    }
    Solution* result = (Solution*)malloc(count * sizeof(Solution));
    if (!result) {
        printf("Memory allocation failed\n");
        return 1;
    }
    Code code = is_final_value(result, base, count, real4, real2, real3, real1 /* ... */);
    if (code == INVALID_ARG) {
        printf("Invalid argument\n");
        return 1;
    }
    const Solution* p = result;
    for (int i = 0; i < count; ++i) {
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
