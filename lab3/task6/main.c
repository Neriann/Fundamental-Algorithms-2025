#include <stdio.h>

#include "functions.h"

int main() {
    char buffer[BUFSIZ];
    scanf("%s", buffer);

    if (check_brackets(buffer)) {
        printf("Success expression!\n");
    }
    else {
        printf("Invalid expression!\n");
    }
    return 0;
}
