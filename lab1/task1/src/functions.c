#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "functions.h"

#define MAX_SIZE 1025 // 1KB + \0

int64_t string_to_int(const char* str, const int64_t base) {
    if (base < 2 || base > 36)
        return 0;

    int8_t mul = 1;
    if (*str == '-') {
        mul = -1;
        ++str;
    }
    int64_t res = 0;
    while (*str) {
        res = res * base + (isdigit(*str) ? *str++ - '0' : *str++ - 'A' + 10);
    }
    return mul * res;
}

char* int_to_string(const int64_t num, const int64_t base, char* res_end) {
    if (base < 2 || base > 36) return NULL;
    char* p = res_end;
    *p = '\0';
    if (num == 0) {
        *(--p) = '0';
        return p;
    }
    int64_t n = num;
    while (n) {
        int64_t rem = n % base;
        *(--p) = (rem > 9) ? ('A' + rem - 10) : ('0' + rem);
        n /= base;
    }
    return p;
}

int64_t divide_by_digit(const char* num, char divider, char* res) {
    if (!num || !*num) return 0;
    size_t len_a = strlen(num);
    int64_t current = 0;
    size_t j = 0;
    int64_t div = isdigit((unsigned char)divider) ? divider - '0' : divider - 'A' + 10;

    if (!div) {
        if (res) strcpy(res, "inf");
        return 0;
    }

    uint8_t found_first = 0;
    for (size_t i = 0; i < len_a; ++i) {
        current = 10 * current + (num[i] - '0');
        if (current >= div) {
            found_first = 1;
        }
        if (found_first) {
            if (res) res[j++] = '0' + current / div;
            current %= div;
        }
    }
    if (res) res[j] = 0;
    return current;
}

char* decimal_to_base(const char* num, uint32_t base, char* res) {
    if (base < 2 || base > 36) return NULL;
    size_t len = strlen(num);

    char tmp[MAX_SIZE];
    strcpy(tmp, num);

    char* p = res + MAX_SIZE - 1;
    *p-- = 0;
    int64_t remainder = 0;
    char div = base > 9 ? 'A' + base - 10 : '0' + base;
    for (size_t i = 0; i < len; ++i) {
        remainder = divide_by_digit(tmp, div, NULL);
        *p-- = (remainder > 9) ? ('A' + remainder - 10) : ('0' + remainder);
        divide_by_digit(tmp, div, tmp);
    }
    return p + 1;
}

char** get_divisible_by_base_digits(const char* num, const uint32_t base) {
    char tmp[MAX_SIZE];
    char* hex = decimal_to_base(num, base, tmp);
    if (!hex) return NULL;

    size_t len_num = strlen(num);
    size_t len_hex = strlen(hex);

    char** answer = malloc(sizeof(char*) * (len_hex + 1));
    if (!answer) return NULL;
    answer[len_hex] = NULL;

    for (size_t i = 0; i < len_hex; ++i) {
        answer[i] = malloc(len_num + 1);
        if (!answer[i]) {
            for (size_t k = 0; k < i; ++k) free(answer[k]);
            free(answer);
            return NULL;
        }
        answer[i][0] = '0'; answer[i][1] = 0;
        divide_by_digit(num, hex[i], answer[i]);
    }
    return answer;
}

int64_t* get_divisible_numbers(const int64_t num) {
    if (num >= 100 || num <= 0) return NULL;
    size_t sz = 100 / num;
    int64_t* numbers = malloc(sizeof(int64_t) * (sz + 1));
    if (!numbers) return NULL;
    int64_t* p = numbers;
    for (int64_t divisible = num; divisible <= 100; divisible += num) {
        *p++ = divisible;
    }
    *p = 0;
    return numbers;
}


NumberType is_prime(const int64_t num) {
    if (num <= 0) return UNNATURAL_NUMBER;
    if (num == 1) return SPECIFIC_NUMBER;
    if (num == 2) return PRIME_NUMBER;
    if (num % 2 == 0) return COMPOSITE_NUMBER;
    for (int64_t divider = 3; divider * divider <= num; divider += 2) {
        if (num % divider == 0) return COMPOSITE_NUMBER;
    }
    return PRIME_NUMBER;
}

void print_powers_table(const int64_t num) {
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

void add(const char* a, const char* b, char* res) {
    size_t len_a = strlen(a), len_b = strlen(b);

    const char* ptr_a = len_a ? a + len_a - 1 : NULL;
    const char* ptr_b = len_b ? b + len_b - 1 : NULL;

    char* ptr_res = res + MAX_SIZE - 1;
    *ptr_res-- = 0;

    uint8_t remainder = 0, sum_digits, current_digit_a, current_digit_b;
    while ((ptr_a && ptr_a >= a) || (ptr_b && ptr_b >= b) || remainder) {
        current_digit_a = (ptr_a && ptr_a >= a) ? *ptr_a-- - '0' : 0;
        current_digit_b = (ptr_b && ptr_b >= b) ? *ptr_b-- - '0' : 0;
        sum_digits = current_digit_a + current_digit_b + remainder;

        remainder = sum_digits / 10;
        sum_digits %= 10;

        *ptr_res-- = sum_digits + '0';
    }
    size_t len_sum = (res + MAX_SIZE) - (ptr_res + 1);
    memmove(res, ptr_res + 1, len_sum);
}

void mul_one_digit(const char* a, int8_t digit, char* res) {
    size_t n = strlen(a);
    res[n] = 0;
    int64_t remainder = 0;
    for (int64_t i = n - 1; i >= 0; --i) {
        int64_t prod = (a[i] - '0') * digit + remainder;
        remainder = prod / 10;
        res[i] = (prod % 10) + '0';
    }
    if (remainder) {
        memmove(res + 1, res, n + 1);
        res[0] = '0' + remainder;
    }
}

void multiply(const char* a, const char* b, char* res) {
    res[0] = '0'; res[1] = '\0'; // инициализация
    size_t len_b = strlen(b);
    char part[MAX_SIZE], tmp[MAX_SIZE];

    for (int64_t i = len_b - 1, shift = 0; i >= 0; --i, ++shift) {
        int8_t digit = b[i] - '0';
        if (digit == 0) continue;
        mul_one_digit(a, digit, part);
        int64_t len = strlen(part);
        for (int64_t j = 0; j < shift; ++j) part[len + j] = '0';
        part[len + shift] = 0;
        add(res, part, tmp);
        strcpy(res, tmp);
    }
    if (res[0] == '0') res[1] = 0; // если много нулей спереди то это возможно только при a = 0, поэтому явно указываем ответ 0
}



char* get_sum(const char* num) {
    char num_plus_one[MAX_SIZE], mul[MAX_SIZE], res[MAX_SIZE];
    add(num, "1", num_plus_one);
    multiply(num, num_plus_one, mul);
    divide_by_digit(mul, '2', res);
    char* ans = malloc(strlen(res) + 1);
    if (!ans) return NULL;
    strcpy(ans, res);
    return ans;
}

char* get_fact(const int64_t num) {
    char res[MAX_SIZE], buf[MAX_SIZE], tmp[MAX_SIZE];
    res[0] = '1'; res[1] = 0;

    for (int64_t i = 2; i <= num; ++i) {
        char* current = buf + MAX_SIZE - 1;
        *current = 0;
        current = int_to_string(i, 10, current);
        multiply(res, current, tmp);
        strcpy(res, tmp);
    }
    char* ans = malloc(strlen(res) + 1);
    if (!ans) return NULL;
    strcpy(ans, res);
    return ans;
}
