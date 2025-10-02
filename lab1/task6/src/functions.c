#include <math.h>

#include "double_calculations/functions.h"
#include "functions.h"


double calculate_integral(double a, double b, double epsilon, double (*func)(double)) {
    double sum = 0.0;
    double dx = (b - a) * epsilon;
    double n = (b - a) / epsilon; // количество разбиений

    double x1 = a, x2 = a + dx;
    double y1, y2;
    for (int i = 0; i < n; ++i) {
        y1 = func(x1);
        y2 = func(x2);
        if (!isnan(y1) && !isnan(y2) && !isinf(y1) && !isinf(y2)) {
            sum += (func(x1) + func(x2)) / 2 * dx;
        }
        x1 += dx;
        x2 += dx;
    }
    return sum;
}

double func_a(double x) {
    return log(1.0 + x) / x;
}

double func_b(double x) {
    return exp(-x * x / 2.0);
}

double func_c(double x) {
    return log(1.0 / (1.0 - x));
}

double func_d(double x) {
    return pow(x, x);
}
