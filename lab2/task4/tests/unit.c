#include <string.h>
#include <math.h>

#include "assert_base.h"
#include "functions.h"

void test_standard_flags() {
    printf("=== Testing Standard Flags ===\n");

    // %d - integer
    {
        char buffer[] = "123 -456";
        int32_t a, b;
        int result = oversscanf(buffer, "%d %d", &a, &b);
        _ASSERT_MSG(result == 2, "Expected 2 conversions, got %d", result);
        _ASSERT_MSG(a == 123, "Expected 123, got %d", a);
        _ASSERT_MSG(b == -456, "Expected -456, got %d", b);
    }

    // %ld - long integer
    {
        char buffer[] = "123456789 -987654321";
        int64_t a, b;
        int result = oversscanf(buffer, "%ld %ld", &a, &b);
        _ASSERT_MSG(result == 2, "Expected 2 conversions, got %d", result);
        _ASSERT_MSG(a == 123456789L, "Expected 123456789, got %ld", a);
        _ASSERT_MSG(b == -987654321L, "Expected -987654321, got %ld", b);
    }

    // %lld - int64_t integer
    {
        char buffer[] = "9223372036854775807 -9223372036854775808";
        int64_t a, b;
        int result = oversscanf(buffer, "%lld %lld", &a, &b);
        _ASSERT_MSG(result == 2, "Expected 2 conversions, got %d", result);
        _ASSERT_MSG(a == 9223372036854775807LL, "Expected LLONG_MAX, got %lld", a);
    }

    // %f - float
    {
        char buffer[] = "2.2228 -2.718";
        float a, b;

        float eps = 1e-6;

        int result = oversscanf(buffer, "%f %f", &a, &b);
        _ASSERT_MSG(result == 2, "Expected 2 conversions, got %d", result);
        _ASSERT_MSG(fabs(a - 2.2228) < eps, "Expected ~3.14, got %f", a);
        _ASSERT_MSG(fabs(b - -2.718) < eps, "Expected ~-2.718, got %f", b);
    }

    // %lf - double
    {
        char buffer[] = "123.456 -789.012";
        double a, b;

        double eps = 1e-9;

        int result = oversscanf(buffer, "%lf %lf", &a, &b);
        _ASSERT_MSG(result == 2, "Expected 2 conversions, got %d", result);
        _ASSERT_MSG(fabs(a - 123.456) < eps, "Expected 123.456, got %lf", a);
        _ASSERT_MSG(fabs(b - -789.012) < eps, "Expected -789.012, got %lf", b);
    }

    // %u - unsigned integer
    {
        char buffer[] = "123 456";
        uint32_t a, b;
        int result = oversscanf(buffer, "%u %u", &a, &b);
        _ASSERT_MSG(result == 2, "Expected 2 conversions, got %d", result);
        _ASSERT_MSG(a == 123, "Expected 123, got %u", a);
        _ASSERT_MSG(b == 456, "Expected 456, got %u", b);
    }

    // %c - char
    {
        char buffer[] = "A b";
        char a, b;
        int result = oversscanf(buffer, "%c %c", &a, &b);
        _ASSERT_MSG(result == 2, "Expected 2 conversions, got %d", result);
        _ASSERT_MSG(a == 'A', "Expected 'A', got '%c'", a);
        _ASSERT_MSG(b == 'b', "Expected 'b', got '%c'", b);
    }

    // %s - string
    {
        char buffer[] = "hello world";
        char str1[20], str2[20];
        int result = oversscanf(buffer, "%s %s", str1, str2);
        _ASSERT_MSG(result == 2, "Expected 2 conversions, got %d", result);
        _ASSERT_MSG(strcmp(str1, "hello") == 0, "Expected 'hello', got '%s'", str1);
        _ASSERT_MSG(strcmp(str2, "world") == 0, "Expected 'world', got '%s'", str2);
    }
}

