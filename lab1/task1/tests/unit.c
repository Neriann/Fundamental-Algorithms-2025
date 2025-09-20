#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "functions.h"


#define ASSERT_MSG(expr) \
if (!(expr)) { \
    fprintf(stderr, "[FAIL] Assertion failed: %s\nFile: %s, Line: %d\n", \
            #expr, __FILE__, __LINE__); \
    exit(EXIT_FAILURE); \
} else { \
    fprintf(stdout, "[OK] Test was (%s) successful\n", #expr); \
}


void test_string_to_int() {
    printf("[...] Testing string_to_int\n");
    ASSERT_MSG(string_to_int("1234", 10) == 1234)
    ASSERT_MSG(string_to_int("0", 10) == 0)
    ASSERT_MSG(string_to_int("9999", 10) == 9999)

    ASSERT_MSG(string_to_int("101", 2) == 5)

    printf("[OK] Tests for string_to_int are accepted\n\n");
}

void test_int_to_string() {
    printf("[...] Testing int_to_string\n");

    char buf[32];
    char* res;

    res = int_to_string(0, 10, buf + 32);
    ASSERT_MSG(strcmp(res, "0") == 0);

    res = int_to_string(123, 10, buf + 32);
    ASSERT_MSG(strcmp(res, "123") == 0);

    res = int_to_string(255, 16, buf + 32);
    ASSERT_MSG(strcmp(res, "FF") == 0);
    printf("[OK] Tests for int_to_string are accepted\n\n");
}

void test_add() {
    printf("[...] Testing add\n");
    char res[1025];
    add("123", "456", res);
    ASSERT_MSG(strcmp(res, "579") == 0);

    add("999", "1", res);
    ASSERT_MSG(strcmp(res, "1000") == 0);
    printf("[OK] Tests for add are accepted\n\n");
}

void test_mul_one_digit() {
    printf("[...] Testing multiply_one_digit\n");
    char res[1025];
    mul_one_digit("123", 4, res);
    ASSERT_MSG(strcmp(res, "492") == 0);
    printf("[OK] Tests for multiply_one_digit are accepted\n\n");
}

void test_multiply() {
    printf("[...] Testing multiply\n");
    char res[1025] = "0";
    multiply("123", "456", res);
    ASSERT_MSG(strcmp(res, "56088") == 0);

    strcpy(res, "0");
    multiply("0", "999", res);
    ASSERT_MSG(strcmp(res, "0") == 0);
    printf("[OK] Tests for multiply are accepted\n\n");
}

void test_divide_by_digit() {
    printf("[...] Testing divide by a digit\n");
    char res[1025];
    int64_t rem = divide_by_digit("123", '2', res);
    ASSERT_MSG(rem == 1);
    ASSERT_MSG(strcmp(res, "61") == 0);

    rem = divide_by_digit("10", '0', res); // деление на 0
    ASSERT_MSG(strcmp(res, "inf") == 0);
    printf("[OK] Tests for divide by a digit are accepted\n\n");
}

void test_get_sum() {
    printf("[...] Testing get_sum\n");
    char* sum = get_sum("123");
    ASSERT_MSG(sum != NULL && strcmp(sum, "7626") == 0); // пример с формулой n*(n+1)/2
    free(sum);

    sum = get_sum("10000000000");
    ASSERT_MSG(sum != NULL && strcmp(sum, "50000000005000000000") == 0);
    printf("[OK] Tests for get_sum are accepted\n\n");
}

void test_get_fact() {
    printf("[...] Testing get_fact\n");
    char* fact = get_fact(5);
    ASSERT_MSG(fact != NULL && strcmp(fact, "120") == 0);
    free(fact);

    fact = get_fact(30);
    ASSERT_MSG(fact != NULL && strcmp(fact, "265252859812191058636308480000000") == 0);
    free(fact);
    printf("[OK] Tests for get_fact are accepted\n\n");
}

void test_is_prime() {
    printf("[...] Testing is_prime\n");
    ASSERT_MSG(is_prime(1) == SPECIFIC_NUMBER);
    ASSERT_MSG(is_prime(2) == PRIME_NUMBER);
    ASSERT_MSG(is_prime(9) == COMPOSITE_NUMBER);
    ASSERT_MSG(is_prime(869) == COMPOSITE_NUMBER);
    ASSERT_MSG(is_prime(1e9 + 7) == PRIME_NUMBER);
    printf("[OK] Tests for is_prime are accepted\n\n");
}

void run_all_tests() {
    test_string_to_int();
    test_int_to_string();
    test_add();
    test_mul_one_digit();
    test_multiply();
    test_divide_by_digit();
    test_get_sum();
    test_get_fact();
    test_is_prime();

    printf("All tests passed!\n");
}

int main() {
    run_all_tests();
    return 0;
}
