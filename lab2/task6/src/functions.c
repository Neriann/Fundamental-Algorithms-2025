#include <stddef.h>
#include <string.h>

#include "functions.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


double get_average_grade(const Student* student) {
    double avg_grade = 0;
    size_t sz = strlen(student->grades);

    for (size_t i = 0; i < sz; ++i) {
        avg_grade += student->grades[i] - '0';
    }
    avg_grade /= sz;
    return avg_grade;
}

double get_average_grade_of_all(const Student* students, size_t count_students) {
    double all_avg_grade = 0;
    for (size_t i = 0; i < count_students; ++i) {
        all_avg_grade += get_average_grade(students + i);
    }
    all_avg_grade /= count_students;
    return all_avg_grade;
}

void print_student_info(const Student* student, FILE* stream) {
    if (!student || !stream)
        return;

    fprintf(stream, "\nStudent ID: %u\n", student->id);
    fprintf(stream, "Student Name: %s\n", student->name);
    fprintf(stream, "Student Surname: %s\n", student->surname);
    fprintf(stream, "Student Group: %s\n", student->group);
    fprintf(stream, "Student Grades: ");
    size_t sz = strlen(student->grades);
    for (size_t i = 0; i < sz; ++i) {
        fprintf(stream, "%c ", student->grades[i]);
    }
    fprintf(stream, "\n");
    double avg_grade = get_average_grade(student);
    fprintf(stream, "Average grade: %lf\n", avg_grade);
    // очищаем буфер, чтобы интерактивно видеть результат запроса
    fflush(stream);
}



// массив сдвигов для полей
const int shifts[] = {offsetof(Student, name), offsetof(Student, surname),
                      offsetof(Student, group)};

enum {
    GRADES = 5,
    DETAILS = 3,
    CHARACTERISTICS = GRADES + DETAILS, // не считая id
};

Code choose_field(Student* const student, const char* lexeme, Field field, size_t curr_lexeme_size) {
    if (!student || !lexeme || !curr_lexeme_size)
        return INVALID_ARG;

    switch (field) {
    case NAME:
    case SURNAME:
    case GROUP:

        char* target = (char*)student + shifts[field];
        if (LEXEME_SZ <= curr_lexeme_size) {
            return OUT_OF_RANGE;
        }
        strncpy(target, lexeme, curr_lexeme_size);
        target[curr_lexeme_size] = 0;
        break;
    default:
        if (!student->grades) {
            student->grades = (unsigned char*)malloc(sizeof(unsigned char) * (GRADES + 1));
        }
        student->grades[field - DETAILS] = *lexeme;
        student->grades[field - DETAILS + 1] = 0;
        break;
    }
    return SUCCESS;
}

Code safety_reallocate(Student** const students, size_t* capacity, size_t current_size) {
    if (!students || !capacity)
        return INVALID_ARG;

    *capacity *= 2;
    Student* new_students = (Student*)realloc(*students, sizeof(Student) * *capacity);
    if (!new_students) {
        for (size_t i = 0; i < current_size; ++i) {
            free((*students)[i].grades);
        }
        free(*students);
        *students = NULL;
        return MEM_ALLOC;
    }
    *students = new_students;
    return SUCCESS;
}

Code parse_lexeme(Student* students, size_t size, FILE* file, char* const lexeme, size_t* const pos) {
    char* p = lexeme;
    char pch = 0, ch;
    while (*pos < CHARACTERISTICS) {
        ch = (char)fgetc(file);
        if (ch == EOF) {
            break;
        }
        if (!isspace(ch)) {
            *p++ = ch;
        }
        if (!isspace(pch) && isspace(ch)) {
            *p = 0;
            Code code = choose_field(students + size, lexeme, *pos, strlen(lexeme));
            if (code != SUCCESS) {
                for (size_t i = 0; i < size; ++i) {
                    free(students[i].grades);
                }
                free(students);
                return MEM_ALLOC;
            }
            p = lexeme;
            ++(*pos);
        }
        pch = ch;
    }
    return SUCCESS;
}

