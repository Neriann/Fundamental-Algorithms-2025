#ifdef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int32_t string_to_int(char* p);

int32_t* get_divisible_numbers(int32_t num);

bool is_prime(int32_t num);

int64_t get_sum(int64_t num);

#endif // MAIN_H
