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
    }
    else {
        int8_t is_flag_t = strcmp(flag, "-t") == 0 || strcmp(flag, "/t") == 0;
        int8_t is_flag_q = strcmp(flag, "-q") == 0 || strcmp(flag, "/q") == 0;
        if (!is_flag_t && !is_flag_q) {
            printf("This flag isn't defined\n");
            return 1;
        }
        else {
            if (argc < 6) {
                printf("Not enough arguments for this flag\n");
                return 1;
            }
            const double epsilon = string_to_double(argv[2]);
            const double a = string_to_double(argv[3]);
            const double b = string_to_double(argv[4]);
            const double c = string_to_double(argv[5]);

            Solution result = {};
            Solution cache[6];
            size_t cache_size = 0;
            double permutations[6][3] = {{a, b, c}, {a, c, b}, {b, a, c}, {b, c, a}, {c, a, b}, {c, b, a}};
            if (is_flag_q) {
                for (size_t i = 0; i < 6; ++i) {
                    result = get_solution_to_equation(epsilon, permutations[i][0], permutations[i][1], permutations[i][2]);
                    uint8_t find = 0;
                    for (size_t j = 0; j < cache_size; ++j) {
                        if (cache[j].type == result.type && cache[j].x1 == result.x1 && cache[j].x2 == result.x2 && cache[j].re == result.re && cache[j].im == result.im) {
                            find = 1;
                            break;
                        }
                    }
                    if (!find) {
                        cache[cache_size++] = result;
                        print_solution_to_equation(&result, epsilon, permutations[i][0], permutations[i][1], permutations[i][2]);
                    }
                }
            } else {
                int8_t find = 0;
                size_t i = 0;
                for (; i < 6; ++i) {
                    if ((find = is_rectangle(epsilon, permutations[i][0], permutations[i][1], permutations[i][2]))) {
                        break;
                    }
                }
                if (find) {
                    printf("There is a rectangle with sides a = %lf, b = %lf, c = %lf\n", permutations[i][0], permutations[i][1], permutations[i][2]);
                }
                else {
                    printf("There is no a rectangle with sides a = %lf, b = %lf, c = %lf\n", permutations[0][0], permutations[0][1], permutations[0][2]);
                }
            }
        }
    }
    return 0;
}
