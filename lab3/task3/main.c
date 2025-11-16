#include <stdio.h>
#include <string.h>

#include "liver.h"

#include "list.h" // headers
#include "src/list.i" // implementation


#define FILENAME_SIZE 50
#define BUFFER_SIZE 512

DECLARE_LIST(Liver, Liver)
IMPLEMENT_LIST(Liver, Liver)

#define SORTED_BY BIRTHDAY

typedef enum {
    UNKNOWN = -1,
    EDIT = 0,
    REMOVE = 1,
    ADD = 2,
    FIND,
    PRINT,
    INFO,
    UNDO
} CommandType;

static const char* commands[] = {
    [FIND] = "FindLiver",
    [EDIT] = "EditLiver",
    [REMOVE] = "RemoveLiver",
    [ADD] = "AddLiver",
    [PRINT] = "PrintLivers",
    [UNDO] = "UndoChanges",
    [INFO] = "Info"
};


typedef struct {
    CommandType type;
    Liver* before;
    Liver* after;
} Action;

void* copy_action(const void* p) {
    if (!p) return NULL;

    const Action* action = (const Action*)p;

    Action* new_action = malloc(sizeof(Action));
    if (!new_action) return NULL;

    new_action->type = action->type;
    new_action->before = copy_liver(action->before);
    new_action->after = copy_liver(action->after);
    return new_action;
}

void destroy_action(void* p) {
    if (!p) return;

    Action* action = (Action*)p;
    destroy_liver(action->before);
    destroy_liver(action->after);
    action->before = action->after = NULL;
    action->type = 0;
    free(action);
}

DECLARE_LIST(Action, Action)
IMPLEMENT_LIST(Action, Action)

// Список в котором хранятся отсортировочные значения
static LinkedListLiver* data = NULL;

// Стек для поддержки операции Undo (для него нужны только операции копирования и удаления)
static LinkedListAction* cache_changes = NULL;
// Счетчик изменений
static size_t count_changes = 0;

void op_edit_restore(Action* action) {
    if (!action) return;

    // Ищем позицию на которой находится обновленный житель
    size_t pos = find_list_Liver(data, *action->after, ID);

    // Удаляем его
    delete_at_list_Liver(data, pos);

    // Возвращаем в список старую версию
    ordered_insert_at_list_Liver(data, *action->before, SORTED_BY);
}

void op_remove_restore(Action* action) {
    if (!action) return;

    // Просто вставляем в список
    ordered_insert_at_list_Liver(data, *action->before, SORTED_BY);
}

void op_add_restore(Action* action) {
    if (!action) return;

    // Находим позицию добавленного объекта
    size_t pos = find_list_Liver(data, *action->after, ID);

    // По позиции удаляем его
    delete_at_list_Liver(data, pos);
}

typedef void (*ActionCallback)(Action*);

static ActionCallback action_callbacks[] = {
    [EDIT] = op_edit_restore,
    [REMOVE] = op_remove_restore,
    [ADD] = op_add_restore
};


void print_info_liver(Liver* liver, FILE* stream) {
    fprintf(stream, "ID: %d\n", liver->id);
    fprintf(stream, "Name: %s\n", liver->name);
    fprintf(stream, "Surname: %s\n", liver->surname);
    fprintf(stream, "Patronymic: %s\n", liver->patronymic);
    fprintf(stream, "Birthday: %s\n", liver->birthday);
    fprintf(stream, "Gender: %c\n", liver->gender);
    fprintf(stream, "Average salary: %lf\n", liver->average_salary);

    fflush(stream);
}


void print_info_livers_list(const LinkedListLiver* data, FILE* stream) {
    for (size_t i = 0; i < data->size; ++i) {
        print_info_liver(get_at_list_Liver(data, i), stream);
    }
}

CommandType get_command_type(const char* target, size_t length) {
    for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); ++i) {
        if (strlen(commands[i]) > length) {
            return UNKNOWN;
        }
        if (strcmp(target, commands[i]) == 0) {
            return i;
        }
    }
    return UNKNOWN;
}