Code create_student_list(FILE* file, Student** const students, size_t* const size) {
    if (!file || !students || !size) {
        return INVALID_ARG;
    }
    size_t curr_size = 0, capacity = 1;
    Student* arr = (Student*)malloc(sizeof(Student) * capacity);
    if (!arr) {
        return MEM_ALLOC;
    }
    char lexeme[LEXEME_SZ];
    while (!feof(file)) {
        if (capacity <= curr_size) {
            Code code = safety_reallocate(&arr, &capacity, curr_size);
            if (code != SUCCESS) {
                return code;
            }
        }
        arr[curr_size].id = curr_size;
        arr[curr_size].grades = NULL;
        size_t pos = 0;

        Code code = parse_lexeme(arr, curr_size, file, lexeme, &pos);
        if (code != SUCCESS) {
            return code;
        }

        if (pos < CHARACTERISTICS && feof(file)) {
            break;
        }
        ++curr_size;
    }
    *students = arr;
    *size = curr_size;
    return SUCCESS;
}

Code find_students(const Student* students, size_t count_students, const Student** const result, size_t* const result_size,
                   const char* target, size_t target_length, Field field) {
    if (!students || !target || !result || !result_size)
        return INVALID_ARG;

    size_t capacity = 1;
    *result_size = 0;
    Student* arr = (Student*)malloc(sizeof(Student) * capacity);
    if (!arr) {
        return MEM_ALLOC;
    }
    for (size_t i = 0; i < count_students; ++i) {
        // сравниваем значение из структуры с заданным target
        const char* curr = (char*)(students + i) + shifts[field];
        if (*curr && strncmp(curr, target, target_length) == 0) {
            if (capacity <= *result_size) {
                // перевыделение памяти
                Code code = safety_reallocate(&arr, &capacity, *result_size);
                if (code != SUCCESS) {
                    return code;
                }
            }
            arr[*result_size] = students[i];
            ++(*result_size);
        }
    }
    *result = arr;
    return (*result_size > 0) ? SUCCESS : OUT_OF_RANGE;
}

Code find_student_by_id(const Student* students, size_t count_students, const Student** const result,
                        size_t target_id) {
    if (!students || !result)
        return INVALID_ARG;

    if (target_id >= count_students)
        return OUT_OF_RANGE;

    for (size_t i = 0; i < count_students; ++i) {
        if (students[i].id == target_id) {
            *result = students + i;
            return SUCCESS;
        }
    }
    *result = NULL;
    return OUT_OF_RANGE;
}

#define EPSILON 1e-6

Code find_students_by_grades(const Student* students, size_t count_students, const Student** const result, size_t* const result_size) {
    if (!students || !result) return INVALID_ARG;

    size_t capacity = 1; *result_size = 0;
    Student* arr = (Student*)malloc(sizeof(Student) * capacity);
    if (!arr) return MEM_ALLOC;

    double average_grade = get_average_grade_of_all(students, count_students);
    for (size_t i = 0; i < count_students; ++i) {
        if (capacity <= *result_size) {
            Code code = safety_reallocate(&arr, &capacity, *result_size);
            if (code != SUCCESS) {
                return code;
            }
        }
        if (get_average_grade(students + i) - average_grade > EPSILON) {
            arr[*result_size] = students[i];
            ++(*result_size);
        }
    }
    if (!*result_size) {
        free(arr);
        *result = NULL;
        return OUT_OF_RANGE;
    }
    *result = arr;
    return SUCCESS;
}

#define define_find_students(field, Enum) \
    Code find_students_by_##field(const Student* students, size_t count_students, const Student** const result, \
                           size_t* const result_size, const char* target, size_t target_length) { \
    return find_students(students, count_students, result, result_size, target, target_length, Enum); \
}

define_find_students(name, NAME)
define_find_students(surname, SURNAME)
define_find_students(group, GROUP)



typedef int (*Compare)(const void*, const void*);

void sort(Student* students, size_t count_students, Compare compare) {
    if (!students || !count_students)
        return;

    qsort(students, count_students, sizeof(Student), compare);
}

int compare_by_id(const void* student1, const void* student2) {
    if (!student1 || !student2)
        return 0;

    return (int32_t)((Student*)student1)->id - (int32_t)((Student*)student2)->id;
}


#define define_compare(field) \
    int compare_##field(const void* student1, const void* student2) { \
        if (!student1 || !student2) return 0; \
    return strcmp(((Student*)student1)->field, ((Student*)student2)->field); \
}

define_compare(name)
define_compare(surname)
define_compare(group)

#define define_sort(field) \
    void sort_by_##field(Student* students, size_t count_students) { \
        sort(students, count_students, compare_##field); \
    }

define_sort(name)
define_sort(surname)
define_sort(group)

void sort_by_id(Student* students, size_t count_students) {
    sort(students, count_students, compare_by_id);
}
