#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "functions.h"
#include "assert_base.h"


void test_get_base_number() {
    printf("[...] Testing get_base_number\n");

    // Только цифры
    ASSERT_MSG(get_base_number("123") == 4);  // max digit '3' -> base 3+1=4
    ASSERT_MSG(get_base_number("0") == 1);    // max digit '0' -> base 0+1=1
    ASSERT_MSG(get_base_number("9") == 10);   // max digit '9' -> base 9+1=10
    ASSERT_MSG(get_base_number("456") == 7);  // max digit '6' -> base 6+1=7

    // С буквами (строчными)
    ASSERT_MSG(get_base_number("abc") == 13); // max letter 'c' -> base 12+1=13
    ASSERT_MSG(get_base_number("z") == 36);   // max letter 'z' -> base 35+1=36
    ASSERT_MSG(get_base_number("a1b2") == 12); // max letter 'b' -> base 11+1=12
    ASSERT_MSG(get_base_number("f") == 16);   // max letter 'f' -> base 15+1=16

    // С буквами (заглавными) - должен преобразовывать в строчные
    ASSERT_MSG(get_base_number("ABC") == 13); // max letter 'C' -> base 12+1=13
    ASSERT_MSG(get_base_number("Z") == 36);   // max letter 'Z' -> base 35+1=36

    // Смешанные цифры и буквы
    ASSERT_MSG(get_base_number("a9z") == 36); // max letter 'z' -> base 35+1=36
    ASSERT_MSG(get_base_number("1f") == 16);  // max letter 'f' -> base 15+1=16

    printf("[OK] Tests for get_base_number are accepted\n\n");
}

void test_string_to_int() {
    printf("[...] Testing string_to_int\n");

    // Десятичная система
    ASSERT_MSG(string_to_int("123", 10) == 123);
    ASSERT_MSG(string_to_int("0", 10) == 0);
    ASSERT_MSG(string_to_int("999", 10) == 999);

    // Двоичная система
    ASSERT_MSG(string_to_int("101", 2) == 5);
    ASSERT_MSG(string_to_int("1101", 2) == 13);
    ASSERT_MSG(string_to_int("0", 2) == 0);

    // Восьмеричная система
    ASSERT_MSG(string_to_int("10", 8) == 8);
    ASSERT_MSG(string_to_int("77", 8) == 63);

    // Шестнадцатеричная система (строчные)
    ASSERT_MSG(string_to_int("ff", 16) == 255);
    ASSERT_MSG(string_to_int("1a", 16) == 26);
    ASSERT_MSG(string_to_int("a", 16) == 10);

    // Шестнадцатеричная система (заглавные) - должны преобразовываться в строчные
    ASSERT_MSG(string_to_int("FF", 16) == 255);
    ASSERT_MSG(string_to_int("1A", 16) == 26);
    ASSERT_MSG(string_to_int("A", 16) == 10);

    // Системы с большими основаниями
    ASSERT_MSG(string_to_int("z", 36) == 35);
    ASSERT_MSG(string_to_int("10", 36) == 36);
    ASSERT_MSG(string_to_int("1z", 36) == 71); // 1*36 + 35 = 71

    // Некорректные основания
    ASSERT_MSG(string_to_int("123", 1) == -1);   // base < 2
    ASSERT_MSG(string_to_int("123", 37) == -1);  // base > 36
    ASSERT_MSG(string_to_int("123", 0) == -1);   // base = 0

    printf("[OK] Tests for string_to_int are accepted\n\n");
}

void test_choose_string_basic() {
    printf("[...] Testing choose_string basic cases\n");

    char result[BUFFER_SIZE];
    const char* input;

    // Одно число
    input = "123";
    choose_string(input, result);
    ASSERT_MSG(strstr(result, "123") != NULL);
    ASSERT_MSG(strstr(result, "4") != NULL);  // base 4 для "123"
    ASSERT_MSG(strstr(result, "27") != NULL); // 123 в base4 = 1*16 + 2*4 + 3 = 27

    // Одна буква
    input = "abc";
    choose_string(input, result);
    ASSERT_MSG(strstr(result, "abc") != NULL);
    ASSERT_MSG(strstr(result, "13") != NULL); // base 13 для "abc"

    // Несколько чисел разделенных не-буквоцифровыми символами
    input = "123 456";
    choose_string(input, result);
    ASSERT_MSG(strstr(result, "123") != NULL);
    ASSERT_MSG(strstr(result, "456") != NULL);

    printf("[OK] Tests for choose_string basic cases are accepted\n\n");
}

void test_choose_string_complex() {
    printf("[...] Testing choose_string complex cases\n");

    char result[BUFFER_SIZE];
    const char* input;

    // Смешанные буквы и цифры
    input = "a1b2";
    choose_string(input, result);
    ASSERT_MSG(strstr(result, "a1b2") != NULL);
    ASSERT_MSG(strstr(result, "12") != NULL); // base 12 для "a1b2"

    // Специальные символы как разделители
    input = "hello,world!test123";
    choose_string(input, result);
    ASSERT_MSG(strstr(result, "hello") != NULL);
    ASSERT_MSG(strstr(result, "world") != NULL);
    ASSERT_MSG(strstr(result, "test123") != NULL);

    // Числа с разными основаниями
    input = "1a 2b 3c";
    choose_string(input, result);
    ASSERT_MSG(strstr(result, "1a") != NULL);
    ASSERT_MSG(strstr(result, "2b") != NULL);
    ASSERT_MSG(strstr(result, "3c") != NULL);

    printf("[OK] Tests for choose_string complex cases are accepted\n\n");
}

void test_choose_string_edge_cases() {
    printf("[...] Testing choose_string edge cases\n");

    char result[BUFFER_SIZE];
    const char* input;

    // Пустая строка
    input = "";
    choose_string(input, result);
    ASSERT_MSG(strlen(result) == 0 || result[0] == 0);

    // Только специальные символы
    input = "!@#$%^&*()";
    choose_string(input, result);
    ASSERT_MSG(strlen(result) == 0 || result[0] == 0);

    // Одна цифра
    input = "5";
    choose_string(input, result);
    ASSERT_MSG(strstr(result, "5") != NULL);
    ASSERT_MSG(strstr(result, "6") != NULL); // base 6 для "5"

    // Одна буква
    input = "f";
    choose_string(input, result);
    ASSERT_MSG(strstr(result, "f") != NULL);
    ASSERT_MSG(strstr(result, "16") != NULL); // base 16 для "f"

    printf("[OK] Tests for choose_string edge cases are accepted\n\n");
}

void test_integration() {
    printf("[...] Testing integration between functions\n");

    // Проверяем, что функции работают согласованно
    const char* test_strings[] = {"123", "abc", "1a2b", "9z", "0"};
    const int expected_bases[] = {4, 13, 12, 36, 1};

    for (int i = 0; i < 5; i++) {
        const char* str = test_strings[i];
        int32_t base = get_base_number(str);
        ASSERT_MSG(base == expected_bases[i]);

        // Для корректных оснований проверяем преобразование
        if (base >= 2 && base <= 36) {
            int32_t value = string_to_int(str, base);
            ASSERT_MSG(value >= 0); // Должно быть валидное значение
        }
    }

    printf("[OK] Integration tests are accepted\n\n");
}

void run_all_tests() {
    test_get_base_number();
    test_string_to_int();
    test_choose_string_basic();
    test_choose_string_complex();
    test_choose_string_edge_cases();
    test_integration();

    printf("All tests passed!\n");
}

int main() {
    run_all_tests();
    return 0;
}