void test_roman_numbers() {
    printf("\n=== Testing Roman Numbers (%Ro) ===\n");

    // Basic Roman numerals
    {
        char buffer[] = "XIV VIII III";
        int64_t a, b, c;
        int result = oversscanf(buffer, "%Ro %Ro %Ro", &a, &b, &c);
        _ASSERT_MSG(result == 3, "Expected 3 conversions, got %d", result);
        _ASSERT_MSG(a == 14, "XIV should be 14, got %lld", a);
        _ASSERT_MSG(b == 8, "VIII should be 8, got %lld", b);
        _ASSERT_MSG(c == 3, "III should be 3, got %lld", c);
    }

    // Complex Roman numerals
    {
        char buffer[] = "MCMXC MDCLXVI";
        int64_t a, b;
        int result = oversscanf(buffer, "%Ro %Ro", &a, &b);
        _ASSERT_MSG(result == 2, "Expected 2 conversions, got %d", result);
        _ASSERT_MSG(a == 1990, "MCMXC should be 1990, got %lld", a);
        _ASSERT_MSG(b == 1666, "MDCLXVI should be 1666, got %lld", b);
    }

    // Negative Roman numerals
    {
        char buffer[] = "-XIV -V";
        int64_t a, b;
        int result = oversscanf(buffer, "%Ro %Ro", &a, &b);
        _ASSERT_MSG(result == 2, "Expected 2 conversions, got %d", result);
        _ASSERT_MSG(a == -14, "-XIV should be -14, got %lld", a);
        _ASSERT_MSG(b == -5, "-V should be -5, got %lld", b);
    }

    // Invalid Roman numerals
    {
        char buffer[] = "ABC XYZ";
        int64_t a, b;
        int result = oversscanf(buffer, "%Ro %Ro", &a, &b);
        _ASSERT_MSG(result == INVALID_ARG, "Expected INVALID_ARG, got %d", result);
    }
}

void test_zeckendorf_numbers() {
    printf("\n=== Testing Zeckendorf Numbers (%%Zr) ===\n");

    // Valid Zeckendorf representations
    {
        char buffer[] = "11 011 101011";
        uint64_t a, b, c;
        int result = oversscanf(buffer, "%Zr %Zr %Zr", &a, &b, &c);
        _ASSERT_MSG(result == 3, "Expected 3 conversions, got %d", result);
        _ASSERT_MSG(a == 1, "11 should be 1, got %llu", a);
        _ASSERT_MSG(b == 2, "011 should be 2, got %llu", b);
        _ASSERT_MSG(c == 12, "101011 should be 12, got %llu", c);
    }

    // Invalid Zeckendorf (consecutive 1s)
    {
        char buffer[] = "1 10000";
        uint64_t a, b;
        int result = oversscanf(buffer, "%Zr %Zr", &a, &b);
        _ASSERT_MSG(result == INVALID_ARG, "Expected INVALID_ARG for consecutive 1s, got %d", result);
    }

    // Invalid characters
    {
        char buffer[] = "1A2 10B";
        uint64_t a, b;
        int result = oversscanf(buffer, "%Zr %Zr", &a, &b);
        _ASSERT_MSG(result == INVALID_ARG, "Expected INVALID_ARG for non-digits, got %d", result);
    }
}

void test_custom_base() {
    printf("\n=== Testing Custom Base (%%Cv, %%CV) ===\n");

    // Lowercase base 16
    {
        char buffer[] = "ff 1a";
        int64_t a, b;
        int result = oversscanf(buffer, "%Cv %Cv", &a, 16, &b, 16);
        _ASSERT_MSG(result == 2, "Expected 2 conversions, got %d", result);
        _ASSERT_MSG(a == 255, "ff in base 16 should be 255, got %lld", a);
        _ASSERT_MSG(b == 26, "1a in base 16 should be 26, got %lld", b);
    }

    // Uppercase base 16
    {
        char buffer[] = "FF 1A";
        int64_t a, b;
        int result = oversscanf(buffer, "%CV %CV", &a, 16, &b, 16);
        _ASSERT_MSG(result == 2, "Expected 2 conversions, got %d", result);
        _ASSERT_MSG(a == 255, "FF in base 16 should be 255, got %lld", a);
        _ASSERT_MSG(b == 26, "1A in base 16 should be 26, got %lld", b);
    }

    // Invalid case (mixed case)
    {
        char buffer[] = "Ff Aa";
        int64_t a, b;
        int result = oversscanf(buffer, "%Cv %Cv", &a, 16, &b, 16);
        _ASSERT_MSG(result == INVALID_CASE, "Expected INVALID_CASE for mixed case, got %d", result);
    }

    // Different bases
    {
        char buffer[] = "111 777 zz";
        int64_t a, b, c;
        int result = oversscanf(buffer, "%Cv %Cv %Cv", &a, 2, &b, 8, &c, 36);
        _ASSERT_MSG(result == 3, "Expected 3 conversions, got %d", result);
        _ASSERT_MSG(a == 7, "111 in base 2 should be 7, got %lld", a);
        _ASSERT_MSG(b == 511, "777 in base 8 should be 511, got %lld", b);  // 7*64 + 7*8 + 7 = 511
        _ASSERT_MSG(c == 1295, "zz in base 36 should be 1295, got %lld", c); // 35*36 + 35 = 1295
    }
}

