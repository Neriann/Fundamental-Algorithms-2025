#include <stdarg.h>

#include "functions.h"

#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef void (*func_in)(const void** const, char*, size_t);

int64_t roman_digit(char c) {
    switch (c) {
    case 'M':
        return 1000;
    case 'D':
        return 500;
    case 'C':
        return 100;
    case 'L':
        return 50;
    case 'X':
        return 10;
    case 'V':
        return 5;
    case 'I':
        return 1;
    default:
        return 0;
    }
}

Code roman_to_integer(int64_t* num, const char* s, size_t len) {
    if (!num || !s || !len)
        return INVALID_ARG;

    *num = 0;

    int8_t sign = 1;
    // учитываем отрицательные числа
    if (*s == '-') {
        sign = -1;
        ++s;
        --len;
    }
    if (!len) {
        return INVALID_ARG;
    }

    int64_t first, second, result = 0;
    // вычисляем римское число
    for (size_t i = 1; i < len; ++i) {
        first = roman_digit(s[i - 1]);
        second = roman_digit(s[i]);
        if (!first || !second) {
            return INVALID_ARG;
        }
        if (first < second) {
            result -= first;
        }
        else {
            result += first;
        }
    }
    first = roman_digit(s[len - 1]);
    if (!first) {
        return INVALID_ARG;
    }
    result += first;
    *num = sign * result;
    return SUCCESS;
}


Code fibonacci(uint64_t** fib, size_t n) {
    if (!fib || !n)
        return INVALID_ARG;

    if (!*fib) {
        // если память не выделена, делаем аллокацию
        *fib = (uint64_t*)malloc(sizeof(uint64_t) * n);
        if (!*fib)
            return MEM_ALLOC;
    }
    if (n == 1) {
        *fib[0] = 1;
        return SUCCESS;
    }
    (*fib)[0] = 1;
    (*fib)[1] = 2;
    for (size_t i = 2; i < n; ++i) {
        (*fib)[i] = (*fib)[i - 1] + (*fib)[i - 2];
    }
    return SUCCESS;
}

Code zeckendorf_to_integer(uint64_t* num, const char* s, size_t len) {
    if (!num || !s || !len)
        return INVALID_ARG;

    uint64_t* fib = NULL;
    // по умолчанию число равно 0
    *num = 0;

    // допустимые значения - {0, 1}
    for (size_t j = 0; j < len; ++j) {
        if (s[j] != '1' && s[j] != '0') {
            return INVALID_ARG;
        }
    }
    size_t terminator_pos = len;

    // ищем терминирующее повторение
    for (size_t i = 0; i + 1 < len; ++i) {
        // соседние элементы не должны быть равны 1
        if (s[i] == '1' && s[i + 1] == '1') {
            terminator_pos = i;
            break;
        }
    }
    // если повторение не в конце - ошибка
    if (terminator_pos != len - 2) {
        return INVALID_ARG;
    }
    Code code = fibonacci(&fib, terminator_pos + 1);
    if (code != SUCCESS) {
        return code;
    }
    // восстанавливаем исходное число
    for (size_t i = 0; i <= terminator_pos; ++i) {
        if (s[i] == '1') {
            *num += fib[i];
        }
    }
    free(fib);
    return SUCCESS;
}

// массив всех возможных флагов
Status flags[] = {
    {"d", INTEGER},
    {"ld", LONG_INTEGER},
    {"lld", LONGLONG_INTEGER},
    {"f", FLOAT},
    {"u", UNSIGNED_INTEGER},
    {"lu", LONG_UNSIGNED_INTEGER},
    {"llu", LONGLONG_UNSIGNED_INTEGER},
    {"lf", DOUBLE},
    {"Lf", LONG_DOUBLE},
    {"c", CHAR},
    {"s", STRING},
    {"Ro", ROMAN},
    {"Zr", ZECKENDORF},
    {"Cv", TO_LOWER_INTEGER_BASE},
    {"CV", TO_UPPER_INTEGER_BASE}
};


Code parse_params(const char* pos, size_t* bytes) {
    for (size_t i = 0; i < sizeof(flags) / sizeof(flags[0]); ++i) {
        // ищем корректный флаг
        if (strncmp(pos, flags[i].flag_name, strlen(flags[i].flag_name)) == 0) {
            *bytes = strlen(flags[i].flag_name);
            return flags[i].flag_value;
        }
    }
    *bytes = 0;
    return UNDEFINED_FLAG;
}


