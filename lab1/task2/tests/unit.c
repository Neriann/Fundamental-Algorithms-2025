#include "assert_base.h"
#include "primes/functions.h"

void test_find_nth_prime(const PrimeNumbers* primes) {
    printf("[...] Testing find_nth_prime\n");

    ASSERT_MSG(find_nth_prime(-1, primes).code == UNNATURAL_NUMBER);
    ASSERT_MSG(find_nth_prime(1, primes).value == 2);
    ASSERT_MSG(find_nth_prime(2, primes).value == 3);
    ASSERT_MSG(find_nth_prime(3, primes).value == 5);
    ASSERT_MSG(find_nth_prime(100, primes).value == 541);
    ASSERT_MSG(find_nth_prime(5e6, primes).value == 86028121);
    ASSERT_MSG(find_nth_prime(6e6, primes).code == TOO_BIG_NUMBER);

    printf("[OK] Tests for find_nth_prime are accepted\n\n");}

void run_all_tests() {

    PrimeNumbers primes = {NULL, 0};
    generate_primes(&primes);

    test_find_nth_prime(&primes);
    printf("All tests passed!\n");
}

int main() {
    run_all_tests();
}
