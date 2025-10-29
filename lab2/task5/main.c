#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "functions.h"


int main() {
    char input_filename[64], output_filename[64];
    printf("<input_filename>: ");
    scanf("%s", input_filename);
    printf("<output_filename>: ");
    scanf("%s", output_filename);

    FILE* input_file = fopen(input_filename, "r");
    FILE* output_file = fopen(output_filename, "w");
    if (!input_file || !output_file) {
        printf("Error opening input or output file\n");
        return 1;
    }
    char buff[512];
    while (1) {
        if (fgets(buff, sizeof(buff), input_file) == NULL) break;

        size_t len = strlen(buff);
        if (len < MAX_LINE_LENGTH) {
            fputs(buff, output_file);
            continue;
        }
        char** result = NULL;
        size_t result_size;
        Code code = parse_lexeme(&result, &result_size, buff);
        if (code != SUCCESS) {
            printf("Error while parsing lexemes\n");
            fclose(input_file);
            fclose(output_file);
            return 1;
        }
        Code ans = calculate_normalize_data(result, result_size, output_file);
        if (ans != SUCCESS) {
            printf("Error while calculating normalized data\n");
            for (size_t i = 0; i < result_size; ++i) {
                free(result[i]);
            }
            free(result);
            fclose(input_file);
            fclose(output_file);
            return 1;
        }
        for (size_t i = 0; i < result_size; ++i) {
            free(result[i]);
        }
        free(result);
    }
    fclose(input_file);
    fclose(output_file);
    return 0;
}
