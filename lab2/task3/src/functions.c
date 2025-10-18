#include <stdarg.h>

#include "functions.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>


// Из десятичной cистемы счисления в заданную

Code integer_to_string_basic(uint64_t num, bool is_signed, bool is_lower, int64_t base, char* buff, size_t buff_size) {
    if (!buff || buff_size == 0)
        return EMPTY_BUFF;

    if (base < 2 || base > 36) {
        base = 10;
    }
    bool negative = 0;
    if (is_signed && (int64_t)num < 0) {
        num = (uint64_t)(-(int64_t)num);
        negative = 1;
    }
    char* p = buff + buff_size - 1;
    *p = 0;
    if (num == 0) {
        if (buff_size < 2) return BUFF_OVERFLOW;
        buff[0] = '0';
        buff[1] = 0;
        return SUCCESS;
    }
    uint64_t n = num;
    char a = is_lower ? 'a' : 'A';
    while (n) {
        uint64_t rem = n % base;
        if (p - 1 < buff) return BUFF_OVERFLOW;
        *(--p) = (rem > 9) ? (char)(a + rem - 10) : (char)('0' + rem);
        n /= base;
    }
    if (negative) {
        if (p - 1 < buff) return BUFF_OVERFLOW;
        *--p = '-';
    }
    size_t len = strlen(p);
    // переносим результат в начало буфера
    if (p != buff) {
        memmove(buff, p, len);
        buff[len] = 0;
    }
    return SUCCESS;
}

Code integer_to_string(uint64_t num, bool is_signed, char* buff, size_t buff_size) {
    bool is_lower = 0;
    int64_t base = 10;
    return integer_to_string_basic(num, is_signed, is_lower, base, buff, buff_size);
}

Code integer_to_base_string(uint64_t num, bool is_lower, int64_t base, char* buff, size_t buff_size) {
    bool is_signed = 1;
    return integer_to_string_basic(num, is_signed, is_lower, base, buff, buff_size);
}

Code fraction_to_string(long double num, int64_t precision, char* buff, size_t buff_size) {
    if (!buff || buff_size == 0) {
        return EMPTY_BUFF;
    }
    int64_t int_part = (int64_t)num;
    long double frac_part = num - int_part;
    if (frac_part < 0)
        frac_part = -frac_part;

    char* p = buff;

    char tmp[64];
    bool is_signed = 1;
    Code code = integer_to_string(int_part, is_signed, tmp, sizeof(tmp));
    if (code != SUCCESS) return code;

    char* q = tmp;
    size_t len = 0;
    while (*q && len + 1 < buff_size) {
        *p++ = *q++;
        ++len;
    }
    // обработка точности после запятой
    if (precision > 0) {
        if (len + 1 >= buff_size) return BUFF_OVERFLOW;
        *p++ = '.';
        ++len;
        while (precision--) {
            if (len + 1 >= buff_size) return BUFF_OVERFLOW;
            frac_part *= 10.0;
            *p++ = (char)((int64_t)frac_part % 10 + '0');
            ++len;
        }
    }
    *p = 0;
    return SUCCESS;
}

Code move_it(size_t padding, char* buff, size_t buff_size) {
    if (!buff || buff_size == 0)
        return EMPTY_BUFF;

    size_t len = strlen(buff);
    if (padding > 0 && padding > len) {
        // +терминирующий ноль
        if (padding + 1 >= buff_size) return BUFF_OVERFLOW;

        memmove(buff + padding - len, buff, len);
        memset(buff, ' ', padding - len);

        buff[padding] = 0;
    }
    return SUCCESS;
}


