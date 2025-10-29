#ifndef FUNCTIONS_H
#define FUNCTIONS_H

enum {
    MAX_LINE_LENGTH = 80
};

typedef enum {
    MEM_ALLOC = -2,
    INVALID_ARG = -1,
    SUCCESS = 0,
} Code;

Code parse_lexeme(char*** result, size_t* result_size, const char* input);

Code write_to_file(char** result, size_t result_size, size_t hi_bound, size_t sum_length, size_t last_processed, size_t count_spaces, FILE* output_file);

Code calculate_normalize_data(char** result, size_t result_size, FILE* output_file);

#endif //FUNCTIONS_H
