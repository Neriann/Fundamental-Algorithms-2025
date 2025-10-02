#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

#include "functions.h"


char* remove_arabic_digits(const char* buff, char* res) {
    size_t pos = 0;
    const char* p = buff;
    while (*p != 0) {
        if (!isdigit(*p)) {
            res[pos++] = *p;
        }
        ++p;
    }
    res[pos] = 0;
    return res;
}

char* count_latin_letters(const char* buff, char* res) {
    size_t pos = 0;
    int32_t cnt = 0;
    for (int i = 0; buff[i] != 0; ++i) {
        if (isalpha(buff[i])) {
            ++cnt;
        }
        if (buff[i] == '\n') {
            pos += snprintf(res + pos, BUFFER_SIZE, "%d\n", cnt);
            cnt = 0;
        }
    }
    res[pos] = 0;
    return res;
}

char* count_rare_symbols(const char* buff, char* res) {
    size_t pos = 0;
    int32_t cnt = 0;
    for (int i = 0; buff[i] != 0; ++i) {
        if (!isalnum(buff[i]) && !isspace(buff[i])) {
            ++cnt;
        }
        if (buff[i] == '\n') {
            pos += snprintf(res + pos, BUFFER_SIZE, "%d\n", cnt);
            cnt = 0;
        }
    }
    res[pos] = 0;
    return res;
}

char* replace_except_digits(const char* buff, char* res) {
    size_t pos = 0;
    for (int i = 0; buff[i] != 0; ++i) {
        /*if (buff[i] == '\n') {
            pos += snprintf(res + pos, BUFFER_SIZE, "%0x\n", buff[i]);
        } else */if (!isdigit(buff[i])) {
            pos += snprintf(res + pos, BUFFER_SIZE, "%0x", buff[i]);
        } else {
            res[pos++] = buff[i];
        }
    }
    res[pos] = 0;
    return res;
}
