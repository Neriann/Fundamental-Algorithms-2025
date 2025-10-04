#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "functions.h"

#include <limits.h>


int32_t my_abs(const int32_t x) {
    return x < 0 ? -x : x;
}

int32_t get_max_num(char* buff, const int32_t base) {
    int32_t max = INT_MIN;
    while (fgets(buff, BUFFER_SIZE, stdin)) {
        const size_t len = strlen(buff);
        if (buff[len - 1] == '\n') {
            buff[len - 1] = 0;
        }
        if (strcmp(buff, "STOP") == 0) {
            break;
        }
        const int32_t num = my_abs(string_to_int(buff, base));
        if (num > max) {
            max = num;
        }
    }
    return max;
}

char* get_needed_systems(const int32_t max, char* res) {
    size_t pos = 0;
    char buff[BUFFER_SIZE];
    pos += snprintf(res + pos, BUFFER_SIZE, "%s ", int_to_string(max, 9, buff + BUFFER_SIZE - 1));
    pos += snprintf(res + pos, BUFFER_SIZE, "%s ", int_to_string(max, 18, buff + BUFFER_SIZE - 1));
    pos += snprintf(res + pos, BUFFER_SIZE, "%s ", int_to_string(max, 27, buff + BUFFER_SIZE - 1));
    pos += snprintf(res + pos, BUFFER_SIZE, "%s", int_to_string(max, 36, buff + BUFFER_SIZE - 1));
    return res;
}

int32_t string_to_int(const char *str, const int32_t base) {
    int32_t result = 0, mul = 1;
    if (*str == '-') {
        mul = -1;
        ++str;
    }
    while (*str) {
        result = result * base + (isdigit(*str) ? *str++ - '0' : *str++ - 'a' + 10);
    }
    return mul * result;
}

char* int_to_string(const int32_t number, const int32_t base, char* res) {
    *res-- = 0;
    int32_t n = my_abs(number), rem;
    if (n == 0) {
        *res = '0';
        return res;
    }
    while (n) {
        rem = n % base;
        *res-- = rem > 9 ? rem + 'a' - 10 : rem + '0';
        n /= base;
    }
    if (number < 0) {
        *res-- = '-';
    }
    return res + 1;
}
