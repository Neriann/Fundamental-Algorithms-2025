#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/main.h"

#define MAX_SIZE 1025 // - 1KB + last \0


int64_t string_to_int(const char* p) {
    int64_t res = 0;
    while (*p) {
        res = res * 10 + *p++ - '0';
    }
    return res;
}

char* int_to_string(const int64_t num, const int64_t base, char* res) {
    int64_t n = num, remainder = 0;
    while (n) {
        remainder = n % base;
        *res-- = remainder > 9 ? 'A' + remainder - 10 : '0' + remainder;
        n /= base;
    }
    return res + 1;
}

int64_t divide_by_digit(const char* num, char divider, char* res) {
    size_t len_a = strlen(num);
    int64_t current = 0;
    size_t j = 0;
    int64_t div = isdigit(divider) ? divider - '0' : divider - 'A' + 10;

    if (!div) {
        strcpy(res, "inf\0");
        return 0;
    }

    bool found_first = false;
    for (size_t i = 0; i < len_a; ++i) {
        current = 10 * current + num[i] - '0';
        if (current >= div) {
            found_first = true;
        }
        if (found_first) {
            if (res) res[j++] = '0' + current / div; // res - not NULL
            current %= div;
        }
    }
    if (res) res[j] = 0;
    return current; // remainder
}

char* decimal_to_base(const char* num, uint32_t base, char* res) {
    if (base < 2 || base > 36) return NULL; // проверка основания
    size_t len = strlen(num);

    char tmp[MAX_SIZE];
    strcpy(tmp, num);

    char* p = res + MAX_SIZE - 1;
    *p-- = 0;
    int64_t remainder = 0;
    char div = base > 9 ? 'A' + base - 10 : '0' + base;
    for (size_t i = 0; i < len; ++i) {
        remainder = divide_by_digit(tmp, div, NULL);
        *p = remainder > 9 ? 'A' + remainder - 10 : '0' + remainder;
        --p;
        divide_by_digit(tmp, div, tmp);
    }
    return p + 1;
}

char** get_divisible_by_base_digits(const char* num, uint32_t base) {
    char tmp[MAX_SIZE];
    char* hex = decimal_to_base(num, base, tmp); // the hex-num will be in the memory of the tmp pull
    size_t len_num = strlen(num);
    size_t len_hex = strlen(hex);

    char** answer = (char**)malloc(sizeof(char*) * (len_hex + 1));
    if (!answer) return NULL;
    answer[len_hex] = NULL;
    for (size_t i = 0; i < len_hex; ++i) {
        answer[i] = (char*)malloc(sizeof(char) * (len_num + 1));
        if (!answer[i]) return NULL;
        answer[i][0] = '0';
        answer[i][1] = 0;
        divide_by_digit(num, hex[i], answer[i]);
    }
    return answer;
}

int64_t* get_divisible_numbers(const int64_t num) {
    if (num >= 100 || num <= 0) {
        return NULL;
    }
    size_t sz = 100 / num;
    int64_t* numbers = (int64_t*)malloc(sizeof(int64_t) * (sz + 1));
    int64_t* p = numbers;
    for (int divisible = num; divisible <= 100; divisible += num) {
        *p++ = divisible;
    }
    *p = 0; // terminator
    return numbers;
}

#define SPECIFIC_NUMBER 0
#define PRIME_NUMBER 1
#define COMPOSITE_NUMBER 2


uint8_t is_prime(const int64_t num) {
    if (num < 2) {
        return SPECIFIC_NUMBER;
    }
    for (int divider = 2; divider * divider <= num; ++divider) {
        if (num % divider == 0) {
            return COMPOSITE_NUMBER;
        }
    }
    return PRIME_NUMBER;
}

