#include <stdio.h>
#include <string.h>

#include "functions.h"

#define IS_FLAG_Q (strcmp(flag, "-q") == 0 || strcmp(flag, "/q") == 0)
#define IS_FLAG_M (strcmp(flag, "-M") == 0 || strcmp(flag, "/M") == 0)
#define IS_FLAG_T (strcmp(flag, "-t") == 0 || strcmp(flag, "/t") == 0)

int main(const int argc, const char* argv[]) {
    if (argc < 2) {
        printf("Specify the flag and set the parameters for it");
        return 1;
    }
    const char* flag = argv[1];
    if (IS_FLAG_M) {
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
        int8_t is_flag_t = IS_FLAG_T;
        int8_t is_flag_q = IS_FLAG_Q;
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
            size_t i = 0;

            Solution result = {};
            double permutation[] = {a, b, c};
            if (is_flag_q) {
                do {
                    result = get_solution_to_equation(epsilon, permutation[0], permutation[1], permutation[2]);
                    print_solution_to_equation(&result, epsilon, permutation[0], permutation[1], permutation[2]);
                    swap(&permutation[i % 3], &permutation[(i + 1) % 3]);
                }
                while (++i != 6);
            } else {
                int8_t find = 0;
                do {
                    if ((find = is_rectangle(epsilon, permutation[0], permutation[1], permutation[2]))) {
                        break;
                    }
                    swap(&permutation[i % 3], &permutation[(i + 1) % 3]);
                }
                while (++i != 6);
                if (find) {
                    printf("There is a rectangle with sides a = %lf, b = %lf, c = %lf\n", permutation[0], permutation[1], permutation[2]);
                }
                else {
                    printf("There is no a rectangle with sides a = %lf, b = %lf, c = %lf\n", permutation[0], permutation[1], permutation[2]);
                }
            }
        }
    }
    return 0;
}
