#include <string.h>

#include "functions.h"
#include "assert_base.h"


void test_to_power_of_two_system() {
    char buff[64];
    char* result;
    size_t result_size;
    Code code;

    // === Test 1: Base 16 ===
    int64_t num = 255, base = 16;
    code = to_power_of_two_system(&result, &result_size, buff, sizeof(buff), num, base);
    _ASSERT_MSG(code == SUCCESS, "code: %d", code);
    _ASSERT_MSG(strcmp(result, "FF") == 0, "result with num=%ld, base=%ld: %s", num, base, result);
    _ASSERT_MSG(result_size == strlen(result), "result size mismatch");

    // === Test 2: Base 2 ===
    num = 13; base = 2;
    code = to_power_of_two_system(&result, &result_size, buff, sizeof(buff), num, base);
    _ASSERT_MSG(code == SUCCESS, "code: %d", code);
    _ASSERT_MSG(strcmp(result, "1101") == 0, "binary result with num=%ld: %s", num, result);
    _ASSERT_MSG(result_size == strlen(result), "result size mismatch");

    // === Test 3: Base 8 ===
    num = 64; base = 8;
    code = to_power_of_two_system(&result, &result_size, buff, sizeof(buff), num, base);
    _ASSERT_MSG(code == SUCCESS, "code: %d", code);
    _ASSERT_MSG(strcmp(result, "100") == 0, "octal result with num=%ld: %s", num, result);
    _ASSERT_MSG(result_size == strlen(result), "result size mismatch");

    // === Test 4: Zero ===
    num = 0; base = 8;
    code = to_power_of_two_system(&result, &result_size, buff, sizeof(buff), num, base);
    _ASSERT_MSG(code == SUCCESS, "code: %d", code);
    _ASSERT_MSG(strcmp(result, "0") == 0, "result for zero: %s", result);
    _ASSERT_MSG(result_size == 1, "result size mismatch for zero");

    // === Test 5: Negative number ===
    num = -15; base = 16;
    code = to_power_of_two_system(&result, &result_size, buff, sizeof(buff), num, base);
    _ASSERT_MSG(code == SUCCESS, "code: %d", code);
    _ASSERT_MSG(strcmp(result, "-F") == 0, "result with num=%ld, base=%ld: %s", num, base, result);
    _ASSERT_MSG(result_size == strlen(result), "result size mismatch");

    // === Test 6: Large number ===
    num = 1023; base = 2;
    code = to_power_of_two_system(&result, &result_size, buff, sizeof(buff), num, base);
    _ASSERT_MSG(code == SUCCESS, "code: %d", code);
    _ASSERT_MSG(strcmp(result, "1111111111") == 0, "result for num=%ld: %s", num, result);
    _ASSERT_MSG(result_size == strlen(result), "result size mismatch");

    // === Test 7: Invalid base (not power of two) ===
    num = 10; base = 3;
    code = to_power_of_two_system(&result, &result_size, buff, sizeof(buff), num, base);
    _ASSERT_MSG(code == INVALID_BASE, "expected INVALID_BASE for base=%ld, got: %d", base, code);

    // === Test 8: Base 32 ===
    num = 255; base = 32;
    code = to_power_of_two_system(&result, &result_size, buff, sizeof(buff), num, base);
    _ASSERT_MSG(code == SUCCESS, "code: %d", code);
    _ASSERT_MSG(strcmp(result, "7V") == 0, "result for base 32: %s", result);
    _ASSERT_MSG(result_size == strlen(result), "result size mismatch");

    printf("✅ All to_power_of_two_system() tests passed successfully.\n");
}


void run_all_tests() {
    test_to_power_of_two_system();
}

int main() {
    run_all_tests();
}
