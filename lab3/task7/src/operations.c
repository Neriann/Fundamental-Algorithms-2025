#include "operations.h"

int to_power(int* a, const int* b) {
    int base = *a;
    int pow = *b;

    int res = 1;
    while (pow) {
        if (pow & 1) {
            res = res * base;
        }
        base = base * base;
        pow >>= 1;
    }
    return res;
}

int multiply(int* a, const int* b) {
    return *a * *b;
}

int division(int* a, const int* b) {
    return *a / *b;
}

int subtract(int* a, const int* b) {
    return *a - *b;
}

int addition(int* a, const int* b) {
    return *a + *b;
}

int assign(int* a, const int* b) {
    *a = *b;
    return *a;
}
