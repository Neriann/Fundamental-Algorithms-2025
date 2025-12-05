// #include <string.h>
//
// #include "assert_base.h"
// #include "functions.h"
//
//
// void test_string_to_int() {
//     printf("[...] Testing string_to_int\n");
//     ASSERT_MSG(string_to_int("1234", 10) == 1234)
//     ASSERT_MSG(string_to_int("0", 10) == 0)
//     ASSERT_MSG(string_to_int("9999", 10) == 9999)
//
//     ASSERT_MSG(string_to_int("101", 2) == 5)
//
//     printf("[OK] Tests for string_to_int are accepted\n\n");
// }
//
// void test_int_to_string() {
//     printf("[...] Testing int_to_string\n");
//
//     char buf[32];
//     char* res;
//
//     res = int_to_string(0, 10, buf + 32);
//     ASSERT_MSG(strcmp(res, "0") == 0);
//
//     res = int_to_string(123, 10, buf + 32);
//     ASSERT_MSG(strcmp(res, "123") == 0);
//
//     res = int_to_string(255, 16, buf + 32);
//     ASSERT_MSG(strcmp(res, "FF") == 0);
//     printf("[OK] Tests for int_to_string are accepted\n\n");
// }
//
//
// void test_get_sum() {
//     printf("[...] Testing get_sum\n");
//     int64_t sum = get_sum(123);
//     ASSERT_MSG(sum == 7626);
//
//     sum = get_sum(1000000000);
//     ASSERT_MSG(sum == 500000000500000000);
//
//     sum = get_sum(10000000000);
//     ASSERT_MSG(sum == OVERFLOW_NUMBER)
//
//     sum = get_sum(-1);
//     ASSERT_MSG(sum == NEGATIVE_NUMBER)
//
//     sum = get_sum(0);
//     ASSERT_MSG(sum == ZERO_NUMBER)
//     printf("[OK] Tests for get_sum are accepted\n\n");
// }
//
// void test_get_fact() {
//     printf("[...] Testing get_fact\n");
//     int64_t fact = get_fact(5);
//     ASSERT_MSG(fact == 120);
//
//     fact = get_fact(20);
//     ASSERT_MSG(fact == 2432902008176640000);
//
//     fact = get_fact(0);
//     ASSERT_MSG(fact == 1);
//
//     fact = get_fact(21);
//     ASSERT_MSG(fact == OVERFLOW_NUMBER)
//
//     fact = get_fact(-1);
//     ASSERT_MSG(fact == NEGATIVE_NUMBER)
//
//     printf("[OK] Tests for get_fact are accepted\n\n");
// }
//
// void test_is_prime() {
//     printf("[...] Testing is_prime\n");
//     ASSERT_MSG(is_prime(-1000) == UNNATURAL_NUMBER);
//     ASSERT_MSG(is_prime(0) == UNNATURAL_NUMBER);
//     ASSERT_MSG(is_prime(1) == SPECIFIC_NUMBER);
//     ASSERT_MSG(is_prime(2) == PRIME_NUMBER);
//     ASSERT_MSG(is_prime(9) == COMPOSITE_NUMBER);
//     ASSERT_MSG(is_prime(869) == COMPOSITE_NUMBER);
//     ASSERT_MSG(is_prime(1e9 + 7) == PRIME_NUMBER);
//     printf("[OK] Tests for is_prime are accepted\n\n");
// }
//
// void test_get_hex_num() {
//     printf("[...] Testing get_hex\n");
//     char buff[MAX_SIZE];
//     char* p = buff + MAX_SIZE - 1;
//     *p-- = 0;
//     char* str = "-255";
//     char* res = get_hex_num(str, p);
//     ASSERT_MSG(strcmp(res, "-FF") == 0)
// }
//
// void run_all_tests() {
//     test_string_to_int();
//     test_int_to_string();
//     test_get_sum();
//     test_get_fact();
//     test_is_prime();
//     test_get_hex_num();
//
//     printf("All tests passed!\n");
// }
//
int main() {
    // run_all_tests();
    return 0;
}