void test_error_conditions() {
    printf("\n=== Testing Error Conditions ===\n");

    // Invalid format specifier
    {
        char buffer[] = "test";
        int32_t a;
        int result = oversscanf(buffer, "%invalid", &a);
        _ASSERT_MSG(result == INVALID_ARG, "Expected INVALID_ARG for invalid format, got %d", result);
    }

    // NULL arguments
    {
        int result = oversscanf(NULL, "%d", NULL);
        _ASSERT_MSG(result == INVALID_ARG, "Expected INVALID_ARG for NULL args, got %d", result);
    }

    // Empty input
    {
        char buffer[] = "";
        int32_t a;
        int result = oversscanf(buffer, "%d", &a);
        _ASSERT_MSG(result == 0, "Expected 0 conversions for empty input, got %d", result);
    }
}

void test_file_operations() {
    printf("\n=== Testing File Operations ===\n");

    FILE* test_file = fopen("test_input.txt", "w+");
    if (test_file) {
        fprintf(test_file, "123 3.14 hello\nXIV 00001011\n");

        // перенос указателя на начало файла
        rewind(test_file);

        int32_t a;
        double b;
        char str[20];
        int64_t roman;
        uint64_t zeck;

        double eps = 1e-9;

        int result = overfscanf(test_file, "%d %lf %s", &a, &b, str);
        _ASSERT_MSG(result == 3, "Expected 3 conversions from file, got %d", result);
        _ASSERT_MSG(a == 123, "Expected 123 from file, got %d", a);
        _ASSERT_MSG(fabs(b - 3.14) < eps, "Expected 3.14 from file, got %lf", b);
        _ASSERT_MSG(strcmp(str, "hello") == 0, "Expected 'hello' from file, got '%s'", str);

        result = overfscanf(test_file, "%Ro %Zr", &roman, &zeck);
        _ASSERT_MSG(result == 2, "Expected 2 conversions from file, got %d", result);
        _ASSERT_MSG(roman == 14, "Expected XIV=14 from file, got %lld", roman);
        _ASSERT_MSG(zeck == 29, "Expected 00001011 from file, got %lld", zeck);

        fclose(test_file);
        remove("test_input.txt");
    }
}

void test_mixed_formats() {
    printf("\n=== Testing Mixed Formats ===\n");

    // Complex mixed format string
    {
        char buffer[] = "123 3.14 hello XIV 10011 FF 16";
        int32_t a;
        double b;
        char str[20];
        int64_t roman;
        uint64_t zeck;
        int64_t hex;

        double eps = 1e-9;

        int result = oversscanf(buffer, "%d %lf %s %Ro %Zr %CV",
                               &a, &b, str, &roman, &zeck, &hex, 16);
        _ASSERT_MSG(result == 6, "Expected 6 conversions, got %d", result);
        _ASSERT_MSG(a == 123, "Expected 123, got %d", a);
        _ASSERT_MSG(fabs(b - 3.14) < eps, "Expected 3.14, got %lf", b);
        _ASSERT_MSG(strcmp(str, "hello") == 0, "Expected 'hello', got '%s'", str);
        _ASSERT_MSG(roman == 14, "Expected XIV=14, got %lld", roman);
        _ASSERT_MSG(zeck == 6, "Excepted 10011, got %llu", zeck);
        _ASSERT_MSG(hex == 255, "Expected FF=255, got %lld", hex);
    }
}

void test_shift_formats() {
    printf("\n=== Testing Shift Formats ===\n");

    {
        char buff[] = "      123    \n     \n\t \n   321   ";
        int32_t a, b;
        int result = oversscanf(buff, "%d %d", &a, &b);
        _ASSERT_MSG(result == 2, "Expected 2 conversions, got %d", result);
        _ASSERT_MSG(a == 123, "Expected 123, got %d", a);
        _ASSERT_MSG(b == 321, "Expected 321, got %d", b);
    }

    FILE* test_file = fopen("test_input.txt", "w+");
    if (test_file) {
        fprintf(test_file, "  \n    A   \n  0.025  \t  \n\n LII    aboba \n \n");

        rewind(test_file);

        char c;
        double f;
        int64_t roman;
        char str[20];

        double eps = 1e-9;

        int result = overfscanf(test_file, "%c %lf %Ro %s", &c, &f, &roman, &str);
        _ASSERT_MSG(result == 4, "Expected 4 conversions, got %d", result);
        _ASSERT_MSG(c == 'A', "Expected 'A', got %c", c);
        _ASSERT_MSG(fabs(f - 0.025) < eps, "Expected 0.025, got %lf", f);
        _ASSERT_MSG(roman == 52, "Expected 52, got %ld", roman);
        _ASSERT_MSG(strcmp(str, "aboba") == 0, "Expected aboba, got %s", str);

        fclose(test_file);
        remove("test_input.txt");
    }
}

int main() {
    printf("Starting comprehensive tests...\n");

    test_standard_flags();
    test_roman_numbers();
    test_zeckendorf_numbers();
    test_custom_base();
    test_error_conditions();
    test_file_operations();
    test_mixed_formats();
    test_shift_formats();

    printf("\n=== ALL TESTS PASSED! ===\n");
    return 0;
}