int entering_liver(Liver* liver, FILE* fi) {
    if (!liver) return -2;
    printf("<Enter new Liver data>\n");
    printf("<Name>: ");
    if (fscanf(fi, "%s", &liver->name) <= 0) return EOF;
    printf("<Surname>: ");
    if (fscanf(fi, "%s", &liver->surname) <= 0) return EOF;
    printf("<Partonymic>: ");
    if (fscanf(fi, "%s", &liver->patronymic) <= 0) return EOF;
    printf("<Birthday>: ");
    if (fscanf(fi, "%s", &liver->birthday) <= 0) return EOF;
    printf("<Gender>: ");
    if (fscanf(fi, "%s", &liver->gender) <= 0) return EOF;
    printf("<Average salary>: ");
    if (fscanf(fi, "%lf", &liver->average_salary) <= 0) return EOF;
    return 0;
}

int choose_field(Liver* liver, FieldType field, FILE* stream) {
    switch (field) {
        case ID:
            return fscanf(stream, "%d", &liver->id);
        case NAME:
            return fscanf(stream, "%s", liver->name);
        case SURNAME:
            return fscanf(stream, "%s", liver->surname);
        case PATRONYMIC:
            return fscanf(stream, "%s", &liver->patronymic);
        case BIRTHDAY:
            return fscanf(stream, "%s", &liver->birthday);
        case GENDER:
            return fscanf(stream, "%s", &liver->gender);
        case SALARY:
            return fscanf(stream, "%lf", &liver->average_salary);
        default:
            return 0;
    }
}

int choose_field_interactive(Liver* liver, FieldType* field) {
    printf("╔═════╦════════════════════════╗\n");
    printf("║ Keys| Fields                 ║\n");
    printf("╠═════╬════════════════════════╣\n");
    printf("║  0  │ Id                     ║\n");
    printf("║  1  │ Name                   ║\n");
    printf("║  2  │ Surname                ║\n");
    printf("║  3  │ Patronymic             ║\n");
    printf("║  4  │ Birthday               ║\n");
    printf("║  5  │ Gender                 ║\n");
    printf("║  6  │ Average Salary         ║\n");
    printf("╚═════╩════════════════════════╝\n");
    printf("<Choose field (0-6)>: ");
    if (scanf("%d", field) <= 0) return EOF;
    printf("<Enter field value>: ");
    if (choose_field(liver, *field, stdin) <= 0) return EOF;

    return 0;
}


int find_interactive(LinkedListLiver* list) {
    Liver target;
    FieldType field;

    printf("<Enter the key to search for the Liver>\n");
    if (choose_field_interactive(&target, &field) == EOF) return EOF;

    return find_list_Liver(list, target, field);
}


