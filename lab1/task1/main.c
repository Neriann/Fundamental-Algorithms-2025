#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"


int main(const int argc, const char* argv[]) {
    if (argc < 3) {
        printf("Not enough arguments\n");
        return 1;
    }
    const char* flag = argv[1];
    const char* pointer_to_num = argv[2];

    if (strcmp(flag, "-h") == 0) {
        const int64_t num = string_to_int(pointer_to_num, 10);
        int64_t* numbers = get_divisible_numbers(num);
        if (numbers != NULL) {
            int64_t* p = numbers;
            while (*p) printf("%ld ", *p++);
            printf("\n");
            free(numbers);
        } else {
            printf("There are no numbers between 1 and 100 that are divisible by %ld\n", num);
        }
    }
    else if (strcmp(flag, "-p") == 0) {
        const int64_t num = string_to_int(pointer_to_num, 10);
        const uint8_t code = is_prime(num);
        if (code == UNNATURAL_NUMBER) printf("The number %ld isn't natural\n", num);
        else if (code == PRIME_NUMBER) printf("The number %ld is prime\n", num);
        else if (code == COMPOSITE_NUMBER) printf("The number %ld is composite\n", num);
        else printf("The number %ld is specific\n", num);
    }
    else if (strcmp(flag, "-s") == 0) {
        char** answer = get_divisible_by_base_digits(pointer_to_num, 16);
        if (answer) {
            for (size_t i = 0; answer[i] != NULL; ++i) {
                printf("%s ", answer[i]);
                free(answer[i]);
            }
            printf("\n");
            free(answer);
        }
    }
    else if (strcmp(flag, "-e") == 0) {
        const int64_t num = string_to_int(pointer_to_num, 10);
        print_powers_table(num);
    }
    else if (strcmp(flag, "-a") == 0) {
        char* answer = get_sum(pointer_to_num);
        if (!answer) {
            printf("Memory allocation error\n");
            return 1;
        }
        printf("%s\n", answer);
        free(answer);
    }
    else if (strcmp(flag, "-f") == 0) {
        const int64_t num = string_to_int(pointer_to_num, 10);
        char* fact = get_fact(num);
        if (!fact) {
            printf("Error while computing factorial\n");
            return 1;
        }
        printf("%s\n", fact);
        free(fact);
    } else {
        printf("This flag isn't defined\n");
        return 1;
    }
    return 0;
}
