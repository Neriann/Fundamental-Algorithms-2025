#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpreter.h"
#include "operations.h"

static const Operation operations[] = {
    {.op = '^', .rank = 5, to_power},
    {.op = '*', .rank = 4, multiply},
    {.op = '/', .rank = 4, division},
    {.op = '-', .rank = 3, subtract},
    {.op = '+', .rank = 3, addition},
    {.op = '(', .rank = 2, NULL},
    {.op = ')', .rank = 2, NULL},
    {.op = '=', .rank = 1, assign}, // Приоритет должен быть меньше чем у '('
};

// Переменные с именами A-Z
static int operands[26] = {};


Operation find_operation(char operation) {
    for (size_t i = 0; i < sizeof(operations) / sizeof(operations[0]); ++i) {
        if (operations[i].op == operation) {
            return operations[i];
        }
    }
    return (Operation){0};
}

int is_operation(char c) {
    Operation op = find_operation(c);
    // Подходят все операции кроме скобок
    return op.rank && op.func;
}

void division_into_tokens(char*** res, size_t* res_size, const char* p_expr) {
    size_t capacity = 10;
    size_t size = 0;
    char** tokens = (char**)malloc(capacity * sizeof(char*));

    char buff[32];
    char* p = buff;

    char pch = 0, ch;
    do {
        ch = *p_expr++;
        // Операнд или операция
        if (isalnum(ch) || is_operation(ch)) {
            *p++ = ch;
        }
        else if (isalnum(pch) || is_operation(pch)) {
            *p = 0;

            if (size >= capacity) {
                capacity *= 2;
                char** new_tokens = (char**)realloc(tokens, capacity * sizeof(char*));
                if (!new_tokens) {
                    for (size_t i = 0; i < size; ++i) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    fprintf(stderr, "Out of memory\n");
                    return;
                }
                tokens = new_tokens;
            }

            size_t len = strlen(buff);
            tokens[size] = (char*)malloc((len + 1) * sizeof(char));
            strncpy(tokens[size], buff, len);
            tokens[size][len] = 0;
            ++size;

            p = buff;
        }

        if (ch == '(' || ch == ')') {
            if (size >= capacity) {
                capacity *= 2;
                char** new_tokens = (char**)realloc(tokens, capacity * sizeof(char*));
                if (!new_tokens) {
                    for (size_t i = 0; i < size; ++i) {
                        free(tokens[i]);
                    }
                    free(tokens);
                    fprintf(stderr, "Out of memory\n");
                    return;
                }
                tokens = new_tokens;
            }
            tokens[size] = (char*)malloc(2 * sizeof(char));
            tokens[size][0] = ch;
            tokens[size][1] = 0;
            ++size;
        }
        pch = ch;
    } while (ch != 0);

    *res = tokens;
    *res_size = size;
}

