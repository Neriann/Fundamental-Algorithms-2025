#include "functions.h"

#include <stdio.h>

int main() {
    char c; char ss[50]; char s[50];
    int n, m;
    FILE* f = fopen("../test.txt", "r");
    int r = overfscanf(f, "%d %d", &n, &m);
    printf("%d\n%d %d", n, m, r);
}
