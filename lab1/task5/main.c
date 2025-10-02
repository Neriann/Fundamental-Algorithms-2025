#include <stdio.h>
#include <string.h>

#include "functions.h"


int main(const int argc, const char* argv[]) {
    if (argc < 3) {
        printf("Not enough arguments\n");
        return 1;
    }
    const char* flag = argv[1];
    const char* file_in = argv[2];

    char current_flag[MAX_LEN], file_out[MAX_LEN];
    size_t flag_len = strlen(flag);
    if (flag_len > 2) {
        const char* current_file = argv[3];
        snprintf(file_out, strlen(current_file) + 1, "%s", current_file);
        size_t pos = 0;
        for (int i = 0; i < flag_len; ++i) {
            if (flag[i] != 'n') {
                current_flag[pos++] = flag[i];
            }
        }
        current_flag[flag_len - 1] = 0;
    }
    else {
        // для snprintf добавляем +1 к длине тк контролируется постановление терминирующего нуля
        snprintf(file_out, strlen(file_in) + 5, "out_%s", file_in);
        snprintf(current_flag, flag_len + 1, "%s", flag);
    }
    FILE* input = fopen(file_in, "r");
    if (!input) {
        printf("Error open %s in read mode\n", file_in);
        return 1;
    }
    FILE* output = fopen(file_out, "w");
    if (!output) {
        printf("Error open %s in write mode\n", file_out);
        return 1;
    }
    char buff[BUFFER_SIZE];
    size_t n = fread(buff, sizeof(char), BUFFER_SIZE, input);
    if (!feof(input)) {
        printf("Error reading from %s in read mode\n", file_in);
        return 1;
    }
    buff[n] = 0;
    char answer[BUFFER_SIZE];
    if (IS_FLAG(current_flag, "-d") || IS_FLAG(current_flag, "/d")) {
        remove_arabic_digits(buff, answer);
        fwrite(answer, sizeof(char), strlen(answer), output);
    }
    else if (IS_FLAG(current_flag, "-i") || IS_FLAG(current_flag, "/i")) {
        count_latin_letters(buff, answer);
        fwrite(answer, sizeof(char), strlen(answer), output);
    }
    else if (IS_FLAG(current_flag, "-s") || IS_FLAG(current_flag, "/s")) {
        count_rare_symbols(buff, answer);
        fwrite(answer, sizeof(char), strlen(answer), output);
    }
    else if (IS_FLAG(current_flag, "-a") || IS_FLAG(current_flag, "/a")) {
        replace_except_digits(buff, answer);
        fwrite(answer, sizeof(char), strlen(answer), output);
    }
    else {
        printf("Unknown flag: %s\n", current_flag);
        return 1;
    }
    fclose(input);
    fclose(output);
    return 0;
}
