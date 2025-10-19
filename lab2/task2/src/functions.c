#include "functions.h"

#include <stdio.h>

#include "errors.h"

// В каждой из функций считаем что по поступающему указателю корректно выделена память

// Ищем первое вхождение c
void* my_memchr(const void* str, int c, size_t n) {
    if (!str)
        return NULL;

    const unsigned char* p = (const unsigned char*)str;
    for (size_t i = 0; i < n; ++i) {
        if ((int)p[i] == c) {
            return (void*)(p + i);
        }
    }
    return NULL;
}

// Сравниваем байты
int my_memcmp(const void* str1, const void* str2, size_t n) {
    if (!str1 || !str2)
        return -2;

    const unsigned char* p1 = (const unsigned char*)str1;
    const unsigned char* p2 = (const unsigned char*)str2;
    for (size_t i = 0; i < n; ++i) {
        if (p1[i] != p2[i]) {
            return p1[i] > p2[i] ? 1 : -1;
        }
    }
    return 0;
}

// Копируем объект (deep copy, так как dest уже указывает на другой пул памяти)
void* my_memcpy(void* dest, const void* str, size_t n) {
    if (!dest || !str)
        return NULL;

    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)str;
    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
    return dest;
}

// Ставим n байт равных c
void* my_memset(void* str, int c, size_t n) {
    if (!str)
        return NULL;

    unsigned char* p = (unsigned char*)str;
    for (size_t i = 0; i < n; ++i) {
        p[i] = c;
    }
    return str;
}

char* my_strncat(char* dest, const char* src, size_t n) {
    if (!dest || !src)
        return NULL;

    size_t len = my_strlen(dest);
    size_t i = 0;
    for (; i < n && src[i] != 0; ++i) {
        dest[len + i] = src[i];
    }
    dest[len + i] = 0;
    return dest;
}

char* my_strchf(const char* str, int c) {
    if (!str)
        return NULL;

    while (*str) {
        if ((int)*str == c) {
            return (char*)str;
        }
        ++str;
    }
    return NULL;
}

// Сравниваем две строки до n символов
int my_strncmp(const char* str1, const char* str2, size_t n) {
    if (!str1 || !str2)
        return -2;

    for (size_t i = 0; i < n; ++i) {
        if (str1[i] == 0 && str2[i] == 0) {
            return 0;
        }
        if (str1[i] != str2[i]) {
            return str1[i] > str2[i] ? 1 : -1;
        }
    }
    return 0;
}

size_t my_strlen(const char* str) {
    if (!str)
        return 0;

    size_t len = 0;
    while (*str++) {
        ++len;
    }
    return len;
}

char* my_strncpy(char* dest, const char* src, size_t n) {
    if (!dest || !src)
        return NULL;

    size_t i = 0;
    for (; i < n && src[i] != 0; ++i) {
        dest[i] = src[i];
    }
    dest[i] = 0;
    return dest;
}

size_t my_strcspn(const char* str1, const char* str2) {
    if (!str1 || !str2)
        return 0;

    size_t i = 0;
    for (; str1[i] != 0; ++i) {
        for (size_t j = 0; str2[j] != 0; ++j) {
            if (str1[i] == str2[j]) {
                return i;
            }
        }
    }
    return i;
}

char* my_strerror(int errnum) {
    static char buff[128];
    if (errnum < 0 || errnum >= max_error) {
        snprintf(buff, sizeof(buff), "Unknown error: %d", errnum);
        return buff;
    }
    return (char*)errlist[errnum];
}

char* my_strpbrk(const char* str1, const char* str2) {
    if (!str1 || !str2)
        return NULL;

    size_t i = 0;
    for (; str1[i] != 0; ++i) {
        for (size_t j = 0; str2[j] != 0; ++j) {
            if (str1[i] == str2[j]) {
                return (char*)str1 + i;
            }
        }
    }
    return NULL;
}

char* my_strchl(const char* str, int c) {
    if (!str)
        return NULL;

    size_t len = my_strlen(str);
    for (int i = (int)len - 1; i >= 0; --i) {
        if (str[i] == c) {
            return (char*)str + i;
        }
    }
    return NULL;
}

char* my_strstr(const char* haystack, const char* needle) {
    if (!haystack || !needle)
        return NULL;

    const char* p1;
    const char* p2;
    for (; *haystack; ++haystack) {
        p1 = haystack;
        p2 = needle;
        while (*p1 == *p2) {
            ++p1;
            ++p2;
            if (*p2 == 0)
                return (char*)haystack;
        }
    }
    return NULL;
}

char* my_strtok(char* str, const char* delim) {
    static char* curr = NULL;
    if (str)
        curr = str;
    if (!delim || !curr)
        return NULL;

    while (*curr && my_strchf(delim, *curr))
        ++curr;

    if (!curr)
        return NULL;

    char* res = curr;
    while (*curr) {
        if (my_strchf(delim, *curr)) {
            *curr++ = 0;
            return res;
        }
        ++curr;
    }

    if (*res) {
        curr = NULL;
        return res;
    }

    return NULL;
}
