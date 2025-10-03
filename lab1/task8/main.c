#include <stdio.h>
#include <string.h>

#include "functions.h"

int main() {
    int32_t base;
    scanf("%d", &base);
    if (base < 2 || base > 36) {
        printf("Invalid base value\n");
        return 1;
    }
    getchar();

    char buff[BUFFER_SIZE];
    const int32_t max = get_max_num(buff, base);

    char result[BUFFER_SIZE];
    get_needed_systems(max, result);

    printf("The number %d in 9, 18, 27, 36 numbers systems:\n", max);
    printf("%s\n", result);
}
