#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define BUFFER_SIZE 1024

#include <stdint.h>

int32_t my_abs(const int32_t x);

int32_t get_max_num(char* buff, const int32_t base);

char* get_needed_systems(const int32_t max, char* res);

int32_t string_to_int(const char* str, const int32_t base);

char* int_to_string(const int32_t number, const int32_t base, char* res);

#endif //FUNCTIONS_H
