#include <ctype.h>

#include "functions.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>


char* choose_string(const char* p, char* res) {
    *res = 0; // изначально результат пустой
    char pch = 0, ch;
    char str[BUFFER_SIZE];
    size_t pos = 0, shift = 0;
    while (*p || pos > 0) {
        ch = *p++;
        if (isalnum(ch)) {
            str[pos++] = ch;
        }
        if (isalnum(pch) && !isalnum(ch)) {
            str[pos] = 0;
            const int32_t min_base = get_base_number(str);
            const int32_t dec = string_to_int(str, min_base);
            shift += snprintf(res + shift, BUFFER_SIZE, "%s %d %d\n", str, min_base, dec);
            pos = 0;
        }
        pch = ch;
    }
    return res;
}

int32_t get_base_number(const char* str) {
    const size_t len = strlen(str);
    char max_letter = 0;
    for (size_t i = 0; i < len; ++i) {
        if (str[i] > max_letter) {
            max_letter = str[i];
        }
    }
    if (isalpha(max_letter)) {
        return tolower(max_letter) - 'a' + 11;
    }
    return max_letter - '0' + 1;
}

int32_t string_to_int(const char* str, const int32_t base) {
    if (base < 2 || base > 36) {
        return -1;
    }
    int32_t res = 0;
    while (*str) {
        if (isalpha(*str)) {
            res = res * base + (tolower(*str++) - 'a' + 10);
        } else {
            res = res * base + (*str++ - '0');
        }
    }
    return res;
}
