#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

typedef enum {
    INVALID_COMMAND = -1,
    FIND_BY_ID = 0,
    FIND_BY_NAME,
    FIND_BY_SURNAME,
    FIND_BY_GROUP,
    FIND_BY_GRADES,
    SORT_BY_ID,
    SORT_BY_NAME,
    SORT_BY_SURNAME,
    SORT_BY_GROUP
} CommandType;

static const char* COMMAND_STRINGS[] = {
    [FIND_BY_ID] = "find_by_id=",
    [FIND_BY_NAME] = "find_by_name=",
    [FIND_BY_SURNAME] = "find_by_surname=",
    [FIND_BY_GROUP] = "find_by_group=",
    [FIND_BY_GRADES] = "find_by_grades_greater_then_avg",
    [SORT_BY_ID] = "sort_by_id",
    [SORT_BY_NAME] = "sort_by_name",
    [SORT_BY_SURNAME] = "sort_by_surname",
    [SORT_BY_GROUP] = "sort_by_group",
};

CommandType get_command_type(const char* line) {
    for (size_t i = 0; i < sizeof(COMMAND_STRINGS) / sizeof(COMMAND_STRINGS[0]); ++i) {
        if (strncmp(line, COMMAND_STRINGS[i], strlen(COMMAND_STRINGS[i])) == 0) {
            return i;
        }
    }
    return INVALID_COMMAND;
}

Code find_students_base(const Student* students, size_t count_students, const Student** const result,
                        size_t* const result_size, const char* target, size_t target_length, CommandType command) {
    switch (command) {
    case FIND_BY_NAME:
        return find_students_by_name(students, count_students, result, result_size, target, target_length);

    case FIND_BY_SURNAME:
        return find_students_by_surname(students, count_students, result, result_size, target, target_length);
    case FIND_BY_GROUP:
        return find_students_by_group(students, count_students, result, result_size, target, target_length);
    default:
        return INVALID_ARG;
    }
}

void sort_base(Student* students, size_t count_students, CommandType command) {
    switch (command) {
        case SORT_BY_ID: sort_by_id(students, count_students); break;
        case SORT_BY_NAME: sort_by_name(students, count_students); break;
        case SORT_BY_SURNAME: sort_by_surname(students, count_students); break;
        case SORT_BY_GROUP: sort_by_group(students, count_students); break;

        default: ;
    }
}

void cleanup_print_by_command(const Student** const result, size_t* const result_size, CommandType command, FILE* stream) {
    switch (command) {
    case FIND_BY_ID:
        print_student_info(*result, stream);
        break;
    case FIND_BY_NAME:
    case FIND_BY_SURNAME:
    case FIND_BY_GROUP:
    case FIND_BY_GRADES:
    case SORT_BY_ID:
    case SORT_BY_NAME:
    case SORT_BY_SURNAME:
    case SORT_BY_GROUP:
        for (size_t i = 0; i < *result_size; ++i) {
            print_student_info(*result + i, stream);
        }
        free((void*)*result);
        *result = NULL;
        *result_size = 0;
        break;
    default: ;
    }
}

Code deep_copy(const Student** const result, size_t* const size, const Student* students, size_t count_students) {
    if (!result) return INVALID_ARG;

    Student* tmp = (Student*)malloc(count_students * sizeof(Student));
    if (!tmp) {
        *result = NULL; *size = 0;
        return MEM_ALLOC;
    }
    for (size_t i = 0; i < count_students; ++i) {
        tmp[i] = students[i];
        size_t len = strlen(students[i].grades);
        tmp[i].grades = malloc((len + 1) * sizeof(char));
        if (!tmp[i].grades) {
            for (size_t j = 0; j < i; ++j) {
                free(tmp[j].grades);
            }
            free(tmp);
            *result = NULL; *size = 0;
            return MEM_ALLOC;
        }
        strncpy(tmp[i].grades, students[i].grades, len);
        tmp[i].grades[len] = 0;
    }
    *result = tmp;
    *size = count_students;
    return SUCCESS;
}

void log(Code code) {
    switch (code) {
    case OUT_OF_RANGE:
        printf("Out of range\n"); break;
    case MEM_ALLOC:
        printf("Out of memory\n"); break;
    case INVALID_ARG:
        printf("Invalid argument\n"); break;
    default: ;
    }
}

void handler(Student* students, size_t count_students, FILE* stream) {
    char buff[128];
    while (fgets(buff, sizeof(buff), stdin)) {
        CommandType command = get_command_type(buff);

        const Student* result = NULL;
        size_t size = 0;

        Code ans = SUCCESS;
        switch (command) {
        case FIND_BY_ID:
            uint32_t id = strtoul(buff + strlen(COMMAND_STRINGS[command]), NULL, 10);
            ans = find_student_by_id(students, count_students, &result, id);
            break;
        case FIND_BY_GRADES:
            ans = find_students_by_grades(students, count_students, &result, &size);
            break;
        case FIND_BY_NAME:
        case FIND_BY_SURNAME:
        case FIND_BY_GROUP:
            char* target = buff + strlen(COMMAND_STRINGS[command]);
            target[strcspn(target, "\n")] = 0;
            ans = find_students_base(students, count_students, &result, &size, target, strlen(target), command);
            break;
        case SORT_BY_ID:
        case SORT_BY_NAME:
        case SORT_BY_SURNAME:
        case SORT_BY_GROUP:
            sort_base(students, count_students, command);
            deep_copy(&result, &size, students, count_students);
            break;

        default:
            printf("Unknown command: %s", buff);
            break;
        }
        log(ans);
        cleanup_print_by_command(&result, &size, command, stream);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 4) {
        printf("Usage: %s <input_filename> <output_filename>\n", argv[0]);
        return 1;
    }
    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        printf("Error opening input_file %s\n", argv[1]);
        return 1;
    }
    FILE* output_file = NULL;
    if (argc == 3)
        output_file = fopen(argv[2], "w");

    Student* students = NULL;
    size_t count_students = 0;
    Code code = create_student_list(input_file, &students, &count_students);
    if (code != SUCCESS) {
        printf("Error creating student list\n");
        return 1;
    }
    handler(students, count_students, output_file);

    for (size_t i = 0; i < count_students; ++i) {
        free(students[i].grades);
    }
    free(students);
    fclose(input_file);
    if (output_file)
        fclose(output_file);
    return 0;
}
