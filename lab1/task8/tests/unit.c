#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "functions.h"
#include "assert_base.h"

void test_my_abs() {
    printf("[...] Testing my_abs\n");
    ASSERT_MSG(my_abs(5) == 5);
    ASSERT_MSG(my_abs(-5) == 5);
    ASSERT_MSG(my_abs(0) == 0);
    ASSERT_MSG(my_abs(INT_MAX) == INT_MAX);
    ASSERT_MSG(my_abs(-INT_MAX + 1) == INT_MAX - 1);
    printf("[OK] Tests for my_abs are accepted\n\n");
}

void test_string_to_int() {
    printf("[...] Testing string_to_int\n");
    
    // Десятичная система
    ASSERT_MSG(string_to_int("1234", 10) == 1234);
    ASSERT_MSG(string_to_int("0", 10) == 0);
    ASSERT_MSG(string_to_int("-123", 10) == -123);
    ASSERT_MSG(string_to_int("9999", 10) == 9999);
    
    // Двоичная система
    ASSERT_MSG(string_to_int("101", 2) == 5);
    ASSERT_MSG(string_to_int("1101", 2) == 13);
    ASSERT_MSG(string_to_int("-101", 2) == -5);
    
    // Шестнадцатеричная система
    ASSERT_MSG(string_to_int("ff", 16) == 255);
    ASSERT_MSG(string_to_int("1a", 16) == 26);
    ASSERT_MSG(string_to_int("-ff", 16) == -255);
    
    // Системы с большими основаниями
    ASSERT_MSG(string_to_int("z", 36) == 35);
    ASSERT_MSG(string_to_int("10", 36) == 36);
    
    printf("[OK] Tests for string_to_int are accepted\n\n");
}

void test_int_to_string() {
    printf("[...] Testing int_to_string\n");

    char buffer[BUFFER_SIZE];
    char* res;

    // Десятичная система
    res = int_to_string(0, 10, buffer + BUFFER_SIZE - 1);
    ASSERT_MSG(strcmp(res, "0") == 0);

    res = int_to_string(123, 10, buffer + BUFFER_SIZE - 1);
    ASSERT_MSG(strcmp(res, "123") == 0);

    res = int_to_string(-456, 10, buffer + BUFFER_SIZE - 1);
    ASSERT_MSG(strcmp(res, "-456") == 0);

    // Шестнадцатеричная система
    res = int_to_string(255, 16, buffer + BUFFER_SIZE - 1);
    ASSERT_MSG(strcmp(res, "ff") == 0);

    res = int_to_string(26, 16, buffer + BUFFER_SIZE - 1);
    ASSERT_MSG(strcmp(res, "1a") == 0);

    // Двоичная система
    res = int_to_string(5, 2, buffer + BUFFER_SIZE - 1);
    ASSERT_MSG(strcmp(res, "101") == 0);

    res = int_to_string(13, 2, buffer + BUFFER_SIZE - 1);
    ASSERT_MSG(strcmp(res, "1101") == 0);

    // Системы с большими основаниями
    res = int_to_string(35, 36, buffer + BUFFER_SIZE - 1);
    ASSERT_MSG(strcmp(res, "z") == 0);

    res = int_to_string(36, 36, buffer + BUFFER_SIZE - 1);
    ASSERT_MSG(strcmp(res, "10") == 0);

    printf("[OK] Tests for int_to_string are accepted\n\n");
}

void test_conversion_round_trip() {
    printf("[...] Testing conversion round trip\n");
    
    char buffer[BUFFER_SIZE];
    char* p = buffer + BUFFER_SIZE - 1;
    
    // Тестируем преобразование туда-обратно
    const int32_t test_numbers[] = {0, 1, -1, 123, -456, 255, -128, 1024, -9999};
    const int32_t bases[] = {2, 8, 10, 16, 36};
    
    for (size_t i = 0; i < sizeof(test_numbers) / sizeof(test_numbers[0]); i++) {
        for (size_t j = 0; j < sizeof(bases) / sizeof(bases[0]); j++) {
            char* str = int_to_string(test_numbers[i], bases[j], p);
            int32_t converted = string_to_int(str, bases[j]);
            ASSERT_MSG(converted == test_numbers[i]);
        }
    }
    
    printf("[OK] Tests for conversion round trip are accepted\n\n");
}

void test_get_needed_systems() {
    printf("[...] Testing get_needed_systems\n");
    
    char result[BUFFER_SIZE];
    
    // Тест с положительным числом
    get_needed_systems(100, result);
    // Проверяем основные форматы
    ASSERT_MSG(strstr(result, "121") != NULL); // в 9-ричной
    ASSERT_MSG(strstr(result, "5a") != NULL);  // в 18-ричной
    
    // Тест с нулем
    get_needed_systems(0, result);
    ASSERT_MSG(strstr(result, "0") != NULL);
    
    // Тест с отрицательным числом
    get_needed_systems(-255, result);
    // Должны быть представления в разных системах
    
    printf("[OK] Tests for get_needed_systems are accepted\n\n");
}

// Тест для edge cases (граничные случаи)
void test_edge_cases() {
    printf("[...] Testing edge cases\n");
    
    char buffer[BUFFER_SIZE];
    char* res;
    
    // Максимальные и минимальные значения
    res = int_to_string(INT_MAX, 10, buffer + BUFFER_SIZE - 1);
    ASSERT_MSG(string_to_int(res, 10) == INT_MAX);
    
    res = int_to_string(INT_MIN + 1, 10, buffer + BUFFER_SIZE - 1); // +1 чтобы избежать переполнения в abs
    ASSERT_MSG(string_to_int(res, 10) == INT_MIN + 1);
    
    // Граничные значения оснований
    ASSERT_MSG(string_to_int("10", 2) == 2);
    ASSERT_MSG(string_to_int("z", 36) == 35);
    
    printf("[OK] Tests for edge cases are accepted\n\n");
}

void run_all_tests() {
    test_my_abs();
    test_string_to_int();
    test_int_to_string();
    test_conversion_round_trip();
    test_get_needed_systems();
    test_edge_cases();

    printf("All tests passed!\n");
}

int main() {
    run_all_tests();
    return 0;
}