int overscanf_base(const void* some, func_in in, const char* format, va_list* args) {
    if (!some || !format || !args) {
        return INVALID_ARG;
    }
    int count = 0;
    while (*format) {
        if (*format == '%') {
            size_t bytes;
            Code code = parse_params(++format, &bytes);

            format += bytes;

            char buff[512];
            in(&some, buff, sizeof(buff));

            void* value = va_arg(*args, void*);
            switch (code) {
            case UNDEFINED_FLAG:
                return INVALID_ARG;

            case INTEGER:
            {
                *(int32_t*)value = (int32_t)strtol(buff, NULL, 10);
                break;
            }
            case LONG_INTEGER:
            case LONGLONG_INTEGER:
            {
                *(int64_t*)value = strtoll(buff, NULL, 10);
                break;
            }
            case UNSIGNED_INTEGER:
            {
                *(uint32_t*)value = (uint32_t)strtoul(buff, NULL, 10);
                break;
            }
            case LONG_UNSIGNED_INTEGER:
            case LONGLONG_UNSIGNED_INTEGER:
            {
                *(uint64_t*)value = strtoull(buff, NULL, 10);
                break;
            }
            case FLOAT:
            {
                *(float*)value = (float)strtof(buff, NULL);
                break;
            }
            case DOUBLE:
            {
                *(double*)value = (double)strtod(buff, NULL);
                break;
            }
            case LONG_DOUBLE:
            {
                *(long double*)value = strtold(buff, NULL);
                break;
            }
            case CHAR:
            {
                *(char*)value = *buff;
                break;
            }
            case STRING:
            {
                size_t len = strlen(buff);
                strncpy((char*)value, buff, len);
                ((char*)value)[len] = 0;
                break;
            }
            case ROMAN:
            {
                Code ans = roman_to_integer((int64_t*)value, buff, strlen(buff));
                if (ans != SUCCESS) {
                    return ans;
                }
                break;
            }
            case ZECKENDORF:
            {
                Code ans = zeckendorf_to_integer((uint64_t*)value, buff, strlen(buff));
                if (ans != SUCCESS) {
                    return ans;
                }
                break;
            }
            case TO_LOWER_INTEGER_BASE:
            case TO_UPPER_INTEGER_BASE:
            {
                bool is_lower = code == TO_LOWER_INTEGER_BASE ? 1 : 0;
                for (size_t i = 0; i < strlen(buff); ++i) {
                    if (!is_lower && islower(buff[i]) || is_lower && isupper(buff[i])) {
                        *(int64_t*)value = 0;
                        return INVALID_CASE;
                    }
                }
                int64_t base = va_arg(*args, int64_t);
                if (base < 2 || base > 36) {
                    base = 10;
                }
                *(int64_t*)value = strtol(buff, NULL, base);
                break;
            }
            default:
                break;
            }
            if (*buff) ++count;
        }
        else {
            ++format;
        }
    }
    return count;
}

void read_from_file(const void** const in, char* res, size_t n) {
    if (!in || !*in || !res || !n)
        return;

    FILE* f = (FILE*)*in;

    char ch;
    // проверка на ведущие разделяющие символы
    while ((ch = (char)fgetc(f)) != EOF && (ch == '\n' || ch == ' ' || ch == '\t')) {}

    // так как один символ уже вытащили используем do-while
    size_t i = 0;
    do {
        if (ch == '\n' || ch == ' ' || ch == '\t') {
            break;
        }
        res[i++] = ch;
    } while (i < n - 1 && (ch = (char)fgetc(f)) != EOF);
    res[i] = 0;
}

void read_from_buff(const void** const in, char* res, size_t n) {
    if (!in || !*in || !res || !n)
        return;

    char** str = (char**)in;
    // проверка на ведущие разделяющие символы
    while (**str && (**str == '\n' || **str == ' ' || **str == '\t')) *(*str)++;

    size_t i = 0;
    while (i++ < n - 1 && **str) {
        if (**str == '\n' || **str == ' ' || **str == '\t') {
            *(*str)++;
            break;
        }
        *res++ = *(*str)++;
    }
    *res = 0;
}

int overfscanf(FILE* stream, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result = overscanf_base(stream, read_from_file, format, &args);
    va_end(args);
    return result;
}

int oversscanf(char* buff, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result = overscanf_base(buff, read_from_buff, format, &args);
    va_end(args);
    return result;
}
