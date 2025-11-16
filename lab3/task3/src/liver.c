#include "liver.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

void* copy_liver(const void* liver) {
    if (!liver)
        return NULL;

    Liver* new_liver = malloc(sizeof(Liver));
    memcpy(new_liver, liver, sizeof(Liver));
    return (void*)new_liver;
}

void copy_liver_field(void* dest, const void* src, size_t field) {
    if (!src || !dest)
        return;

    Liver* from = (Liver*)src;
    Liver* to = (Liver*)dest;
    switch (field) {
    case ID:
        to->id = from->id;
        break;
    case NAME:
        strcpy(to->name, from->name);
        break;
    case SURNAME:
        strcpy(to->surname, from->surname);
        break;
    case PATRONYMIC:
        strcpy(to->patronymic, from->patronymic);
        break;
    case BIRTHDAY:
        strcpy(to->birthday, from->birthday);
        break;
    case GENDER:
        to->gender = from->gender;
        break;
    case SALARY:
        to->average_salary = from->average_salary;
        break;
    default: ;
    }
}

int compare_liver(const void* lhs, const void* rhs) {
    if (!lhs || !rhs)
        return 0;

    const Liver* l1 = (const Liver*)lhs;
    const Liver* l2 = (const Liver*)rhs;
    return l1->id == l2->id && !strcmp(l1->name, l2->name) && !strcmp(l1->surname, l2->surname) && !strcmp(
            l1->patronymic, l2->patronymic) &&
        !strcmp(l1->birthday, l2->birthday) && l1->gender == l2->gender && fabs(l1->average_salary - l2->average_salary)
        < EPS;
}

// 0 - равны, 1 - не равны
int compare_liver_one_field(const void* l1, const void* l2, size_t field) {
    if (!l1 || !l2) return 0;

    Liver* a = (Liver*)l1;
    Liver* b = (Liver*)l2;
    switch (field) {
    case ID:
        if (a->id < b->id) return -1;
        if (a->id > b->id) return 1;
        return 0;
    case NAME:
        return strcmp(a->name, b->name);
    case SURNAME:
        return strcmp(a->surname, b->surname);
    case PATRONYMIC:
        return strcmp(a->patronymic, b->patronymic);
    case BIRTHDAY:
        return strcmp(a->birthday, b->birthday);
    case GENDER:
        if (a->gender < b->gender) return -1;
        if (a->gender > b->gender) return 1;
        return 0;
    case SALARY:
        if (a->average_salary < b->average_salary) return -1;
        if (a->average_salary > b->average_salary) return 1;
        return 0;
    default: ;
    }
    return 0;
}

void destroy_liver(void* liver) {
    free(liver);
}
