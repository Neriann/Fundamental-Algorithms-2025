#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

enum {
    MAX_LINE_LENGTH = 80
};

typedef enum {
    MEM_ALLOC = -2,
    INVALID_ARG = -1,
    SUCCESS = 0,
} Code;

Code parse_lexeme(char*** result, size_t* result_size, bool is_space, const char* input);

Code normalization_interval(char** spaces, size_t spaces_size, size_t hi_bound, size_t last_processed, size_t count_spaces, FILE* output_file);

Code calculating_normalized_data(char** lexemes, size_t lexemes_size, char** spaces, size_t spaces_size, FILE* output_file);

#endif //FUNCTIONS_H
