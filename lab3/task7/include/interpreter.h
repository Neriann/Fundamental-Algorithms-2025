#ifndef INTERPRETER_H
#define INTERPRETER_H

#define BUFFER_SIZE 512

typedef int binary_func(int*, const int*);

typedef enum {
    false = 0,
    true = 1
} bool;

typedef struct {
    char op;
    int rank;
    binary_func* func;
} Operation;

typedef struct {
    int value;
    bool is_const;
} Operand;


void handler(FILE* trace_file, const char* expression);


#endif //INTERPRETER_H
