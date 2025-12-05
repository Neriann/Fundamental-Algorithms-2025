#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "functions.h"


Code string_to_int(int64_t* result, const char* str, int64_t base) {
    if (!result || base != 10)
        return INVALID_ARGS;

    int8_t mul = 1;
    if (*str == '-') {
        mul = -1;
        ++str;
    }
    int64_t res = 0;
    while (*str) {
        int tmp = (isdigit(*str) ? *str++ - '0' : *str++ - 'A' + 10);
        if (res > INT64_MAX / base - tmp) {
            return OVERFLOW_NUMBER;
        }
        res = res * base + tmp;
    }
    *result = mul * res;
    return SUCCESS;
}

Code int_to_string(int64_t num, int64_t base, char** res, char* p) {
    if (!p || base < 2 || base > 36) return INVALID_ARGS;
    *p = 0;
    if (num == 0) {
        *--p = '0';
        *res = p;
        return SUCCESS;
    }
    int64_t n = num;
    while (n) {
        int64_t rem = n % base;
        if (rem < 0) rem = labs(rem);
        *(--p) = (rem > 9) ? ('A' + rem - 10) : ('0' + rem);
        n /= base;
    }
    if (num < 0) {
        *--p = '-';
    }
    *res = p;
    return SUCCESS;
}

Code is_number(const char* str) {
    if (!str || !*str) return NOT_NUMBER;

    if (*str == '-') ++str;

    for (; *str; ++str) {
        if (!isdigit(*str)) return NOT_NUMBER;
    }
    return SUCCESS;
}

Code get_hex_num(const char* num, char** res, char* buff) {
    if (!num || !*num) return INVALID_ARGS;

    int64_t dec;
    Code code = string_to_int(&dec, num, 10);
    if (code != SUCCESS) return code;

    char* p;
    code = int_to_string(dec, 16, &p, buff);
    if (code != SUCCESS) return code;

    *res = p;
    return SUCCESS;
}

Code get_divisible_numbers(int64_t** res, size_t* res_size, int64_t num) {
    num = labs(num);
    if (num > 100) return INVALID_ARGS;
    size_t sz = 100 / num;
    int64_t* numbers = malloc(sizeof(int64_t) * sz);
    if (!numbers) return ALLOCATE_ERROR;
    int64_t* p = numbers;
    for (int64_t divisible = num; divisible <= 100; divisible += num) {
        *p++ = divisible;
    }
    *res = numbers;
    *res_size = sz;
    return SUCCESS;
}


Code is_prime(int64_t num) {
    if (num <= 0) return UNNATURAL_NUMBER;
    if (num == 1) return SPECIFIC_NUMBER;
    if (num == 2) return PRIME_NUMBER;
    if (num % 2 == 0) return COMPOSITE_NUMBER;
    for (int64_t divider = 3; divider * divider <= num; divider += 2) {
        if (num % divider == 0) return COMPOSITE_NUMBER;
    }
    return PRIME_NUMBER;
}

void print_powers_table(int64_t num) {
    if (num < 1) {
        printf("The minimum table size is 1\n");
        return;
    }
    if (num > 10) {
        printf("The maximum table size is 10\n");
        return;
    }
    int64_t max_num = 1;
    for (int64_t n = 1; n <= num; ++n) max_num *= num;

    int32_t col_width = 0;
    while (max_num) {
        ++col_width;
        max_num /= 10;
    }

    printf("%*s |", col_width, "n");
    for (int32_t pow = 1; pow <= num; ++pow) {
        printf("%*d", col_width + 1, pow);
    }
    printf("\n%*s-+", col_width, "-");
    for (int32_t i = 0; i < num; ++i) {
        for (int32_t j = 0; j <= col_width; ++j) printf("-");
    }
    printf("\n");
    for (int32_t base = 1; base <= num; ++base) {
        int64_t curr_num = 1;
        printf("%*d |", col_width, base);
        for (int32_t pow = 1; pow <= num; ++pow) {
            curr_num *= base;
            printf("%*ld", col_width + 1, curr_num);
        }
        printf("\n");
    }
}



Code get_sum(int64_t* sum, int64_t num) {
    if (num < 0)
        return NEGATIVE_NUMBER;
    if (!num)
        return ZERO_NUMBER;

    int64_t res = 0;
    for (int64_t i = 1; i <= num; ++i) {
        if (num > INT64_MAX / i) return OVERFLOW_NUMBER;

        res += i;
    }
    *sum = res;
    return SUCCESS;
}

Code get_fact(int64_t* fact, int64_t num) {
    if (num < 0) return NEGATIVE_NUMBER;

    int64_t res = 1;
    for (int64_t i = 2; i <= num; ++i) {
        if (res > INT64_MAX / i) {
            return OVERFLOW_NUMBER;
        }
        res *= i;
    }
    *fact = res;
    return SUCCESS;
}
