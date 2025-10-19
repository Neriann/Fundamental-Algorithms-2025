#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "assert_base.h"
#include "functions.h"


void test_flag_d() {
    printf("=== Testing flag %%d (integer) ===\n");

    char buffer[256];

    // Тест 1: Простые числа
    int64_t result = oversprintf(buffer, "%d", 42);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "42") == 0);

    // Тест 2: Отрицательные числа
    result = oversprintf(buffer, "%d", -123);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "-123") == 0);

    // Тест 3: Ноль
    result = oversprintf(buffer, "%d", 0);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "0") == 0);

    // Тест 4: С шириной
    result = oversprintf(buffer, "%5d", 42);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "   42") == 0);
}

void test_flag_ld() {
    printf("\n=== Testing flag %%ld (long integer) ===\n");

    char buffer[256];

    long test_long = 123456789L;
    int64_t result = oversprintf(buffer, "%ld", test_long);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "123456789") == 0);

    // Отрицательное long
    result = oversprintf(buffer, "%ld", -987654321L);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "-987654321") == 0);
}

void test_flag_lld() {
    printf("\n=== Testing flag %%lld (long long integer) ===\n");

    char buffer[256];

    long long test_llong = 9223372036854775807LL;
    int64_t result = oversprintf(buffer, "%lld", test_llong);
    ASSERT_MSG(result > 0);
    printf("LLONG_MAX = %s\n", buffer);
}

void test_flag_u() {
    printf("\n=== Testing flag %%u (unsigned integer) ===\n");

    char buffer[256];

    // Тест 1: Простые беззнаковые числа
    int64_t result = oversprintf(buffer, "%u", 123);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "123") == 0);

    // Тест 2: Большие беззнаковые числа
    result = oversprintf(buffer, "%u", 4294967295U);
    ASSERT_MSG(result > 0);
    printf("UINT32_MAX = %s\n", buffer);
}

void test_flag_lu_llu() {
    printf("\n=== Testing flags %%lu, %%llu (long unsigned) ===\n");

    char buffer[256];

    unsigned long test_ulong = 123456789UL;
    int64_t result = oversprintf(buffer, "%lu", test_ulong);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "123456789") == 0);

    unsigned long long test_ullong = 18446744073709551615ULL;
    result = oversprintf(buffer, "%llu", test_ullong);
    ASSERT_MSG(result > 0);
    printf("ULLONG_MAX = %s\n", buffer);
}

void test_flag_f() {
    printf("\n=== Testing flag %%f (float) ===\n");

    char buffer[256];

    // Тест 1: Простые вещественные
    int64_t result = oversprintf(buffer, "%.2f", 3.14159);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "3.14") == 0);

    // Тест 2: Отрицательные
    result = oversprintf(buffer, "%.3f", -2.71828);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "-2.718") == 0);

    // Тест 3: Точность по умолчанию
    result = oversprintf(buffer, "%f", 1.5);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strstr(buffer, "1.500000") != NULL);
}

void test_flag_lf() {
    printf("\n=== Testing flag %%lf (double) ===\n");

    char buffer[256];

    double test_double = 123.456789;
    int64_t result = oversprintf(buffer, "%.4lf", test_double);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "123.4568") == 0);
}

void test_flag_Lf() {
    printf("\n=== Testing flag %%Lf (long double) ===\n");

    char buffer[256];

    long double test_ldouble = 123.456789L;
    int64_t result = oversprintf(buffer, "%.3Lf", test_ldouble);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "123.457") == 0);
}

void test_flag_c() {
    printf("\n=== Testing flag %%c (char) ===\n");

    char buffer[256];

    // Тест 1: Обычные символы
    int64_t result = oversprintf(buffer, "%c", 'A');
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "A") == 0);

    // Тест 2: Специальные символы
    result = oversprintf(buffer, "%c", ' ');
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, " ") == 0);

    result = oversprintf(buffer, "%c", '7');
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "7") == 0);
}

void test_flag_s() {
    printf("\n=== Testing flag %%s (string) ===\n");

    char buffer[256];

    // Тест 1: Простые строки
    int64_t result = oversprintf(buffer, "%s", "Hello");
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "Hello") == 0);

    // Тест 2: Пустая строка
    result = oversprintf(buffer, "%s", "");
    ASSERT_MSG(result == 0);
    ASSERT_MSG(strcmp(buffer, "") == 0);

    // Тест 3: С шириной
    result = oversprintf(buffer, "%10s", "test");
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "      test") == 0);
}

void test_flag_Ro() {
    printf("\n=== Testing flag %%Ro (Roman) ===\n");

    char buffer[256];

    // Тест 1: Простые римские числа
    int64_t result = oversprintf(buffer, "%Ro", 4);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "IV") == 0);

    // Тест 2: Сложные числа
    result = oversprintf(buffer, "%Ro", 1987);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "MCMLXXXVII") == 0);

    // Тест 3: Максимальное значение
    result = oversprintf(buffer, "%Ro", 3999);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "MMMCMXCIX") == 0);
}

void test_flag_Zr() {
    printf("\n=== Testing flag %%Zr (Zeckendorf) ===\n");

    char buffer[256];

    // Тест представления Цекендорфа
    int64_t result = oversprintf(buffer, "%Zr", 10);
    ASSERT_MSG(result > 0);
    printf("Zeckendorf(10) = %s\n", buffer);

    result = oversprintf(buffer, "%Zr", 20);
    ASSERT_MSG(result > 0);
    printf("Zeckendorf(20) = %s\n", buffer);

    result = oversprintf(buffer, "%Zr", 100);
    ASSERT_MSG(result > 0);
    printf("Zeckendorf(100) = %s\n", buffer);
}

