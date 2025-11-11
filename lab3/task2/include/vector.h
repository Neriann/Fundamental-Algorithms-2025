#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BASE_CAPACITY 10

#define DECLARE_VECTOR(VECTOR_TYPE) \
    typedef struct { \
        VECTOR_TYPE* data; \
        size_t size; \
        size_t capacity; \
        VECTOR_TYPE (*CopyVoidPtr)(VECTOR_TYPE); \
        int (*CompareVoidPtr)(VECTOR_TYPE, VECTOR_TYPE); \
        void (*DeleteVoidPtr)(VECTOR_TYPE); \
    } Vector; \
    \
    Vector* create_vector(size_t initial_capacity, VECTOR_TYPE(* CopyFunc)(VECTOR_TYPE), int (*CompareFunc)(VECTOR_TYPE, VECTOR_TYPE), void (*DeleteFunc)(VECTOR_TYPE)); \
    \
    void erase_vector(Vector* v); \
     \
    int is_equal_vector(const Vector* v1, const Vector* v2); \
    \
    void copy_vector(Vector* dest, const Vector* src); \
    \
    Vector* copy_vector_new(const Vector* src); \
    \
    void push_back_vector(Vector* v, VECTOR_TYPE value); \
    \
    void delete_at_vector(Vector* v, size_t index); \
    \
    VECTOR_TYPE get_at_vector(const Vector* v, size_t index); \
    \
    void delete_vector(Vector** v);



#define IMPLEMENT_VECTOR(VECTOR_TYPE) \
Vector* create_vector(size_t initial_capacity, VECTOR_TYPE(* CopyFunc)(VECTOR_TYPE), int (*CompareFunc)(VECTOR_TYPE, VECTOR_TYPE), void (*DeleteFunc)(VECTOR_TYPE)) { \
    if (!CopyFunc || !CompareFunc || !DeleteFunc) { \
        fprintf(stderr, "Invalid function pointer\n"); \
        return NULL; \
    } \
    Vector* vec = (Vector*) malloc(sizeof(Vector));  \
    if (!vec) { \
        fprintf(stderr, "Failed to allocate memory for vector\n"); \
        return NULL; \
    } \
    \
    vec->capacity = (initial_capacity > BASE_CAPACITY) ? initial_capacity : BASE_CAPACITY; \
    vec->size = 0; \
    vec->CopyVoidPtr = CopyFunc; \
    vec->CompareVoidPtr = CompareFunc; \
    vec->DeleteVoidPtr = DeleteFunc; \
    vec->data = (VECTOR_TYPE*) malloc(vec->capacity * sizeof(VECTOR_TYPE)); \
    if (!vec->data) { \
        fprintf(stderr, "Failed to allocate memory for data\n"); \
        return NULL; \
    } \
    return vec; \
} \
\
void erase_vector(Vector* v) { \
    if (v) { \
        for (size_t i = 0; i < v->size; ++i) { \
            v->DeleteVoidPtr(v->data[i]); \
        } \
        free(v->data); \
        v->data = NULL; \
        v->size = 0; v->capacity = 0; \
    } \
} \
 \
int is_equal_vector(const Vector* v1, const Vector* v2) { \
    if (!v1 || !v2) return 0; \
    \
    if (v1->size != v2->size) return 0; \
 \
    if (v1->CompareVoidPtr != v2->CompareVoidPtr) { \
        return 0; \
    } \
    \
    for (size_t i = 0; i < v1->size; ++i) { \
        if (!v1->CompareVoidPtr(v1->data[i], v2->data[i])) return 0; \
    } \
    return 1; \
} \
 \
void copy_vector(Vector* dest, const Vector* src) { \
    if (!dest || !src) return; \
 \
    if (dest == src) return; \
 \
    free(dest->data); \
\
    dest->data = (VECTOR_TYPE*) malloc(src->capacity * sizeof(VECTOR_TYPE)); \
    if (!dest->data) { \
        fprintf(stderr, "Failed to allocate memory for data\n"); \
        return; \
    } \
    for (size_t i = 0; i < src->size; ++i) { \
        dest->data[i] = src->CopyVoidPtr(src->data[i]); \
    } \
    dest->size = src->size; \
    dest->capacity = src->capacity; \
    dest->CopyVoidPtr = src->CopyVoidPtr; \
    dest->CompareVoidPtr = src->CompareVoidPtr; \
    dest->DeleteVoidPtr = src->DeleteVoidPtr; \
} \
 \
Vector* copy_vector_new(const Vector* src) { \
    if (!src) { \
        fprintf(stderr, "Invalid function pointer\n"); \
        return NULL; \
    }; \
    Vector* dest = (Vector*) malloc(sizeof(Vector)); \
    if (!dest) { \
        fprintf(stderr, "Failed to allocate memory for vector\n"); \
        return NULL; \
    } \
    \
    dest->data = (VECTOR_TYPE*) malloc(src->capacity * sizeof(VECTOR_TYPE)); \
    if (!dest->data) { \
        fprintf(stderr, "Failed to allocate memory for data\n"); \
        free(dest); \
        return NULL; \
    } \
    for (size_t i = 0; i < src->size; ++i) { \
        dest->data[i] = src->CopyVoidPtr(src->data[i]); \
    } \
    dest->size = src->size; \
    dest->capacity = src->capacity; \
    dest->CopyVoidPtr = src->CopyVoidPtr; \
    dest->CompareVoidPtr = src->CompareVoidPtr; \
    dest->DeleteVoidPtr = src->DeleteVoidPtr; \
    return dest; \
} \
 \
void push_back_vector(Vector* v, VECTOR_TYPE value) { \
    if (!v) { \
        fprintf(stderr, "Invalid function pointer\n"); \
        return; \
    } \
    \
    if (v->size >= v->capacity) { \
        v->capacity = (v->capacity == 0) ? 1 : v->capacity * 2; \
        VECTOR_TYPE* new_v = (VECTOR_TYPE*) realloc(v->data, v->capacity * sizeof(VECTOR_TYPE)); \
        if (!new_v) { \
            fprintf(stderr, "Failed to reallocate memory for vector\n"); \
            return; \
        }\
        v->data = new_v; \
    } \
 \
    v->data[v->size++] = v->CopyVoidPtr(value); \
} \
 \
void delete_at_vector(Vector* v, size_t index) { \
    if (!v) { \
        fprintf(stderr, "Invalid function pointer\n"); \
        return; \
    } \
    if (index >= v->size) { \
        perror("Index out of bounds\n"); \
        return; \
    } \
    v->DeleteVoidPtr(v->data[index]); \
    for (size_t i = index + 1; i < v->size; ++i) { \
        v->data[i - 1] = v->data[i]; \
    } \
    --v->size; \
} \
 \
VECTOR_TYPE get_at_vector(const Vector* v, size_t index) { \
    if (!v) { \
        fprintf(stderr, "Invalid function pointer\n"); \
        VECTOR_TYPE empty = {}; \
        return empty; \
    } \
    if (index >= v->size) { \
        fprintf(stderr, "Index out of bounds\n"); \
        VECTOR_TYPE empty = {}; \
        return empty; \
    } \
 \
    return v->data[index]; \
} \
 \
void delete_vector(Vector** v) { \
    if (v && *v) { \
        erase_vector(*v); \
        free(*v); \
        *v = NULL; \
    } \
}

#endif //VECTOR_H
