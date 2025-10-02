#include <stdio.h>

#include "double_calculations/functions.h"

#include "functions.h"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s [epsilon]\n", argv[0]);
        return 1;
    }
    const double eps = string_to_double(argv[1]);
    double res_func_a = calculate_integral(0, 1, eps, func_a);
    double res_func_b = calculate_integral(0, 1, eps, func_b);
    double res_func_c = calculate_integral(0, 1, eps, func_c);
    double res_func_d = calculate_integral(0, 1, eps, func_d);
    printf("%.12lf\n%.12lf\n%.12lf\n%.12lf\n", res_func_a, res_func_b, res_func_c, res_func_d);
}
