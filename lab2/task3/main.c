#include <limits.h>
#include <string.h>

#include "functions.h"

#include <stdio.h>

int main() {
    int a = overfprintf(stdout, "%Zr\n", 5);
    printf("%d\n", a);
}
