#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "functions.h"


int32_t get_max_num(char* buff, const int32_t base) {
    int32_t max = 0;
    while (fgets(buff, BUFFER_SIZE, stdin)) {
        const size_t len = strlen(buff);
        if (buff[len - 1] == '\n') {
            buff[len - 1] = 0;
        }
        if (strcmp(buff, "STOP") == 0) {
            break;
        }
        const int32_t num = string_to_int(buff, base);
        if (num > max) {
            max = num;
        }
    }
    return max;
}

char* get_needed_systems(const int32_t max, char* res) {
    size_t pos = 0;
    char buff[BUFFER_SIZE];
    char* p = buff + BUFFER_SIZE - 1;
    *p-- = 0;
    pos += snprintf(res + pos, BUFFER_SIZE, "%s ", int_to_string(max, 9, p));
    pos += snprintf(res + pos, BUFFER_SIZE, "%s ", int_to_string(max, 18, p));
    pos += snprintf(res + pos, BUFFER_SIZE, "%s ", int_to_string(max, 27, p));
    pos += snprintf(res + pos, BUFFER_SIZE, "%s", int_to_string(max, 36, p));
    return res;
}

int32_t string_to_int(const char *str, const int32_t base) {
    int32_t result = 0;
    while (*str) {
        result = result * base + (isdigit(*str) ? *str++ - '0' : *str++ - 'a' + 10);
    }
    return result;
}

char* int_to_string(int32_t number, const int32_t base, char* res) {
    int32_t rem;
    while (number) {
        rem = number % base;
        *res-- = rem > 9 ? rem + 'a' - 10 : rem + '0';
        number /= base;
    }
    return res + 1;
}