void print_info_program() {
    printf("=== Liver Program Commands ===\n");
    printf("╔═════════════════════════════════════════════════╗\n");
    printf("║ %-12s - Print available program commands ║\n", commands[INFO]);
    printf("║ %-12s - Find first liver the data        ║\n", commands[FIND]);
    printf("║ %-12s - Edit liver the data              ║\n", commands[EDIT]);
    printf("║ %-12s - Remove liver the data            ║\n", commands[REMOVE]);
    printf("║ %-12s - Add new liver the data           ║\n", commands[ADD]);
    printf("║ %-12s - Undo edited changes (last N/2)   ║\n", commands[UNDO]);
    printf("║ %-12s - Print all the data               ║\n", commands[PRINT]);
    printf("╚═════════════════════════════════════════════════╝\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_filename>\n", argv[0]);
        return 1;
    }
    FILE* fi;
    if (!((fi = fopen(argv[1], "r")))) {
        printf("Error opening file\n");
        return 1;
    }
    data = create_list_Liver(copy_liver, compare_liver, destroy_liver, copy_liver_field, compare_liver_one_field);
    cache_changes = create_list_Action(copy_action, NULL, destroy_action, NULL, NULL);
    Liver liver;

    char buff[BUFFER_SIZE];
    while (fgets(buff, sizeof(buff), fi)) {
        if (sscanf(buff, "%d %s %s %s %s %c %lf", &liver.id, &liver.name, &liver.surname, &liver.patronymic, &liver.birthday, &liver.gender, &liver.average_salary) != 7) {
            fprintf(stderr, "Invalid fields of Liver\n");
            delete_list_Liver(&data);
            return 1;
        }
        ordered_insert_at_list_Liver(data, liver, SORTED_BY);
    }

    print_info_program();

    char line[BUFFER_SIZE] = {'1'};
    while (1) {
        printf("<Enter command>: ");
        if (scanf("%s", line) <= 0) {
            break;
        }
        line[strcspn(line, " \n\r\t")] = 0;
        if (!*line) continue;

        CommandType command = get_command_type(line, sizeof(line));
        switch (command) {
        case INFO:
            print_info_program();
            break;
        case FIND:
        {
            int pos = find_interactive(data);

            // проверка на окончание ввода при выполнении команды
            if (pos == EOF) {
                delete_list_Liver(&data);
                return 0;
            }

            if (pos < 0) {
                printf("Error finding Liver in list\n");
                break;
            }
            Liver* finded = get_at_list_Liver(data, pos);
            print_info_liver(finded, stdout);
            break;
        }
        case EDIT:
        {
            int pos = find_interactive(data);

            // проверка на окончание ввода при выполнении команды
            if (pos == EOF) {
                delete_list_Liver(&data);
                return 0;
            }

            if (pos < 0) {
                printf("Error finding Liver to edit in list\n");
                break;
            }
            printf("<Enter the field you want to edit>\n");

            FieldType field;
            Liver target;
            if (choose_field_interactive(&target, &field) == EOF) break;

            if (field == ID) {
                printf("Id is not editable\n");
                break;
            }
            Action action;
            action.type = command;
            action.before = get_at_list_Liver(data, pos);
            action.after = replace_field_list_Liver(data, pos, target, field);

            printf("<Successfully edited Liver>\n");
            print_info_liver(action.after, stdout);

            push_stack_Action(cache_changes, action);
            ++count_changes;
            break;
        }
        case REMOVE:
        {
            int pos = find_interactive(data);

            // проверка на окончание ввода при выполнении команды
            if (pos == EOF) {
                delete_list_Liver(&data);
                return 0;
            }

            if (pos < 0) {
                printf("Error finding Liver to remove in list\n");
                break;
            }
            Action action;
            action.type = command;
            action.before = get_at_list_Liver(data, pos);
            action.after = NULL;
            delete_at_list_Liver(data, pos);

            printf("<Removed Liver>: \n");
            print_info_liver(action.before, stdout);
            push_stack_Action(cache_changes, action);

            ++count_changes;
            break;
        }
        case ADD:
        {
            Liver tmp;
            tmp.id = 0;
            // находим нужный id для нового жителя (первый свободный в порядке возрастания)
            for (; tmp.id < data->size; ++tmp.id) {
                if (find_list_Liver(data, tmp, ID) < 0) {
                    break;
                }
            }
            Liver* new_liver = (Liver*)malloc(sizeof(Liver));
            new_liver->id = tmp.id;
            // проверка на окончание ввода при выполнении команды
            if (entering_liver(new_liver, stdin) == EOF) {
                delete_list_Liver(&data);
                return 0;
            }
            Action action;
            action.type = command;
            action.before = NULL;
            action.after = new_liver;

            ordered_insert_at_list_Liver(data, *new_liver, SORTED_BY);
            printf("Successfully added new liver\n");

            push_stack_Action(cache_changes, action);
            ++count_changes;
            break;
        }
        case PRINT:
        {
            char filename[FILENAME_SIZE];
            printf("<Enter output filename>: ");
            // проверка на окончание ввода
            if (scanf("%s", filename) == EOF) {
                delete_list_Liver(&data);
                return 0;
            }
            FILE* f;
            if (!((f = fopen(filename, "w")))) {
                printf("Error opening file! Repeat the command with the correct filename\n");
                break;
            }
            print_info_livers_list(data, f);
            printf("Successfully saved to %s\n", filename);
            break;
        }
        case UNDO:
        {
            if (!(count_changes / 2)) {
                printf("Not enough changes to undo\n");
                break;
            }
            for (size_t i = 0; i < count_changes / 2; ++i) {
                Action* curr_action = pop_stack_Action(cache_changes);
                ActionCallback func = action_callbacks[curr_action->type];
                func(curr_action);

                destroy_action(curr_action);
            }
            // Забываем оставшиеся в стеке изменения (затираем все поля)
            erase_list_Action(cache_changes);

            count_changes = 0;
            break;
        }
        default:
            printf("Unknown command: %s\n", line);
        }
    }
    if (count_changes || cache_changes->size) {
        erase_list_Action(cache_changes);
    }

    delete_list_Liver(&data);
    delete_list_Action(&cache_changes);

    return 0;
}