Code integer_to_roman(int64_t num, char* buff, size_t buff_size) {
    if (!buff || buff_size == 0 || num <= 0 || num > 3999) {
        return EMPTY_BUFF;
    }
    char* p = buff;
    while (num && p - buff < buff_size - 1) {
        if (num >= 1000) { strcpy(p, "M"); num -= 1000; p += 1; }
        else if (num >= 900) { strcpy(p, "CM"); num -= 900; p += 2; }
        else if (num >= 500) { strcpy(p, "D"); num -= 500; p += 1; }
        else if (num >= 400) { strcpy(p, "CD"); num -= 400; p += 2; }
        else if (num >= 100) { strcpy(p, "C"); num -= 100; p += 1; }
        else if (num >= 90) { strcpy(p, "XC"); num -= 90; p += 2; }
        else if (num >= 50) { strcpy(p, "L"); num -= 50; p += 1; }
        else if (num >= 40) { strcpy(p, "XL"); num -= 40; p += 2; }
        else if (num >= 10) { strcpy(p, "X"); num -= 10; p += 1; }
        else if (num >= 9) { strcpy(p, "IX"); num -= 9; p += 2; }
        else if (num >= 5) { strcpy(p, "V"); num -= 5; p += 1; }
        else if (num >= 4) { strcpy(p, "IV"); num -= 4; p += 2; }
        else { strcpy(p, "I"); num -= 1; p += 1; }
    }
    *p = 0;
    return SUCCESS;
}


Code fibonacci(uint64_t value, uint64_t** fib, size_t* n) {
    if (value == 0) return ZERO_NUMBER;
    if (*fib == NULL) {
        *fib = (uint64_t*)malloc(10 * sizeof(uint64_t));
        if (!*fib) return MEM_ALLOC;
    }
    if (value == 1) {
        *fib[0] = 1;
        *n = 1;
        return SUCCESS;
    }

    size_t cap = 10, sz = 2;
    // Для представления Цекендорфа числа Фибоначчи: F_i, где i >= 2
    (*fib)[0] = 1;
    (*fib)[1] = 2;
    while ((*fib)[sz - 1] + (*fib)[sz - 2] <= value) {
        if (cap <= sz) {
            cap *= 2;
            uint64_t* new_fib = (uint64_t*)realloc(*fib, cap * sizeof(uint64_t));
            if (!new_fib) {
                free(*fib);
                *fib = NULL;
                return MEM_ALLOC;
            }
            *fib = new_fib;
        }
        (*fib)[sz] = (*fib)[sz - 1] + (*fib)[sz - 2];
        ++sz;
    }
    *n = sz;
    return SUCCESS;
}

// Соединяем полученные данные в единое представление
Code zeckendorf_view(const bool* is_view, size_t sz, char* buff, size_t buff_size) {
    if (sz + 2 > buff_size) return BUFF_OVERFLOW;
    char* p = buff;
    for (size_t i = 0; i < sz; ++i) {
        *p++ = (char)('0' + is_view[i]);
    }
    *p++ = '1';
    *p = 0;
    return SUCCESS;
}

Code zeckendorf_calc(uint64_t value, char* buff, size_t buff_size) {
    if (!buff || buff_size == 0) {
        return EMPTY_BUFF;
    }
    uint64_t* fib = NULL;
    size_t sz = 0;

    Code code = fibonacci(value, &fib, &sz);

    if (code != SUCCESS) return code;

    bool* is_view = (bool*)calloc(sz, sizeof(bool));
    if (!is_view) {
        free(fib);
        return MEM_ALLOC;
    }
    // жадно ищем наибольшее подходящее число Фибоначчи
    uint64_t curr = 0;
    for (size_t i = sz; i-- > 0;) {
        if (curr + fib[i] <= value) {
            curr += fib[i];
            // отмечаем подходящее число в массиве
            is_view[i] = 1;
        }
        if (curr == value) break;
    }
    code = zeckendorf_view(is_view, sz, buff, buff_size);
    free(fib);
    free(is_view);
    return code;
}

Code string_to_integer(const char* str, bool is_lower, int64_t base, int64_t* value) {
    if (!str || !*str) return ZERO_NUMBER;

    if (base < 2 || base > 36) {
        base = 10;
    }
    int8_t sign = 1;
    if (*str == '-') {
        ++str;
        sign = -1;
    }
    int64_t result = 0;
    while (*str) {
        result = result * base;
        if (isdigit(*str)) {
            result += *str - '0';
        } else if (is_lower && islower(*str)) {
            result += *str - 'a' + 10;
        } else if (!is_lower && isupper(*str)) {
            result += *str - 'A' + 10;
        } else {
            return INVALID_CASE;
        }
        ++str;
    }
    *value = sign * result;
    return SUCCESS;
}

