#include <math.h>

#include "double_calculations/functions.h"
#include "functions.h"


double calculate_integral(double a, double b, double epsilon, double (*func)(double)) {
    double dx = 1, prev_sum, curr_sum = 0;
    do {
        prev_sum = curr_sum;
        curr_sum = 0;
        for (double i = a, j = a + dx; j <= b; i += dx, j += dx) {
            curr_sum += (func(i) + func(j)) / 2 * (j - i);
        }
        dx /= 2;
    } while (my_abs(prev_sum - curr_sum) >= epsilon || my_abs(curr_sum) < epsilon);
    return curr_sum;
}

double func_a(double x) {
    if (x == 0) return 0;
    return log(1.0 + x) / x;
}

double func_b(double x) {
    return exp(-x * x / 2.0);
}

double func_c(double x) {
    if (x == 1.0) return 0;
    return log(1.0 / (1.0 - x));
}

double func_d(double x) {
    return pow(x, x);
}