int calculate_expression(const char* expression) {
    Operand stack_operands[BUFFER_SIZE];
    size_t stack_operands_size = 0;

    char stack_operations[BUFFER_SIZE];
    size_t stack_operations_size = 0;

    char** tokens = NULL;
    size_t tokens_size = 0;

    division_into_tokens(&tokens, &tokens_size, expression);

    for (size_t i = 0; i < tokens_size; ++i) {
        char* p = tokens[i];

        Operation current_op = find_operation(*p);

        // если нет ранга, значит это операнд
        if (!current_op.rank) {
            stack_operands[stack_operands_size++] = isalpha(*p) && isupper(*p) ?
                (Operand){.value = *p, .is_const = false}
            : (Operand){.value = (int)strtol(p, NULL, 10), .is_const = true};

            continue;
        }
        // Иначе это операция
        char ch = *p;

        // Если стек операций пустой или операция - (, то просто добавляем в стек
        if (!stack_operations_size || current_op.op == '(') {
            // Выражение не может начинаться с закрывающейся скобки
            if (current_op.op == ')') {
                fprintf(stderr, "Invalid expression\n");
                break;
            }
            stack_operations[stack_operations_size++] = ch;
            continue;
        }
        if (current_op.op == ')') {
            char op;
            while (stack_operations_size > 0 && stack_operands_size > 1 && (op = stack_operations[--stack_operations_size]) != '(') {
                current_op = find_operation(op);

                Operand rval = stack_operands[--stack_operands_size];
                Operand lval = stack_operands[--stack_operands_size];

                int* rp = rval.is_const ? &rval.value : &operands[rval.value - 'A'];
                int* lp = lval.is_const ? &lval.value : &operands[lval.value - 'A'];

                stack_operands[stack_operands_size++] = (Operand){.value = current_op.func(lp, rp), .is_const = true};
            }
            continue;
        }
        // Иначе сравниваем приоритет текущей операции с операцией, лежащей на верхушке стека
        Operation previous_op = find_operation(stack_operations[stack_operations_size - 1]);
        // Если текущий приоритет выше, то просто заносим в стек операций
        // Включаем равенство, чтобы поддерживать операции вида A = B = C
        if (current_op.rank >= previous_op.rank) {
            stack_operations[stack_operations_size++] = ch;
        }
        else {
            // иначе вытаскиваем из стека операции и операнды, пока не восстановится условие приоритета
            // или один из стеков не опустеет

            while (stack_operations_size > 0 && stack_operands_size > 1 && current_op.rank < previous_op.rank) {
                // Удаляем текущую операцию из стека
                --stack_operations_size;

                Operand rval = stack_operands[--stack_operands_size];
                Operand lval = stack_operands[--stack_operands_size];

                int* rp = rval.is_const ? &rval.value : &operands[rval.value - 'A'];
                int* lp = lval.is_const ? &lval.value : &operands[lval.value - 'A'];

                // Выполняется предшествующая операция со стека! Результат заносится в стек операндов
                stack_operands[stack_operands_size++] = (Operand){.value = previous_op.func(lp, rp), .is_const = true};

                current_op = previous_op;
                previous_op = find_operation(stack_operations[stack_operations_size - 1]);
            }
            // Кладем текущую операцию на стек
            stack_operations[stack_operations_size++] = ch;
        }
    }
    // Если в стеке операций остались элементы подсчитываем их
    while (stack_operations_size > 0 && stack_operands_size > 1) {
        Operation operation = find_operation(stack_operations[--stack_operations_size]);

        Operand rval = stack_operands[--stack_operands_size];
        Operand lval = stack_operands[--stack_operands_size];

        int* rp = rval.is_const ? &rval.value : &operands[rval.value - 'A'];
        int* lp = lval.is_const ? &lval.value : &operands[lval.value - 'A'];

        stack_operands[stack_operands_size++] = (Operand){.value = operation.func(lp, rp), .is_const = true};
    }
    // Очищаем память массива токенов
    for (size_t i = 0; i < tokens_size; ++i) {
        free(tokens[i]);
    }
    free(tokens);

    if (stack_operands_size != 1) {
        fprintf(stderr, "Invalid expression\n");
    }

    return stack_operands[stack_operands_size - 1].value;
}

void logging(FILE* trace_file, const char* expression, const char* name) {
    static int iteration = 0;
    fprintf(trace_file, "[%d] %-32s | ", iteration++, expression);

    for (size_t j = 0; j < sizeof(operands) / sizeof(operands[0]); ++j) {
        if (operands[j]) {
            fprintf(trace_file, "%c=%d ", (char)('A' + j), operands[j]);
        }
    }
    fprintf(trace_file, "| %s\n", name);

    fflush(trace_file);
}

// Обработчик программы
void handler(FILE* trace_file, const char* expression) {
    char mini_expr[100];
    // Читаем до 99 символов до ')'
    if (sscanf(expression, "print(%99[^)])", mini_expr) == 1) {
        if (strlen(mini_expr) == 1) {
            printf("%c=%d\n", *mini_expr, operands[*mini_expr - 'A']);
        } else {
            int value = calculate_expression(mini_expr);
            printf("%s=%d\n", mini_expr, value);
        }
        logging(trace_file, expression, expression);
    } else {
        calculate_expression(expression);
        size_t count_operations = 0, count_assign_op = 0;
        const char* p = expression;
        while (*p) {
            if (*p == '=') ++count_assign_op;
            if (is_operation(*p)) ++count_operations;
            ++p;
        }
        // Если есть операции помимо присваивания
        if (count_operations && count_operations - count_assign_op) logging(trace_file, expression, "Arithmetic operation");
        // Если только присваивание
        else if (count_operations) logging(trace_file, expression, "Assignment");
        // Иначе не известная операция
        else logging(trace_file, expression, "Operation not found");
    }
}