void print_powers_table(const int64_t num) {
    if (num > 10) {
        printf("The maximum table size is 10\n");
        return;
    }
    int64_t max_num = 1;
    for (int64_t n = 1; n <= num; ++n) {
        max_num *= num;
    }
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
        for (int32_t j = 0; j <= col_width; ++j) {
            printf("-");
        }
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

size_t max(size_t a, size_t b) { return a > b ? a : b; }

void add(const char* a, const char* b, char* res) {
    size_t len_a = strlen(a), len_b = strlen(b);

    const char* ptr_a = a + len_a - 1;
    const char* ptr_b = b + len_b - 1;

    char* ptr_res = res + MAX_SIZE - 1;
    *ptr_res-- = 0;

    uint8_t remainder = 0, sum_digits, current_digit_a, current_digit_b;
    while (ptr_a >= a || ptr_b >= b || remainder) {
        current_digit_a = ptr_a >= a ? *ptr_a-- - '0' : 0;
        current_digit_b = ptr_b >= b ? *ptr_b-- - '0' : 0;
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
    size_t len_b = strlen(b);
    char part[MAX_SIZE], tmp[MAX_SIZE];

    // res[0] = '0';
    // res[1] = 0;
    for (int64_t i = len_b - 1, shift = 0; i >= 0; --i, ++shift) {
        int8_t digit = b[i] - '0';
        if (digit == 0) {
            continue;
        }
        mul_one_digit(a, digit, part);
        int64_t len = strlen(part);
        for (int64_t j = 0; j < shift; ++j) {
            part[len + j] = '0';
        }
        part[len + shift] = 0;
        add(res, part, tmp);
        strcpy(res, tmp);
    }
}

#define DIVISION_ERROR "1"
#define ALLOCATE_ERROR "2"

char* get_sum(const char* num) {
    char num_plus_one[MAX_SIZE], mul[MAX_SIZE], res[MAX_SIZE];
    add(num, "1\0", num_plus_one); // чтобы поддерживать числа, значение которых > LLONG_MAX
    mul[0] = '0'; mul[1] = 0;
    multiply(num, num_plus_one, mul);
    if (divide_by_digit(mul, '2', res)) {
        return DIVISION_ERROR;
    }
    char* ans = (char*)malloc(sizeof(char) * strlen(res) + 1); // с учетом \0
    if (!ans) {
        return ALLOCATE_ERROR;
    }
    strcpy(ans, res);
    return ans;
}

char* get_fact(const int64_t num) {
    char res[MAX_SIZE], buf[MAX_SIZE], tmp[MAX_SIZE];
    res[0] = '1'; res[1] = 0;

    char* current;
    for (int64_t i = 2; i <= num; ++i) {
        tmp[0] = '0'; tmp[1] = 0;
        current = buf + MAX_SIZE - 1;
        *current-- = 0;
        current = int_to_string(i, 10, current);
        multiply(res, current, tmp);
        strcpy(res, tmp);
    }
    size_t len = strlen(res);
    char* ans = (char*)malloc(sizeof(char) * (len + 1));
    strcpy(ans, res);
    return ans;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Not enough arguments\n");
        return 1;
    }
    const char* flag = argv[1];
    char* pointer_to_num = argv[2];
    if (strcmp(flag, "-h") == 0 || strcmp(flag, "/h") == 0) {
        const int64_t num = string_to_int(pointer_to_num);
        int64_t* numbers = get_divisible_numbers(num);
        if (numbers != NULL) {
            int64_t* p = numbers;
            while (*p) {
                printf("%ld ", *p++);
            }
            printf("\n");
            free(numbers);
        }
        else {
            printf("There are no numbers between 1 and 100 that are divisible by %ld\n", num);
        }
    }
    else if (strcmp(flag, "-p") == 0 || strcmp(flag, "/p") == 0) {
        const int64_t num = string_to_int(pointer_to_num);
        const uint8_t code = is_prime(num);
        if (code == PRIME_NUMBER) {
            printf("The number %ld is prime\n", num);
        }
        else if (code == COMPOSITE_NUMBER) {
            printf("The number %ld is composite\n", num);
        }
        else {
            printf("The number %ld is specific\n", num);
        }
    }
    else if (strcmp(flag, "-s") == 0 || strcmp(flag, "/s") == 0) {
        char** answer = get_divisible_by_base_digits(pointer_to_num, 16);
        for (size_t i = 0; answer[i] != NULL; ++i) {
            printf("%s ", answer[i]);
            free(answer[i]);
        }
        printf("\n");
        free(answer);
    }
    else if (strcmp(flag, "-e") == 0 || strcmp(flag, "/e") == 0) {
        const int64_t num = string_to_int(pointer_to_num);
        print_powers_table(num);
    }
    else if (strcmp(flag, "-a") == 0 || strcmp(flag, "/a") == 0) {
        char* answer = get_sum(pointer_to_num);
        if (answer == DIVISION_ERROR) {
            printf("Error when dividing a number\n");
            return 1;
        } else if (answer == ALLOCATE_ERROR) {
            printf("Memory allocation error\n");
            return 1;
        }
        printf("%s\n", answer);
        free(answer);
    }
    else if (strcmp(flag, "-f") == 0 || strcmp(flag, "/f") == 0) {
        const int64_t num = string_to_int(pointer_to_num);
        char* fact = get_fact(num);
        printf("%s\n", fact);
        free(fact);
    }
    return 0;
}
