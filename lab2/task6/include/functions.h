#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdint.h>
#include <stdio.h>

enum {
    LEXEME_SZ = 100
};

typedef enum {
    NAME = 0,
    SURNAME = 1,
    GROUP = 2
} Field;

typedef struct {
    uint32_t id;
    char name[LEXEME_SZ];
    char surname[LEXEME_SZ];
    char group[LEXEME_SZ];
    unsigned char* grades;
} Student;

typedef enum {
    OUT_OF_RANGE = -1,
    MEM_ALLOC = -2,
    INVALID_ARG = -3,
    SUCCESS = 0,
} Code;

void print_student_info(const Student* student, FILE* stream);

Code create_student_list(FILE* file, Student** const students, size_t* const size);

Code find_student_by_id(const Student* students, size_t count_students, const Student** const result, size_t target_id);

Code find_students_by_grades(const Student* students, size_t count_students, const Student** const result, size_t* const result_size);

#define DECLARE_FINDS(field) Code find_students_by_##field(const Student* students, size_t count_students, const Student** const result, \
size_t* const result_size, const char* target, size_t target_length);

DECLARE_FINDS(name)
DECLARE_FINDS(surname)
DECLARE_FINDS(group)


void sort_by_id(Student* students, size_t count_students);

#define DECLARE_SORTS(field) void sort_by_##field(Student* students, size_t count_students);

DECLARE_SORTS(name)
DECLARE_SORTS(surname)
DECLARE_SORTS(group)


#endif //FUNCTIONS_H