void test_flag_Cv_CV() {
    printf("\n=== Testing flags %%Cv, %%CV (base conversion) ===\n");

    char buffer[256];

    // Тест 1: Шестнадцатеричная система (нижний регистр)
    int64_t result = oversprintf(buffer, "%Cv", 255LL, 16LL);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "ff") == 0);

    // Тест 2: Шестнадцатеричная система (верхний регистр)
    result = oversprintf(buffer, "%CV", 255LL, 16LL);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "FF") == 0);

    // Тест 3: Двоичная система
    result = oversprintf(buffer, "%Cv", 10LL, 2LL);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "1010") == 0);

    // Тест 4: Восьмеричная система
    result = oversprintf(buffer, "%CV", 64LL, 8LL);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "100") == 0);

    // Тест 5: Отрицательные числа
    result = oversprintf(buffer, "%Cv", -42LL, 16LL);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "-2a") == 0);
}

void test_flag_to_TO() {
    printf("\n=== Testing flags %%to, %%TO (string to integer) ===\n");

    char buffer[256];

    // Тест 1: Десятичная система из строки
    int64_t result = oversprintf(buffer, "%to", "123", 10);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "123") == 0);

    // Тест 2: Шестнадцатеричная система (нижний регистр)
    result = oversprintf(buffer, "%to", "ff", 16);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "255") == 0);

    // Тест 3: Шестнадцатеричная система (верхний регистр)
    result = oversprintf(buffer, "%TO", "FF", 16);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "255") == 0);

    // Тест 4: Двоичная система
    result = oversprintf(buffer, "%to", "1010", 2);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "10") == 0);

    // Тест 5: Отрицательные числа
    result = oversprintf(buffer, "%to", "-42", 10);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "-42") == 0);
}

void test_flag_mi_mu() {
    printf("\n=== Testing flags %%mi, %%mu (memory dump) ===\n");

    char buffer[512];

    // Тест 1: Дамп знакового целого
    int32_t test_int = 0x12345678;
    int64_t result = oversprintf(buffer, "%mi", test_int);
    ASSERT_MSG(result > 0);
    printf("Memory dump int: %s\n", buffer);

    // Тест 2: Дамп беззнакового целого
    uint32_t test_uint = 0xABCDEF12;
    result = oversprintf(buffer, "%mu", test_uint);
    ASSERT_MSG(result > 0);
    printf("Memory dump uint: %s\n", buffer);
}

void test_flag_mf_md() {
    printf("\n=== Testing flags %%mf, %%md (float/double memory dump) ===\n");

    char buffer[512];

    // Тест 1: Дамп float
    float test_float = 3.14f;
    int64_t result = oversprintf(buffer, "%mf", test_float);
    ASSERT_MSG(result > 0);
    printf("Memory dump float: %s\n", buffer);

    // Тест 2: Дамп double
    double test_double = 2.71828;
    result = oversprintf(buffer, "%md", test_double);
    ASSERT_MSG(result > 0);
    printf("Memory dump double: %s\n", buffer);
}

void test_multiple_flags() {
    printf("\n=== Testing multiple flags combination ===\n");

    char buffer[512];

    // Тест комбинации разных флагов
    int64_t result = oversprintf(buffer, "Int: %d, Float: %.2f, String: %s, Char: %c",
                                42, 3.14159, "test", 'X');
    ASSERT_MSG(result > 0);
    printf("Combined: %s\n", buffer);

    // Тест с шириной и разными типами
    result = oversprintf(buffer, "|%5d|%10.3f|%8s|", 123, 45.6789, "hello");
    ASSERT_MSG(result > 0);
    printf("Formatted: %s\n", buffer);

    // Тест специальных форматов
    result = oversprintf(buffer, "Roman: %Ro, Base: %CV, Zeck: %Zr",
                        2023, 255, 16, 20);
    ASSERT_MSG(result > 0);
    printf("Special formats: %s\n", buffer);
}

void test_width_precision() {
    printf("\n=== Testing width and precision ===\n");

    char buffer[256];

    // Тест ширины
    int64_t result = oversprintf(buffer, "%8d", 42);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "      42") == 0);

    // Тест точности для вещественных
    result = oversprintf(buffer, "%.3f", 3.14159);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "3.142") == 0);

    // Тест ширины и точности вместе
    result = oversprintf(buffer, "%10.2f", 123.456);
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "    123.46") == 0);

    // Тест ширины для строк
    result = oversprintf(buffer, "%6s", "abc");
    ASSERT_MSG(result > 0);
    ASSERT_MSG(strcmp(buffer, "   abc") == 0);
}

int main() {
    printf("Starting comprehensive flag tests...\n\n");

    test_flag_d();
    test_flag_ld();
    test_flag_lld();
    test_flag_u();
    test_flag_lu_llu();
    test_flag_f();
    test_flag_lf();
    test_flag_Lf();
    test_flag_c();
    test_flag_s();
    test_flag_Ro();
    test_flag_Zr();
    test_flag_Cv_CV();
    test_flag_to_TO();
    test_flag_mi_mu();
    test_flag_mf_md();
    test_multiple_flags();
    test_width_precision();

    printf("\n=== All flag tests passed successfully! ===\n");
    return 0;
}
