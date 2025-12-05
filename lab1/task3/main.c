#include <stdio.h>
#include <string.h>

#include "double_calculations/functions.h"


int main(const int argc, const char* argv[]) {
    if (argc < 2) {
        printf("Specify the flag and set the parameters for it");
        return 1;
    }
    const char* flag = argv[1];
    if (strcmp(flag, "-m") == 0 || strcmp(flag, "/m") == 0) {
        if (argc < 4) {
            printf("Not enough arguments for this flag\n");
            return 1;
        }
        const int64_t num1 = string_to_int(argv[2], 10);
        const int64_t num2 = string_to_int(argv[3], 10);
        if (is_divisible_by(num1, num2)) {
            printf("The number %ld is divisible by %ld\n", num1, num2);
        }
        else {
            printf("The number %ld is not divisible by %ld\n", num1, num2);
        }
        return 0;
    }
    int8_t is_flag_t = strcmp(flag, "-t") == 0 || strcmp(flag, "/t") == 0;
    int8_t is_flag_q = strcmp(flag, "-q") == 0 || strcmp(flag, "/q") == 0;
    if (!is_flag_t && !is_flag_q) {
        printf("This flag isn't defined\n");
        return 1;
    }
    if (argc < 6) {
        printf("Not enough arguments for this flag\n");
        return 1;
    }
    const double epsilon = string_to_double(argv[2]);
    const double a = string_to_double(argv[3]);
    const double b = string_to_double(argv[4]);
    const double c = string_to_double(argv[5]);

    Solution result = {};
    Permutation cache[6];
    size_t cache_size = 0;
    double permutations[6][3] = {{a, b, c}, {a, c, b}, {b, a, c}, {b, c, a}, {c, a, b}, {c, b, a}};
    if (is_flag_q) {
        for (size_t i = 0; i < 6; ++i) {
            result = get_solution_to_equation(epsilon, permutations[i][0], permutations[i][1], permutations[i][2]);
            uint8_t find = 0;
            for (size_t j = 0; j < cache_size; ++j) {
                if (cache[j].a == permutations[i][0] && cache[j].b == permutations[i][1] && cache[j].c ==
                    permutations[i][2]) {
                    find = 1;
                    break;
                }
            }
            if (!find) {
                cache[cache_size].a = permutations[i][0];
                cache[cache_size].b = permutations[i][1];
                cache[cache_size].c = permutations[i][2];
                ++cache_size;
                print_solution_to_equation(&result, epsilon, permutations[i][0], permutations[i][1],
                                           permutations[i][2]);
            }
        }
    }
    else if (is_flag_t) {
        Code code = 0;
        size_t i = 0;
        for (; i < 6; ++i) {
            if ((code = is_rectangle(epsilon, permutations[i][0], permutations[i][1], permutations[i][2]))) {
                break;
            }
        }
        if (code == NEGATIVE_SIDES) {
            printf("The sides should not be negative\n");
        }
        else if (code == IS_NOT_TRIANGLE) {
            printf("There is not a triangle with sides a = %lf, b = %lf, c = %lf\n", permutations[i][0],
                   permutations[i][1], permutations[i][2]);
        }
        else if (code == IS_RECTANGLE) {
            printf("There is a rectangle with sides a = %lf, b = %lf, c = %lf\n", permutations[i][0],
                   permutations[i][1], permutations[i][2]);
        }
        else {
            printf("There is not a rectangle with sides a = %lf, b = %lf, c = %lf\n", permutations[0][0],
                   permutations[0][1], permutations[0][2]);
        }
    }

    return 0;
}
