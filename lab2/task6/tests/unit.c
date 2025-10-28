#include <stdlib.h>
#include <string.h>

#include "functions.h"


static FILE* f = NULL;
static Student* students = NULL;
static size_t count_students = 0;


void configurate() {
    const char filename[] = "../tests/students.txt";
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return;
    }
    f = file;
}

void test_create_student_list() {
    printf("\n===Creating student list===\n");

    Code code = create_student_list(f, &students, &count_students);
    if (code != SUCCESS) {
        printf("Error creating student list\n");
        return;
    }
    printf("Student list:\n");
    for (size_t i = 0; i < count_students; ++i) {
        print_student_info(students + i, stdout);
    }
}

void test_find_by_id() {
    printf("\n===Testing find by id===\n");
    const Student* result = NULL;
    const uint32_t id = 7;

    Code ans = find_student_by_id(students, count_students, &result, id);
    if (ans == OUT_OF_RANGE) {
        printf("Student not found\n");
        return;
    }
    printf("Student found id %d:\n", id);
    print_student_info(result, stdout);
}

void test_find_by_name() {
    {
        printf("\n ===Testing find by name===\n");

        const Student* result = NULL;
        size_t result_size = 0;

        const char name[] = "John";
        Code ans = find_students_by_name(students, count_students, &result, &result_size, name, strlen(name));
        if (ans == OUT_OF_RANGE) {
            printf("Student not found\n");
            return;
        }
        if (ans != SUCCESS) {
            printf("Error finding student name\n");
            return;
        }
        printf("Student found name %s:\n", name);
        for (size_t i = 0; i < result_size; ++i) {
            print_student_info(result + i, stdout);
        }
    }
}

void test_find_by_surname() {
    {
        printf("\n ===Testing find by surname===\n");

        const Student* result = NULL;
        size_t result_size = 0;

        const char surname[] = "Ronaldo";
        Code ans = find_students_by_surname(students, count_students, &result, &result_size, surname, strlen(surname));
        if (ans == OUT_OF_RANGE) {
            printf("Student not found\n");
            return;
        }
        printf("Student found surname %s:\n", surname);
        for (size_t i = 0; i < result_size; ++i) {
            print_student_info(result + i, stdout);
        }
    }
}

void test_find_by_group() {
    {
        printf("\n ===Testing find by group===\n");

        const Student* result = NULL;
        size_t result_size = 0;

        const char group[] = "CS-21-1";
        Code ans = find_students_by_group(students, count_students, &result, &result_size, group, strlen(group));
        if (ans == OUT_OF_RANGE) {
            printf("Student not found\n");
            return;
        }
        printf("Student found group %s:\n", group);
        for (size_t i = 0; i < result_size; ++i) {
            print_student_info(result + i, stdout);
        }
    }
}

void test_failed_find_by_surname() {
    {
        printf("\n ===Testing find by surname===\n");

        const Student* result = NULL;
        size_t result_size = 0;

        const char surname[] = "Messi";
        Code ans = find_students_by_surname(students, count_students, &result, &result_size, surname, strlen(surname));
        if (ans == OUT_OF_RANGE) {
            printf("Student not found\n");
            return;
        }
        printf("Student found surname %s:\n", surname);
        for (size_t i = 0; i < result_size; ++i) {
            print_student_info(result + i, stdout);
        }
    }
}

void swap(Student* a, Student* b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

void test_sort_by_id() {
    printf("\n ===Testing sorting by id===\n");

    printf("\nBefore sorting:\n");
    swap(&students[0], &students[4]);
    swap(&students[1], &students[5]);
    swap(&students[2], &students[6]);
    swap(&students[4], &students[8]);

    for (size_t i = 0; i < count_students; ++i) {
        print_student_info(students + i, stdout);
    }

    printf("\nAfter sorting:\n");
    sort_by_id(students, count_students);

    for (size_t i = 0; i < count_students; ++i) {
        print_student_info(students + i, stdout);
    }
}

void test_sort_by_name() {
    printf("\n ===Testing sorting by name===\n");

    sort_by_name(students, count_students);

    for (size_t i = 0; i < count_students; ++i) {
        print_student_info(students + i, stdout);
    }
}

void test_sort_by_surname() {
    printf("\n ===Testing sorting by surname===\n");

    sort_by_surname(students, count_students);

    for (size_t i = 0; i < count_students; ++i) {
        print_student_info(students + i, stdout);
    }
}

void test_sort_by_group() {
    printf("\n ===Testing sorting by group===\n");

    sort_by_group(students, count_students);

    for (size_t i = 0; i < count_students; ++i) {
        print_student_info(students + i, stdout);
    }
}

void run_all_tests() {
    test_create_student_list();
    test_find_by_id();
    test_find_by_name();
    test_find_by_surname();
    test_find_by_group();
    test_failed_find_by_surname();
    test_sort_by_id();
    test_sort_by_name();
    test_sort_by_surname();
    test_sort_by_group();
}

int main() {
    configurate();

    run_all_tests();

    free(students);
    fclose(f);
}
