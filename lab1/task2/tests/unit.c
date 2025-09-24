#include "assert_base.h"
#include "functions.h"

void test_find_nth_prime() {
    printf("[...] Testing find_nth_prime\n");
    ASSERT_MSG(find_nth_prime(-1) == UNNATURAL_NUMBER);
    ASSERT_MSG(find_nth_prime(1) == 2);
    ASSERT_MSG(find_nth_prime(2) == 3);
    ASSERT_MSG(find_nth_prime(3) == 5);
    ASSERT_MSG(find_nth_prime(100) == 541);
    ASSERT_MSG(find_nth_prime(5e6) == 86028121);
    ASSERT_MSG(find_nth_prime(6e6) == TOO_BIG_NUMBER);

    printf("[OK] Tests for find_nth_prime are accepted\n\n");}

void run_all_tests() {
    test_find_nth_prime();
    printf("All tests passed!\n");
}

int main() {
    run_all_tests();
}
