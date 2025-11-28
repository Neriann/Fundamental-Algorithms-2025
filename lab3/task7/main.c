#include <stdio.h>
#include <string.h>

#include "interpreter.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_filename> <trace_file>\n", argv[0]);
        return 1;
    }

    FILE* f = NULL;
    if (!((f = fopen(argv[1], "r")))) {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
        return 1;
    }
    FILE* f_tr = NULL;
    if (!((f_tr = fopen(argv[2], "w")))) {
        fprintf(stderr, "Error opening file %s\n", argv[2]);
        return 1;
    }
    char buff[BUFFER_SIZE];
    while (fgets(buff, BUFFER_SIZE, f)) {
        buff[strlen(buff) - 1] = 0;

        handler(f_tr, buff);
    }
    fclose(f);
    fclose(f_tr);
    return 0;
}
