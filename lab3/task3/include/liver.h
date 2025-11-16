#ifndef LIVER_H
#define LIVER_H

#include <stddef.h>

#include "stdint.h"

#define NAME_SIZE 101
#define BIRTHDAY_SIZE 11


#define EPS 1e-3

typedef enum {
    ID = 0,
    NAME,
    SURNAME,
    PATRONYMIC,
    BIRTHDAY,
    GENDER,
    SALARY
} FieldType;

typedef struct {
    uint32_t id;
    char name[NAME_SIZE];
    char surname[NAME_SIZE];
    char patronymic[NAME_SIZE];
    char birthday[BIRTHDAY_SIZE];
    char gender;
    double average_salary;
} Liver;


void* copy_liver(const void* liver);

void copy_liver_field(void* dest, const void* src, size_t field);

int compare_liver(const void* l1, const void* l2);

int compare_liver_one_field(const void* l1, const void* l2, size_t field);

void destroy_liver(void* liver);

#endif //LIVER_H
