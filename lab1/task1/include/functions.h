#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_SIZE 1025 // 1KB + \0


#include <stdint.h>
typedef enum {
    SUCCESS = 0,
    UNNATURAL_NUMBER,
    SPECIFIC_NUMBER,
    PRIME_NUMBER,
    COMPOSITE_NUMBER,
    OVERFLOW_NUMBER,
    NEGATIVE_NUMBER,
    ZERO_NUMBER,
    NOT_NUMBER,
    INVALID_ARGS,
    ALLOCATE_ERROR
} Code;


Code string_to_int(int64_t* result, const char* p, int64_t base); // из с/с base в десятичную

Code int_to_string(int64_t num, int64_t base, char** res, char* p); // из десятичной в заданную с/с

Code is_number(const char* p);

Code get_hex_num(const char* num, char** res, char* buff);

Code get_divisible_numbers(int64_t** res, size_t* res_size, int64_t num);

Code is_prime(int64_t num);

void print_powers_table(int64_t num);

Code get_sum(int64_t* sum, int64_t num);

Code get_fact(int64_t* fact, int64_t num);

#endif // FUNCTIONS_H
