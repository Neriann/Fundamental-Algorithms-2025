#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>

typedef enum {
    ZERO_SOLUTIONS = 0,
    INFINITE_SOLUTIONS,
    ONE_REAL_SOLUTION,
    TWO_REAL_SOLUTIONS,
    TWO_COMPLEX_SOLUTIONS,
} SolutionType;

typedef struct {
    SolutionType type;
    double x1;
    double x2;
    double re;
    double im;
} Solution;

double string_to_double(const char* str);

Solution get_solution_to_equation(const double eps, const double a, const double b, const double c);

void print_solution_to_equation(Solution* result, const double eps, const double a, const double b, const double c);

void swap(double* a, double* b);

double my_abs(const double a);

int64_t string_to_int(const char* str, const int64_t base);

int8_t is_divisible_by(int64_t a, int64_t b);

int8_t is_rectangle(const double eps, const double a, const double b, const double c);

#endif //FUNCTIONS_H
