#include "assert_base.h"

// #include "primes/functions.h"
#include "approximate_values/functions.h"
#include "approximate_values/constants.h"


void test_get_exponent_from_limit() {
    printf("[...] Testing get_exponent_from_limit\n");
    long double e = get_exponent_from_limit(1e-1);
    ASSERT_MSG(my_abs(e - EXP) < 1e-1);

    e = get_exponent_from_limit(1e-5);
    ASSERT_MSG(my_abs(e - EXP) < 1e-5);

    e = get_exponent_from_limit(1e-12);
    ASSERT_MSG(my_abs(e - EXP) < 1e-12);
    printf("[OK] Tests for get_exponent_from_limit are accepted\n\n");
}

void test_get_exponent_from_row() {
    printf("[...] Testing get_exponent_from_row\n");
    long double e = get_exponent_from_row(1e-1);
    ASSERT_MSG(my_abs(e - EXP) < 1e-1);

    e = get_exponent_from_row(1e-5);
    ASSERT_MSG(my_abs(e - EXP) < 1e-5);

    e = get_exponent_from_row(1e-12);
    ASSERT_MSG(my_abs(e - EXP) < 1e-12);
    printf("[OK] Tests for get_exponent_from_row are accepted\n\n");
}


void test_get_pi_from_limit() {
    printf("[...] Testing get_pi_from_limit\n");
    long double pi = get_pi_from_limit(1e-1);
    ASSERT_MSG(my_abs(pi - PI) < 1e-1);

    pi = get_pi_from_limit(1e-5);
    ASSERT_MSG(my_abs(pi - PI) < 1e-5);

    pi = get_pi_from_limit(1e-8);
    ASSERT_MSG(my_abs(pi - PI) < 1e-8);
    printf("[OK] Tests for get_pi_from_limit are accepted\n\n");
}

void test_get_pi_from_row() {
    printf("[...] Testing get_pi_from_row\n");
    long double pi = get_pi_from_row(1e-1);
    ASSERT_MSG(my_abs(pi - PI) < 1e-1);

    pi = get_pi_from_row(1e-5);
    ASSERT_MSG(my_abs(pi - PI) < 1e-5);

    pi = get_pi_from_row(1e-8);
    ASSERT_MSG(my_abs(pi - PI) < 1e-8);
    printf("[OK] Tests for get_pi_from_row are accepted\n\n");
}

void test_get_ln2_from_limit() {
    printf("[...] Testing get_ln2_from_limit\n");
    long double ln2 = get_ln2_from_limit(1e-1);
    ASSERT_MSG(my_abs(ln2 - LN_2) < 1e-1);

    ln2 = get_ln2_from_limit(1e-5);
    ASSERT_MSG(my_abs(ln2 - LN_2) < 1e-5);

    ln2 = get_ln2_from_limit(1e-8);
    ASSERT_MSG(my_abs(ln2 - LN_2) < 1e-8);
    printf("[OK] Tests for get_ln2_from_limit are accepted\n\n");
}

void test_get_ln2_from_row() {
    printf("[...] Testing get_ln2_from_row\n");
    long double ln2 = get_ln2_from_row(1e-1);
    ASSERT_MSG(my_abs(ln2 - LN_2) < 1e-1);

    ln2 = get_ln2_from_row(1e-5);
    ASSERT_MSG(my_abs(ln2 - LN_2) < 1e-5);

    ln2 = get_ln2_from_row(1e-8);
    ASSERT_MSG(my_abs(ln2 - LN_2) < 1e-8);
    printf("[OK] Tests for get_ln2_from_row are accepted\n\n");
}

void test_get_sqrt2_from_limit() {
    printf("[...] Testing get_sqrt2_from_limit\n");
    long double sqrt2 = get_sqrt2_from_limit(1e-1);
    ASSERT_MSG(my_abs(sqrt2 - SQRT_2) < 1e-1);

    sqrt2 = get_sqrt2_from_limit(1e-5);
    ASSERT_MSG(my_abs(sqrt2 - SQRT_2) < 1e-5);

    sqrt2 = get_sqrt2_from_limit(1e-8);
    ASSERT_MSG(my_abs(sqrt2 - SQRT_2) < 1e-8);
    printf("[OK] Tests for get_sqrt2_from_limit are accepted\n\n");

}

void test_get_sqrt2_from_row() {
    printf("[...] Testing get_sqrt2_from_row\n");
    long double sqrt2 = get_sqrt2_from_row(1e-1);
    ASSERT_MSG(my_abs(sqrt2 - SQRT_2) < 1e-1);

    sqrt2 = get_sqrt2_from_row(1e-5);
    ASSERT_MSG(my_abs(sqrt2 - SQRT_2) < 1e-5);

    sqrt2 = get_sqrt2_from_row(1e-8);
    ASSERT_MSG(my_abs(sqrt2 - SQRT_2) < 1e-8);
    printf("[OK] Tests for get_sqrt2_from_row are accepted\n\n");
}

void test_get_gamma_from_limit() {
    printf("[...] Testing gamma_from_limit\n");

    long double gamma = get_gamma_from_limit(1e-1);
    ASSERT_MSG(my_abs(gamma - EULER_MASCHERONI) < 1e-1);

    gamma = get_gamma_from_limit(1e-3);
    ASSERT_MSG(my_abs(gamma - EULER_MASCHERONI) < 1e-3);

    printf("[OK] Tests for get_gamma_from_limit are accepted\n\n");
}


void test_get_gamma_from_row() {
    printf("[...] Testing gamma_from_row\n");

    long double gamma = get_gamma_from_row(1e-1);
    ASSERT_MSG(my_abs(gamma - EULER_MASCHERONI) < 1e-1);

    gamma = get_gamma_from_row(1e-3);
    ASSERT_MSG(my_abs(gamma - EULER_MASCHERONI) < 1e-3);

    gamma = get_gamma_from_row(1e-4);
    ASSERT_MSG(my_abs(gamma - EULER_MASCHERONI) < 1e-4);

    printf("[OK] Tests for get_gamma_from_row are accepted\n\n");
}

void test_get_gamma_from_equation() {
    printf("[...] Testing gamma_from_equation\n");

    PrimeNumbers prime_numbers = {NULL, 0};
    Code code = generate_primes(&prime_numbers);
    ASSERT_MSG(code == SUCCESS);

    long double gamma = get_gamma_from_equation(1e-1, &prime_numbers);
    ASSERT_MSG(my_abs(gamma - EULER_MASCHERONI) < 1e-1);

    gamma = get_gamma_from_equation(1e-3, &prime_numbers);
    ASSERT_MSG(my_abs(gamma - EULER_MASCHERONI) < 1e-3);

    gamma = get_gamma_from_equation(1e-5, &prime_numbers);
    ASSERT_MSG(my_abs(gamma - EULER_MASCHERONI) < 1e-5);
    printf("[OK] Tests for get_gamma_from_row are accepted\n\n");
}


void run_all_tests() {
    test_get_exponent_from_limit();
    test_get_exponent_from_row();

    test_get_pi_from_limit();
    test_get_pi_from_row();

    test_get_ln2_from_limit();
    test_get_ln2_from_row();

    test_get_sqrt2_from_limit();
    test_get_sqrt2_from_row();

    test_get_gamma_from_limit();
    test_get_gamma_from_row();
    test_get_gamma_from_equation();

    printf("===All tests passed===\n");
}

int main() {
    run_all_tests();
}
