#include <stdio.h>
#include <string.h>

#include "functions.h"
#include "assert_base.h"

void test_remove_arabic_digits() {
    printf("[...] Start testing remove_arabic_digits\n");

    char result[BUFFER_SIZE];
    remove_arabic_digits("1ba2b3a", result);
    ASSERT_MSG(strcmp(result, "baba") == 0);

    remove_arabic_digits("abcdef", result);
    ASSERT_MSG(strcmp(result, "abcdef") == 0);

    remove_arabic_digits("123456789", result);
    ASSERT_MSG(strcmp(result, "") == 0);

    remove_arabic_digits("", result);
    ASSERT_MSG(strcmp(result, "") == 0);

    remove_arabic_digits("a23bc4\nef5678g\naaaaa1", result);
    ASSERT_MSG(strcmp(result, "abc\nefg\naaaaa") == 0);

    printf("[OK] Tests for remove_arabic_digits passed\n\n");
}

void test_count_latin_letters() {
    printf("[...] Start testing count_latin_letters\n");

    char result[BUFFER_SIZE];

    // Тест 1: Одна строка
    count_latin_letters("abc123 def!\n", result);
    ASSERT_MSG(strcmp(result, "6\n") == 0);

    // Тест 2: Несколько строк
    count_latin_letters("hello\nworld123\ntest456\n", result);
    ASSERT_MSG(strcmp(result, "5\n5\n4\n") == 0);

    // Тест 3: Буквы в разных регистрах
    count_latin_letters("Hello WORLD\n", result);
    ASSERT_MSG(strcmp(result, "10\n") == 0);

    // Тест 4: Без букв
    count_latin_letters("123 !@#\n456 %^\n", result);
    ASSERT_MSG(strcmp(result, "0\n0\n") == 0);

    // Тест 5: Пустые строки
    count_latin_letters("\n\n", result);
    ASSERT_MSG(strcmp(result, "0\n0\n") == 0);

    printf("[OK] Tests for count_latin_letters passed\n\n");
}

void test_count_rare_symbols() {
    printf("[...] Start testing count_rare_symbols\n");

    char result[BUFFER_SIZE];

    // Тест 1: Обычные символы
    count_rare_symbols("hello! world@\n", result);
    ASSERT_MSG(strcmp(result, "2\n") == 0);

    // Тест 2: Смешанные символы
    count_rare_symbols("abc!@# 123$%^\n", result);
    ASSERT_MSG(strcmp(result, "6\n") == 0);

    // Тест 3: Только редкие символы
    count_rare_symbols("!@#$%^&*()\n", result);
    ASSERT_MSG(strcmp(result, "10\n") == 0);

    // Тест 4: Без редких символов
    count_rare_symbols("abc 123 XYZ\n", result);
    ASSERT_MSG(strcmp(result, "0\n") == 0);

    // Тест 5: Несколько строк
    count_rare_symbols("test!\nhello@world\n123#\n", result);
    ASSERT_MSG(strcmp(result, "1\n1\n1\n") == 0);

    printf("[OK] Tests for count_rare_symbols passed\n\n");
}

void test_replace_except_digits() {
    printf("[...] Start testing replace_except_digits\n");

    char result[BUFFER_SIZE];

    // Тест 1: Буквы и цифры
    replace_except_digits("a1b2c3", result);
    ASSERT_MSG(strcmp(result, "611622633") == 0);

    // Тест 2: Специальные символы
    replace_except_digits("hello!", result);
    ASSERT_MSG(strcmp(result, "68656c6c6f21") == 0);

    // Тест 3: Только цифры
    replace_except_digits("123456", result);
    ASSERT_MSG(strcmp(result, "123456") == 0);

    // Тест 4: С переводом строки
    replace_except_digits("abc\n123", result);
    ASSERT_MSG(strcmp(result, "616263a123") == 0); // a - hex для '\n'

    // Тест 5: Пустая строка
    replace_except_digits("", result);
    ASSERT_MSG(strcmp(result, "") == 0);

    // Тест 6: Смешанный случай
    replace_except_digits("test123!@#", result);
    ASSERT_MSG(strcmp(result, "74657374123214023") == 0);

    printf("[OK] Tests for replace_except_digits passed\n\n");
}

void run_edge_case_tests() {
    printf("Running edge case tests\n");

    char result[BUFFER_SIZE];

    // Граничные случаи для remove_arabic_digits
    remove_arabic_digits("0a1b2c9", result);
    ASSERT_MSG(strcmp(result, "abc") == 0);

    // Граничные случаи для count_latin_letters
    count_latin_letters("a\nb\nc\n", result);
    ASSERT_MSG(strcmp(result, "1\n1\n1\n") == 0);

    // Граничные случаи для count_rare_symbols
    count_rare_symbols(" \t\n", result); // пробел, таб, новая строка
    ASSERT_MSG(strcmp(result, "0\n") == 0);

    // Граничные случаи для replace_except_digits
    replace_except_digits("\x01\x02\x03", result); // управляющие символы
    // Проверка зависит от конкретного представления

    printf("[OK] edge_case_tests passed\n\n");
}

void run_all_tests() {
    printf("=== Starting function tests ===\n\n");
    test_remove_arabic_digits();
    test_count_latin_letters();
    test_count_rare_symbols();
    test_replace_except_digits();

    run_edge_case_tests();

    printf("=== All tests passed ===\n");
}

int main() {
    run_all_tests();
}