Code memory_dump(const void* ptr, size_t size, char* buff, size_t buff_size) {
    if (!ptr || size == 0) {
        return EMPTY_BUFF;
    }
    const char* p = (const char*)ptr;
    char tmp[32];
    bool is_lower = 1;
    int64_t base = 16;

    int64_t value;
    size_t len = 0;
    for (size_t i = 0; i < size; ++i) {
        value = (bool)p[i];

        Code result = integer_to_base_string(value, is_lower, base, tmp, sizeof(tmp));
        if (result != SUCCESS) return result;

        char* q = tmp;
        while (*q) {
            if (len + 1 >= buff_size) return BUFF_OVERFLOW;
            *buff++ = *q++;
        }
        *buff++ = ' ';
    }
    *buff = 0;
    return SUCCESS;
}

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
    {"CV", TO_UPPER_INTEGER_BASE},
    {"to", TO_LOWER_DECIMAL},
    {"TO", TO_UPPER_DECIMAL},
    {"mi", INTEGER_MEMORY},
    {"mu", UNSIGNED_INTEGER_MEMORY},
    {"md", DOUBLE_MEMORY},
    {"mf", FLOAT_MEMORY}
};


Code parse_params(const char* pos, int64_t* width, int64_t* precision, int64_t* bytes) {
    // минимальная ширина строки
    while (isdigit(*pos)) {
        *width = *width * 10 + (*pos - '0');
        ++pos;
        ++*bytes;
    }
    // точность вещественного представления
    if (*pos == '.') {
        ++*bytes;
        ++pos;
        while (isdigit(*pos)) {
            *precision = *precision * 10 + (*pos - '0');
            ++pos;
            ++*bytes;
        }
    }
    // значение точности по умолчанию
    if (*precision == 0)
        *precision = 6;

    // тип данных
    for (size_t i = 0; i < sizeof(flags) / sizeof(Status); ++i) {
        size_t len = strlen(flags[i].flag_name);
        if (strncmp(pos, flags[i].flag_name, len) == 0) {
            *bytes += (int64_t)len;
            return flags[i].flag_value;
        }
    }
    return UNDEFINED_FLAG;
}

long double choose_arg(Code code, va_list* args) {
    switch (code) {
    case INTEGER:
        return (long double)va_arg(*args, int32_t);
    case LONG_INTEGER:
    case LONGLONG_INTEGER:
        return (long double)va_arg(*args, int64_t);
    case FLOAT:
    case DOUBLE:
        return (long double)va_arg(*args, double);
    case LONG_DOUBLE:
        return va_arg(*args, long double);
    default:
        return 0;
    }
}

uint64_t choose_arg_unsigned(Code code, va_list* args) {
    switch (code) {
    case UNSIGNED_INTEGER:
        return (uint64_t)va_arg(*args, uint64_t);
    case LONG_UNSIGNED_INTEGER:
    case LONGLONG_UNSIGNED_INTEGER:
        return (uint64_t)va_arg(*args, int64_t);
    default:
        return 0;
    }
}

typedef void (*output_func)(void* p, const char* str);

void file_output(void* p, const char* str) {
    fputs(str, (FILE*)p);
}

void string_output(void* p, const char* str) {
    // двойной указатель для сохранения смещения исходного указателя.
    char** s = (char**)p;
    while (*str)
        *(*s)++ = *str++;
}

