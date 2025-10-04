#include <ctype.h>

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "functions.h"

char* validate_num(const char* buff, char* res) {
    char* p = res;
    if (*buff == '-') {
        *res++ = '-';
        *buff++;
    }
    while (*buff == '0') {
        *buff++;
    }
    if (!*buff) {
        *res++ = '0';
    } else {
        while (*buff) {
            *res++ = *buff++;
        }
    }
    *res = 0;
    if (strcmp(p, "-0") == 0) {
        ++p;
    }
    return p;
}

char* choose_string(const char* p, char* res) {
    *res = 0; // изначально результат пустой
    char pch = 0, ch;
    char str[BUFFER_SIZE];
    size_t pos = 0, shift = 0;
    while (*p || pos > 0) {
        ch = *p++;
        if (isalnum(ch)) {
            if (pch == '-') str[pos++] = pch;
            str[pos++] = ch;
        }
        if (isalnum(pch) && !isalnum(ch)) {
            str[pos] = 0;
            char tmp[BUFFER_SIZE];
            const char* valid_num = validate_num(str, tmp);
            const int32_t min_base = get_base_number(valid_num);
            const int32_t dec = string_to_int(valid_num, min_base);
            shift += snprintf(res + shift, BUFFER_SIZE, "%s %d %d\n", valid_num, min_base, dec);
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
    } else if (max_letter == '0') {
        return 2;
    }
    return max_letter - '0' + 1;
}

int32_t string_to_int(const char* str, const int32_t base) {
    if (base < 2 || base > 36) {
        return -1;
    }
    int8_t mul = 1;
    if (*str == '-') {
        ++str;
        mul = -1;
    }
    int32_t res = 0;
    while (*str) {
        if (isalpha(*str)) {
            res = res * base + (tolower(*str++) - 'a' + 10);
        }
        else {
            res = res * base + (*str++ - '0');
        }
    }
    return mul * res;
}
