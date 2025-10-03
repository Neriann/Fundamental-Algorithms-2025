#include <stdio.h>
#include <string.h>

#include "functions.h"

int main(const int argc, const char* argv[]) {
    if (argc < 3) {
        printf("Usage: test <file_in> <file_out>\n");
        return 1;
    }
    FILE* in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Error opening file %s in reading mode\n", argv[1]);
        return 1;
    }
    char buff[BUFFER_SIZE];
    size_t bytes_read = fread(buff, sizeof(char), BUFFER_SIZE, in);
    if (!feof(in)) {
        printf("Error reading file %s\n", argv[1]);
        return 1;
    }
    buff[bytes_read] = 0;
    char answer[BUFFER_SIZE];
    const char* res = choose_string(buff, answer);
    if (res == NULL) {
        printf("Choose failed\n");
        return 1;
    }
    FILE* out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Error opening file %s in writing mode\n", argv[2]);
        return 1;
    }

    fwrite(res, sizeof(char), strlen(res), out);
    fclose(in);
    fclose(out);
    return 0;
}
