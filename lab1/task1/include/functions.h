#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>


typedef enum {
    SPECIFIC_NUMBER = 0,
    PRIME_NUMBER,
    COMPOSITE_NUMBER
} NumberType;


int64_t string_to_int(const char* p, const int64_t base); // из с/с base в десятичную

char* int_to_string(const int64_t num, const int64_t base, char* res_end); // из десятичной в заданную с/с

int64_t divide_by_digit(const char* num, char divider, char* res);

char* decimal_to_base(const char* num, uint32_t base, char* res);

char** get_divisible_by_base_digits(const char* num, uint32_t base);

int64_t* get_divisible_numbers(const int64_t num);

NumberType is_prime(const int64_t num);

void print_powers_table(const int64_t num);

void add(const char* a, const char* b, char* res);

void mul_one_digit(const char* a, int8_t digit, char* res);

void multiply(const char* a, const char* b, char* res);

char* get_sum(const char* num);

char* get_fact(const int64_t num);

int main();

#endif // FUNCTIONS_H
