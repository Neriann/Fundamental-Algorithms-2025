#include <stdio.h>

#include "approximate_values/functions.h"


int main() {
    long double eps = 1e-7;

    long double e;

    e = get_exponent_from_limit(eps);
    printf("e from limit: %.12Lf\n", e);

    e = get_exponent_from_row(eps);
    printf("e from row: %.12Lf\n", e);

    e = get_exponent_from_equation(eps);
    printf("e from (ln(x)=1): %.12Lf\n", e);

    long double pi;

    pi = get_pi_from_limit(eps);
    printf("pi from limit: %.12Lf\n", pi);

    pi = get_pi_from_row(eps);
    printf("pi from row: %.12Lf\n", pi);

    pi = bisection_method(eps, 3.0, 4.0, func_pi);
    printf("pi from (cos(x)=-1): %.12Lf\n", pi);

    long double ln2;

    ln2 = get_ln2_from_limit(eps);
    printf("ln(2) from limit: %.12Lf\n", ln2);

    ln2 = get_ln2_from_row(eps);
    printf("ln(2) from row: %.12Lf\n", ln2);

    ln2 = bisection_method(eps, 0.0, 1.0, func_ln2);
    printf("ln(2) from (e^x=2): %.12Lf\n", ln2);

    long double sqrt2;

    sqrt2 = get_sqrt2_from_limit(eps);
    printf("sqrt(2) from limit: %.12Lf\n", sqrt2);

    sqrt2 = get_sqrt2_from_row(eps);
    printf("sqrt(2) from row: %.12Lf\n", sqrt2);

    sqrt2 = bisection_method(eps, 1.0, 2.0, func_sqrt2);
    printf("sqrt(2) from (x^2=2): %.12Lf\n", sqrt2);

    long double euler_mascheroni;

    euler_mascheroni = get_gamma_from_limit(eps);
    printf("gamma from limit: %.12Lf\n", euler_mascheroni);

    euler_mascheroni = get_gamma_from_row(eps);
    printf("gamma from row: %.12Lf\n", euler_mascheroni);


    int32_t t = 1e7;
    euler_mascheroni = get_gamma_from_equation(t, eps);
    printf("gamma from equation: %.12Lf\n", euler_mascheroni);
    return 0;
}
