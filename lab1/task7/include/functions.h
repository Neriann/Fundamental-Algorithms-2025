#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define BUFFER_SIZE 1024

#include <stdint.h>

char* validate_num(const char* buff, char* res);

char* choose_string(const char* buff, char* res);

int32_t get_base_number(const char* str);

int32_t string_to_int(const char* str, const int32_t base);

#endif //FUNCTIONS_H
