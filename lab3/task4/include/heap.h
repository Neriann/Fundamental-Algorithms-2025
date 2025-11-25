#ifndef HEAP_H
#define HEAP_H


#include <stddef.h>

// Бинарная куча (минимальная по умолчанию)
typedef struct {
    int *data; // массив элементов
    size_t size; // текущее количество элементов
    size_t capacity; // вместимость
} Heap;


// Создание кучи с заданной начальной вместимостью
Heap create_heap(size_t initial_capacity);

// Удаление кучи и освобождение памяти
void delete_heap(Heap *h);

// Проверка, пуста ли куча (1 — пуста, 0 — нет)
int is_empty_heap(const Heap *h);

// Возврат текущего количества элементов
size_t size_heap(const Heap *h);

// Получение элемента с наивысшим приоритетом (минимального) без удаления
int peek_heap(const Heap *h);

// Добавление элемента в кучу
void push_heap(Heap *h, int value);

// Удаление элемента с наивысшим приоритетом (минимального) и возврат его
int pop_heap(Heap *h);

// Построение кучи из массива
Heap build_heap(const int *array, size_t n);

// Сравнение двух куч (лексикографически по массиву внутреннего представления)
// возвращает 1 — равны, 0 — не равны
int is_equal_heap(const Heap *h1, const Heap *h2);

#endif //HEAP_H