int64_t overprintf_base(void* some, output_func out, const char* format, va_list* args) {
    if (some == NULL)
        return 0;

    size_t count = 0;
    while (*format) {
        if (*format == '%') {
            int64_t width = 0, precision = 0, bytes = 0;
            Code code = parse_params(++format, &width, &precision, &bytes);

            Code ans = SUCCESS;
            char buff[512];
            format += bytes;
            switch (code) {
            case (UNDEFINED_FLAG):
                return code;

            case (INTEGER):
            case (LONG_INTEGER):
            case (LONGLONG_INTEGER):
            {
                int64_t value = (int64_t)choose_arg(code, args);
                bool is_signed = 1;
                ans = integer_to_string(value, is_signed, buff, sizeof(buff));
                break;
            }
            case (UNSIGNED_INTEGER):
            case (LONG_UNSIGNED_INTEGER):
            case (LONGLONG_UNSIGNED_INTEGER):
            {
                uint64_t value = (uint64_t)choose_arg_unsigned(code, args);
                bool is_signed = 0;

                ans = integer_to_string(value, is_signed, buff, sizeof(buff));
                break;
            }
            case (FLOAT):
            case (DOUBLE):
            case (LONG_DOUBLE):
            {
                long double value = choose_arg(code, args);

                ans = fraction_to_string(value, precision, buff, sizeof(buff));
                break;
            }
            case (CHAR):
            {
                char value = (char)va_arg(*args, int);
                buff[0] = value; buff[1] = 0;
                break;
            }
            case (STRING):
            {
                char* string = va_arg(*args, char*);
                char* p = buff;
                size_t len = 0;
                while (*string) {
                    if (len + 1 >= sizeof(buff)) return BUFF_OVERFLOW;
                    *p++ = *string++;
                }
                break;
            }
            case (ROMAN):
            {
                int64_t value = va_arg(*args, int64_t);
                ans = integer_to_roman(value, buff, sizeof(buff));
                break;
            }
                case (ZECKENDORF):
            {
                uint64_t value = va_arg(*args, uint64_t);
                ans = zeckendorf_calc(value, buff, sizeof(buff));
                break;
            }
                case (TO_UPPER_INTEGER_BASE):
                case (TO_LOWER_INTEGER_BASE):
            {
                int64_t value = va_arg(*args, int64_t);
                int64_t base = va_arg(*args, int64_t);

                bool is_lower = code == TO_LOWER_INTEGER_BASE ? 1 : 0;
                ans = integer_to_base_string(value, is_lower, base, buff, sizeof(buff));
                break;
            }
            case (TO_LOWER_DECIMAL):
            case (TO_UPPER_DECIMAL):
            {
                char* string = va_arg(*args, char*);
                int64_t base = va_arg(*args, int64_t);

                bool is_lower = code == TO_LOWER_DECIMAL ? 1 : 0;

                int64_t value;
                Code part = string_to_integer(string, is_lower, base, &value);
                if (part != SUCCESS) return part;

                bool is_signed = 1;
                ans = integer_to_string(value, is_signed, buff, sizeof(buff));
                break;
            }

            case (INTEGER_MEMORY):
            {
                int32_t value = va_arg(*args, int32_t);

                ans = memory_dump(&value, sizeof(value), buff, sizeof(buff));
                break;
            }
            case (UNSIGNED_INTEGER_MEMORY):
            {
                uint32_t value = va_arg(*args, uint32_t);

                ans = memory_dump(&value, sizeof(value), buff, sizeof(buff));
                break;
            }
            case (FLOAT_MEMORY):
            {
                double promoted = va_arg(*args, double);

                float value = (float)promoted;

                ans = memory_dump(&value, sizeof(value), buff, sizeof(buff));
                break;
            }

            case (DOUBLE_MEMORY):
            {
                double value = va_arg(*args, double);

                ans = memory_dump(&value, sizeof(value), buff, sizeof(buff));
                break;
            }
            default:
                break;
            }
            if (ans != SUCCESS)
                return ans;
            if (width > 0) {
                move_it(width, buff, sizeof(buff));
            }
            count += strlen(buff);
            out(some, buff);
        }
        else {
            char s[] = {*format++, 0};
            out(some, s);
        }
    }
    return (int64_t)count;
}

int64_t overfprintf(FILE* stream, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int64_t res = overprintf_base(stream, file_output, format, &args);
    va_end(args);
    return res;
}

int64_t oversprintf(char* str, const char* format, ...) {
    va_list args;
    va_start(args, format);
    // Используем двойной указатель, чтобы сдвинуть str и потом поставить терминирующий ноль.
    int64_t res = overprintf_base(&str, string_output, format, &args);
    *str = 0;
    va_end(args);
    return res;
}
