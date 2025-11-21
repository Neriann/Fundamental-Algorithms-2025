#include <stdio.h>

#include "functions.h"

int match(char a, char b) {
    return a == '{' && b == '}' || a == '[' && b == ']' || a == '<' && b == '>' || a == '(' && b == ')';
}


int check(const char* str, size_t* pos) {
    while (str[*pos] != 0) {
        char c = str[*pos];
        if (c == '}' || c == ')' || c == ']' || c == '>') {
            return str[*pos];
        }
        if (str[*pos] == '(' || str[*pos] == '[' || str[*pos] == '{' || str[*pos] == '<') {
            char open = str[*pos];

            (*pos)++;

            char close = (char)check(str, pos);
            if (!match(open, close)) {
                return 1;
            }

        }
        (*pos)++;
    }
    return 0;
}


int check_brackets(const char* str) {
    size_t pos = 0;
    return check(str, &pos) == 0;
}
