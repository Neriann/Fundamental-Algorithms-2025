#include "functions.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double string_to_double(const char* str) {
    double integer_part = 0;
    double fractional_part = 0;
    size_t i = 0;
    int8_t mul = 1;
    if (str[i] == '-') {
        mul = -1;
        ++i;
    }
    while (str[i] != '.' && str[i] != '\0') {
        integer_part = 10 * integer_part + str[i++] - '0';
    }
    if (str[i] == '\0') {
        return mul * integer_part; // если введено число без точки
    }
    size_t len = strlen(str);

    i = len - 1;
    while (str[i] != '.') {
        fractional_part = 0.1 * (fractional_part + (str[i--] - '0'));
    }
    return mul * (integer_part + fractional_part);
}

void swap(double* a, double* b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

double my_abs(const double x) {
    return x < 0 ? -x : x;
}

Solution get_solution_to_equation(const double eps, const double a, const double b, const double c) {
    // ax^2 + bx + c = 0
    Solution result = {};

    if (a < eps && b < eps && c < eps) {
        result.type = INFINITE_SOLUTIONS;
        return result;
    }
    else if (a < eps && b < eps) {
        result.type = ZERO_SOLUTIONS;
        return result;
    }
    else if (a < eps) {
        result.type = ONE_REAL_SOLUTION;
        result.x1 = result.x2 = -c / b;
        return result;
    }

    double D = b * b - 4 * a * c;
    if (D < -eps) {
        result.type = TWO_COMPLEX_SOLUTIONS;
        result.re = -b / (2 * a);
        result.im = sqrt(-D) / (2 * a);
        return result;
    }
    else if (D < eps) {
        result.type = ONE_REAL_SOLUTION;
        result.x1 = -b / (2 * a);
    }
    else {
        result.type = TWO_REAL_SOLUTIONS;
        double sqrt_D = sqrt(D);
        result.x1 = (-b + sqrt_D) / (2 * a);
        result.x2 = (-b - sqrt_D) / (2 * a);
    }
    return result;
}


void print_solution_to_equation(Solution* res, const double eps, const double a, const double b, const double c) {
    switch (res->type) {

    case INFINITE_SOLUTIONS:
        printf("Infinite solutions\n");
        break;
    case ZERO_SOLUTIONS:
        printf("Zero solutions\n");
        break;
    case ONE_REAL_SOLUTION:
        printf("One solution - x = %.12lf at a = %lf, b = %lf, c = %lf\n", res->x1, a, b, c);
        break;
    case TWO_REAL_SOLUTIONS:
        printf("Two solutions - x1 = %.12lf, x2 = %.12lf at a = %lf, b = %lf, c = %lf\n", res->x1, res->x2, a, b, c);
        break;
    case TWO_COMPLEX_SOLUTIONS:
        if (my_abs(res->re) < eps) {
            if (my_abs(res->im - 1) < eps) {
                printf("Two solutions - x1,2 = ±i at a = %lf, b = %lf, c = %lf\n", a, b, c);
            }
            else {
                printf("Two solutions - x1,2 = ±%lfi at a = %lf, b = %lf, c = %lf\n", res->im, a, b, c);
            }
        } else {
            printf("Two solutions - x1,2 = %lf ± %lfi at a = %lf, b = %lf, c = %lf\n", res->re, res->im, a, b, c);
        }
        break;
    default:
        printf("Unknown solution type\n");
        break;
    }
}

int64_t string_to_int(const char* str, const int64_t base) {
    if (base < 2 || base > 36)
        return 0;

    int8_t mul = 1;
    if (*str == '-') {
        mul = -1;
        ++str;
    }
    int64_t res = 0;
    while (*str) {
        res = res * base + (isdigit(*str) ? *str++ - '0' : *str++ - 'A' + 10);
    }
    return mul * res;
}

int8_t is_divisible_by(int64_t a, int64_t b) {
    if (b == 0) return 0;
    return (int8_t)(a % b == 0);
}


int8_t is_rectangle(const double eps, const double a, const double b, const double c) {
    if (a < eps || b < eps || c < eps) return 0; // вырожденные случаи

    double left = a * a + b * b;
    double right = c * c;
    double relative_error = my_abs(left - right) / left; // относительная погрешность, вместо абсолютной для более точных вычислений
    return (int8_t)(relative_error < eps);
}
