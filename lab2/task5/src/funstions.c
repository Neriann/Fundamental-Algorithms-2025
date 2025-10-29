#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"


Code parse_lexeme(char*** result, size_t* result_size, const char* p) {
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
        if (!isspace(ch)) {
            *ptr_to_buff++ = ch;
        }
        if (isspace(ch) && !isspace(pch)) {
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
            arr[size] = (char*)malloc(sizeof(char) * (len + 1));
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

Code write_to_file(char** result, size_t result_size, size_t hi_bound, size_t sum_length, size_t last_processed, size_t count_spaces, FILE* output_file) {
    if (!result || !*result || !result_size || !output_file || last_processed >= result_size) return INVALID_ARG;

    // если пробелов нет, то значит поступило только одно число
    if (!count_spaces) {
        fprintf(output_file, "%s\n", *result);
        return SUCCESS;
    }

    size_t total_length_spaces = MAX_LINE_LENGTH - sum_length;
    size_t rem = total_length_spaces % count_spaces;

    // получаем число повторяющихся пробелов между лексемами
    size_t shift = floor((double)total_length_spaces / (double)count_spaces);
    if (result_size > 0) fprintf(output_file, "%s", result[last_processed]);

    for (size_t j = last_processed + 1; j < hi_bound; ++j) {
        // добавляем остаток пробелов
        if (rem) { fprintf(output_file, " "); --rem; }
        fprintf(output_file, "%*s", (int)(strlen(result[j]) + shift), result[j]);
    }
    fprintf(output_file, "\n");
    return SUCCESS;
}

Code calculate_normalize_data(char** result, size_t result_size, FILE* output_file) {
    if (!result || !result_size || !output_file) return INVALID_ARG;

    size_t sum_length = 0, last_processed = 0;
    for (size_t i = 0; i < result_size; ++i) {
        size_t curr_length = strlen(result[i]);
        size_t count_spaces = i - last_processed - 1;
        size_t max_length = MAX_LINE_LENGTH - count_spaces; // максимальная сумма длин лексем, чтобы был хотя бы 1 пробел
        if (sum_length + curr_length >= max_length) {
            // записываем в файл подходящее количество лексем с нужным количеством пробелов
            Code code = write_to_file(result, result_size, i, sum_length, last_processed, count_spaces, output_file);
            if (code != SUCCESS) return code;

            last_processed = i;
            sum_length = 0;
        }
        sum_length += curr_length;
    }
    if (sum_length > 0) {
        size_t count_spaces = result_size - last_processed - 1;
        Code code = write_to_file(result, result_size, result_size, sum_length, last_processed, count_spaces, output_file);
        if (code != SUCCESS) return code;
    }
    return SUCCESS;
}
