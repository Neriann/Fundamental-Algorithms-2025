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
        int64_t num;
        Code code = is_number(pointer_to_num);
        if (code == NOT_NUMBER) {
            printf("Not a decimal number: %s\n", pointer_to_num);
            return 1;
        }
        code = string_to_int(&num, pointer_to_num, 10);
        switch (code) {
        case OVERFLOW_NUMBER:
            printf("The number %s is overflow\n", pointer_to_num);
            return 1;

        case NOT_NUMBER:
            printf("%s is not a number\n", pointer_to_num);
            return 1;

        default: ;
        }
        int64_t* numbers = NULL;
        size_t numbers_size = 0;
        code = get_divisible_numbers(&numbers, &numbers_size, num);
        if (code == ALLOCATE_ERROR) {
            printf("Failed to allocate memory\n");
            return 1;
        }
        if (numbers != NULL) {
            printf("Numbers that are divisible by %ld:\n", num);
            for (size_t i = 0; i < numbers_size; ++i) {
                printf("%ld ", numbers[i]);
            }
            printf("\n");
            free(numbers);
        } else {
            printf("There are no numbers between 1 and 100 that are divisible by %ld\n", num);
        }
    }
    else if (strcmp(flag, "-p") == 0) {
        int64_t num;
        Code code = is_number(pointer_to_num);
        if (code == NOT_NUMBER) {
            printf("Not a decimal number: %s\n", pointer_to_num);
            return 1;
        }
        Code code1 = string_to_int(&num, pointer_to_num, 10);
        switch (code1) {
        case OVERFLOW_NUMBER:
            printf("The number %s is overflow\n", pointer_to_num);
            return 1;

        case NOT_NUMBER:
            printf("%s is not a number\n", pointer_to_num);
            return 1;

        default: ;
        }
        Code code2 = is_prime(num);
        switch (code2) {
            case UNNATURAL_NUMBER:
                printf("The number %ld isn't natural\n", num);
                return 1;
            case PRIME_NUMBER:
                printf("The number %ld is prime\n", num);
                break;
            case COMPOSITE_NUMBER:
                printf("The number %ld is composite\n", num);
                break;
            case SPECIFIC_NUMBER:
                printf("The number %ld is specific\n", num);
                break;

            default: ;
        }
    }
    else if (strcmp(flag, "-s") == 0) {
        if (is_number(pointer_to_num) == NOT_NUMBER) {
            printf("Not a decimal number\n");
            return 1;
        }
        char buff[MAX_SIZE];
        char* res;
        Code code = get_hex_num(pointer_to_num, &res, buff);
        if (code != SUCCESS) {
            printf("The number %s is invalid\n", pointer_to_num);
        }
        while (*res) {
            printf("%c ", *res++);
        }
        printf("\n");
    }
    else if (strcmp(flag, "-e") == 0) {
        int64_t num;
        Code code = is_number(pointer_to_num);
        if (code == NOT_NUMBER) {
            printf("Not a decimal number: %s\n", pointer_to_num);
            return 1;
        }
        code = string_to_int(&num, pointer_to_num, 10);
        switch (code) {
        case OVERFLOW_NUMBER:
            printf("The number %s is overflow\n", pointer_to_num);
            return 1;

        case NOT_NUMBER:
            printf("%s is not a number\n", pointer_to_num);
            return 1;

        default: ;
        }
        print_powers_table(num);
    }
    else if (strcmp(flag, "-a") == 0) {
        int64_t num;
        Code code = is_number(pointer_to_num);
        if (code == NOT_NUMBER) {
            printf("Not a decimal number: %s\n", pointer_to_num);
            return 1;
        }
        code = string_to_int(&num, pointer_to_num, 10);
        switch (code) {
        case OVERFLOW_NUMBER:
            printf("The number %s is overflow\n", pointer_to_num);
            return 1;

        case NOT_NUMBER:
            printf("%s is not a number\n", pointer_to_num);
            return 1;

        default: ;
        }
        int64_t result;
        code = get_sum(&result, num);
        switch (code) {
            case NEGATIVE_NUMBER:
                printf("The number %ld should be natural\n", result);
                break;
            case ZERO_NUMBER:
                printf("The number %ld is not natural\n", result);
                break;
            case OVERFLOW_NUMBER:
                printf("The sum from 1 to %ld is very large\n", num);
                break;
            default:
                printf("The sum from 1 to %ld is equal to %ld\n", num, result);
        }
    }
    else if (strcmp(flag, "-f") == 0) {
        int64_t num;
        Code code = is_number(pointer_to_num);
        if (code == NOT_NUMBER) {
            printf("Not a decimal number: %s\n", pointer_to_num);
            return 1;
        }
        code = string_to_int(&num, pointer_to_num, 10);
        switch (code) {
        case OVERFLOW_NUMBER:
            printf("The number %s is overflow\n", pointer_to_num);
            return 1;

        case NOT_NUMBER:
            printf("%s is not a number\n", pointer_to_num);
            return 1;
        default: ;
        }
        int64_t fact;
        code = get_fact(&fact, num);

        switch (code) {
            case NEGATIVE_NUMBER:
                printf("The number %ld is negative\n", num);
                break;
            case OVERFLOW_NUMBER:
                printf("The factorial of number %ld is very large\n", num);
                break;

            default:
                printf("The factorial of number %ld is %ld\n", num, fact);
                break;
        }

    } else {
        printf("This flag isn't defined\n");
        return 1;
    }
    return 0;
}
