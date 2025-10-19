#include <limits.h>
#include <string.h>

#include "functions.h"

#include <stdio.h>

int main() {
    int a = overfprintf(stdout, "Hello %s\n", "World");
    printf("%d\n", a);
}
