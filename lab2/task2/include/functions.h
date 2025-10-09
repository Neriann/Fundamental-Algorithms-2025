#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>


void* my_memchr(const void* str, int c, size_t n);

int my_memcmp(const void* str1, const void* str2, size_t n);

void* my_memcpy(void* dest, const void* str, size_t n);

void* my_memset(void* str, int c, size_t n);

char* my_strncat(char* dest, const char* src, size_t n);

char* my_strchf(const char* str, int c);

int my_strncmp(const char* str1, const char* str2, size_t n);

size_t my_strlen(const char* str);

char* my_strncpy(char* dest, const char* src, size_t n);

size_t my_strcspn(const char* str1, const char* str2);

char* my_strerror(int errnum);

char* my_strpbrk(const char* str1, const char* str2);

char* my_strchl(const char* str, int c);

char* my_strstr(const char* haystack, const char* needle);

char* my_strtok(char* str, const char* delim);

#endif //FUNCTIONS_H
