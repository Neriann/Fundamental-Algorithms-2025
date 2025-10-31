#include <stdio.h>

#include "functions.h"


int main() {
    int64_t num, base;
    printf("<Enter a number and base system>:\n");
    scanf("%ld %ld", &num, &base);

    char buff[64];
    char* result = NULL;
    size_t result_size;
    Code code = to_power_of_two_system(&result, &result_size, buff, sizeof(buff), num, base);
    switch (code) {
    case SUCCESS:
        printf("%s\n", result);
        break;
    case INVALID_ARG:
        printf("INVALID_ARG\n");
        return 1;
    case OUT_OF_RANGE:
        printf("OUT_OF_RANGE\n");
        return 1;

    case INVALID_BASE:
        printf("NO_POWER_TWO\n");
        return 1;

    default: ;
    }
    return 0;
}
