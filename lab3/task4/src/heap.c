#include "heap.h"

#include <stdlib.h>
#include <string.h>


#define CAPACITY_BASE 10

// Создание кучи с заданной начальной вместимостью
Heap create_heap(size_t initial_capacity) {
    Heap heap;
    heap.capacity = initial_capacity > CAPACITY_BASE ? initial_capacity : CAPACITY_BASE;
    heap.size = 0;
    heap.data = (int*)malloc(heap.capacity * sizeof(int));
    return heap;
}

// Удаление кучи и освобождение памяти
void delete_heap(Heap *h) {
    h->capacity = h->size = 0;
    free(h->data);
    h->data = NULL;
}

// Проверка, пуста ли куча (1 — пуста, 0 — нет)
int is_empty_heap(const Heap *h) {
    if (!h || !h->data) return 1;

    return !h->size;
}

// Возврат текущего количества элементов
size_t size_heap(const Heap *h) {
    if (is_empty_heap(h)) return 0;

    return h->size;
}

// Получение элемента с наивысшим приоритетом (минимального) без удаления
int peek_heap(const Heap *h) {
    if (is_empty_heap(h)) return 0;

    return h->data[0];
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int compare_heap(int a, int b) {
    if (a == b) return 0;
    if (a < b) return -1;
    return 1;
}

// Добавление элемента в кучу
void push_heap(Heap *h, int value) {
    if (is_empty_heap(h)) {
        h->data[h->size++] = value;
        return;
    }

    if (h->size >= h->capacity) {
        size_t new_capacity = 2 * h->capacity;
        int* new_data = (int*)realloc(h->data, new_capacity * sizeof(int));
        if (!new_data) return;

        h->capacity = new_capacity;
        h->data = new_data;
    }

    size_t id = h->size++;

    h->data[id] = value;
    while (id > 0) {
        if (compare_heap(h->data[(id - 1) / 2], h->data[id]) <= 0) {
            break;
        }
        swap(&h->data[id], &h->data[(id - 1) / 2]);
        id = (id - 1) / 2;
    }
}

void sifting(Heap* h, size_t id) {
    while (2 * id + 1 < h->size) {
        size_t left = 2 * id + 1;
        size_t right = 2 * id + 2;

        size_t target_child = left;

        if (right < h->size && compare_heap(h->data[left], h->data[right]) >= 0) {
            target_child = right;
        }

        if (compare_heap(h->data[id], h->data[target_child]) <= 0) {
            break;
        }
        swap(&h->data[target_child], &h->data[id]);
        id = target_child;
    }
}

// Удаление элемента с наивысшим приоритетом (минимального) и возврат его
int pop_heap(Heap *h) {
    if (is_empty_heap(h)) return 0;

    int value = h->data[0];
    swap(&h->data[0], &h->data[h->size - 1]);
    --h->size;

    sifting(h, 0);

    return value;
}

// Построение кучи из массива
Heap build_heap(const int *array, size_t n) {
    if (!array || !n) return create_heap(0);

    Heap heap = create_heap(n);

    memcpy(heap.data, array, n * sizeof(int));
    heap.size = n;
    heap.capacity = n > CAPACITY_BASE ? n : CAPACITY_BASE;

    for (int i = (int)n / 2 - 1; i >= 0; --i) {
        sifting(&heap, i);
    }
    return heap;
}

// Сравнение двух куч (лексикографически по массиву внутреннего представления)
// возвращает 1 — равны, 0 — не равны
int is_equal_heap(const Heap *h1, const Heap *h2) {
    if (size_heap(h1) != size_heap(h2)) return 0;

    for (size_t i = 0; i < size_heap(h1); ++i) {
        if (compare_heap(h1->data[i], h2->data[i]) != 0) return 0;
    }
    return 1;
}
