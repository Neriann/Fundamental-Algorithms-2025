#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"


Code parse_lexeme(char*** result, size_t* result_size, bool is_space, const char* p) {
    if (!result || !p || !result_size) return INVALID_ARG;

    size_t size = 0, capacity = 1;
    char** arr = (char**)malloc(sizeof(char*) * capacity);
    if (!arr) return INVALID_ARG;

    char pch = 0, ch;
    // +терминирующий ноль
    char buff[MAX_LINE_LENGTH + 1]; // лексема не может быть больше чем MAX_LINE_LENGTH
    char* ptr_to_buff = buff;
    while (*p) {
        ch = *p++;
        if (!isspace(ch) && !is_space || isspace(ch) && is_space) {
            *ptr_to_buff++ = ch;
        }
        if (isspace(ch) && !isspace(pch) && !is_space || !isspace(ch) && isspace(pch) && is_space) {
            if (capacity <= size) {
                capacity *= 2;
                char** new_arr = (char**)realloc(arr, sizeof(char*) * capacity);
                if (!new_arr) {
                    free(arr);
                    return INVALID_ARG;
                }
                arr = new_arr;
            }
            *ptr_to_buff = 0;
            size_t len = strlen(buff);
            if (is_space) {
                // выделяем память на максимальный размер лексемы, чтобы можно было добавить пробелы
                arr[size] = (char*)malloc(sizeof(char) * (MAX_LINE_LENGTH + 1));
            } else {
                // для лексем можно выделять фактический размер
                arr[size] = (char*)malloc(sizeof(char) * (len + 1));
            }
            if (!arr[size]) {
                for (size_t i = 0; i < size; ++i) {
                    free(arr[i]);
                }
                free(arr);
                return MEM_ALLOC;
            }
            strncpy(arr[size], buff, len);
            arr[size][len] = 0;
            ptr_to_buff = buff;
            ++size;
        }
        pch = ch;
    }
    *result_size = size;
    *result = arr;
    return SUCCESS;
}

Code normalization_interval(char** spaces, size_t spaces_size, size_t hi_bound, size_t last_processed, size_t count_spaces, FILE* output_file) {
    if (!spaces || !*spaces || !spaces_size || !output_file || last_processed >= spaces_size) return INVALID_ARG;

    size_t interval = hi_bound - last_processed;

    // получаем число повторяющихся пробелов между лексемами и остаток, который добавляем в начальные промежутки
    size_t shift = count_spaces / interval;
    size_t rem = count_spaces % interval;

    for (size_t j = last_processed; j < hi_bound; ++j) {
        if (rem) { snprintf(spaces[j], MAX_LINE_LENGTH, " %s", spaces[j]); --rem; }
        if (shift) snprintf(spaces[j], MAX_LINE_LENGTH, "%*s", (int)(strlen(spaces[j]) + shift), spaces[j]);

        printf("%s|", spaces[j]);
        fflush(stdout);
    }
    return SUCCESS;
}

void file_print(char** lexemes, char** spaces, size_t prev_id, size_t curr_id, FILE* output_file) {
    fprintf(output_file, "%s", lexemes[prev_id]);
    for (size_t j = prev_id + 1; j < curr_id; ++j) {
        fprintf(output_file, "%s", spaces[j - 1]);
        fprintf(output_file, "%s", lexemes[j]);
    }
    fprintf(output_file, "\n");
}

Code calculating_normalized_data(char** lexemes, size_t lexemes_size, char** spaces, size_t spaces_size, FILE* output_file) {
    if (!lexemes || !lexemes_size || !output_file) return INVALID_ARG;

    // обрабатываем первую лексему, чтобы уравнять количество оставшихся лексем и пробелов
    size_t sum_length = strlen(lexemes[0]), last_processed = 0;
    for (size_t i = 1; i < lexemes_size; ++i) {

        size_t space_length = strlen(spaces[i - 1]);
        size_t lexeme_length = strlen(lexemes[i]);

        // записываем результат, только если превысили максимум
        if (sum_length + space_length + lexeme_length > MAX_LINE_LENGTH) {
            // записываем в файл подходящее количество лексем с нужным количеством пробелов
            size_t count_spaces = MAX_LINE_LENGTH - sum_length;
            Code code = normalization_interval(spaces, spaces_size, i - 1, last_processed, count_spaces, output_file);
            if (code != SUCCESS) return code;

            file_print(lexemes, spaces, last_processed, i, output_file);

            // начинаем следующую строку с i-ой лексемы
            last_processed = i;
            sum_length = lexeme_length;
            continue;
        }
        sum_length += lexeme_length;
        sum_length += space_length;
    }
    if (sum_length > 0) {
        size_t count_spaces = MAX_LINE_LENGTH - sum_length;
        Code code = normalization_interval(spaces, spaces_size, spaces_size, last_processed, count_spaces, output_file);
        if (code != SUCCESS) return code;

        file_print(lexemes, spaces, last_processed, lexemes_size, output_file);
    }
    return SUCCESS;
}
