#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "assert_base.h"

// Вспомогательная функция для проверки свойства кучи
int is_valid_min_heap(const Heap* h) {
    for (size_t i = 0; i < h->size; i++) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        
        if (left < h->size && h->data[i] > h->data[left]) {
            return 0;
        }
        if (right < h->size && h->data[i] > h->data[right]) {
            return 0;
        }
    }
    return 1;
}

void test_create_delete_heap() {
    printf("\n=== Test create/delete heap ===\n");
    
    Heap h = create_heap(5);
    _ASSERT_MSG(h.data != NULL, "Heap data should not be NULL");
    _ASSERT_MSG(h.capacity == 10, "Capacity should be 10, got %zu", h.capacity);
    _ASSERT_MSG(h.size == 0, "Size should be 0, got %zu", h.size);
    
    delete_heap(&h);
    _ASSERT_MSG(h.data == NULL, "Heap data should be NULL after deletion");
    _ASSERT_MSG(h.size == 0, "Size should be 0 after deletion");
    _ASSERT_MSG(h.capacity == 0, "Capacity should be 0 after deletion");
}

void test_is_empty() {
    printf("\n=== Test is_empty ===\n");
    
    Heap h = create_heap(5);
    _ASSERT_MSG(is_empty_heap(&h) == 1, "New heap should be empty");
    
    push_heap(&h, 42);
    _ASSERT_MSG(is_empty_heap(&h) == 0, "Heap with elements should not be empty");
    
    pop_heap(&h);
    _ASSERT_MSG(is_empty_heap(&h) == 1, "Heap should be empty after popping all elements");
    
    delete_heap(&h);
}

void test_push_peek() {
    printf("\n=== Test push/peek ===\n");
    
    Heap h = create_heap(5);
    
    push_heap(&h, 30);
    _ASSERT_MSG(peek_heap(&h) == 30, "Peek should return 30, got %d", peek_heap(&h));
    _ASSERT_MSG(is_valid_min_heap(&h), "Heap should maintain min-heap property");
    
    push_heap(&h, 20);
    _ASSERT_MSG(peek_heap(&h) == 20, "Peek should return 20, got %d", peek_heap(&h));
    _ASSERT_MSG(is_valid_min_heap(&h), "Heap should maintain min-heap property");
    
    push_heap(&h, 10);
    _ASSERT_MSG(peek_heap(&h) == 10, "Peek should return 10, got %d", peek_heap(&h));
    _ASSERT_MSG(is_valid_min_heap(&h), "Heap should maintain min-heap property");
    
    push_heap(&h, 40);
    _ASSERT_MSG(peek_heap(&h) == 10, "Peek should still return 10, got %d", peek_heap(&h));
    _ASSERT_MSG(is_valid_min_heap(&h), "Heap should maintain min-heap property");
    
    delete_heap(&h);
}

void test_pop() {
    printf("\n=== Test pop ===\n");
    
    Heap h = create_heap(10);
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    
    for (size_t i = 0; i < 7; i++) {
        push_heap(&h, values[i]);
    }
    
    _ASSERT_MSG(is_valid_min_heap(&h), "Heap should be valid before popping");
    
    int expected_order[] = {20, 30, 40, 50, 60, 70, 80};
    for (size_t i = 0; i < 7; i++) {
        int popped = pop_heap(&h);
        _ASSERT_MSG(popped == expected_order[i], 
                   "Pop #%zu: expected %d, got %d", i + 1, expected_order[i], popped);
        _ASSERT_MSG(is_valid_min_heap(&h) || h.size == 0, 
                   "Heap should maintain min-heap property after pop");
    }
    
    _ASSERT_MSG(is_empty_heap(&h), "Heap should be empty after popping all elements");
    
    delete_heap(&h);
}

void test_build_heap() {
    printf("\n=== Test build_heap ===\n");
    
    int array[] = {9, 5, 7, 1, 3, 2, 8, 6, 4};
    size_t n = sizeof(array) / sizeof(array[0]);
    
    Heap h = build_heap(array, n);
    
    _ASSERT_MSG(h.size == n, "Heap size should be %zu, got %zu", n, h.size);
    _ASSERT_MSG(is_valid_min_heap(&h), "Built heap should be valid min-heap");
    _ASSERT_MSG(peek_heap(&h) == 1, "Min element should be 1, got %d", peek_heap(&h));
    
    // Проверяем, что все элементы присутствуют
    int sorted[n];
    for (size_t i = 0; i < n; i++) {
        sorted[i] = pop_heap(&h);
        if (i > 0) {
            _ASSERT_MSG(sorted[i] >= sorted[i-1], 
                       "Elements should be popped in increasing order");
        }
    }
    
    delete_heap(&h);
}

void test_size_heap() {
    printf("\n=== Test size_heap ===\n");
    
    Heap h = create_heap(10);
    
    _ASSERT_MSG(size_heap(&h) == 0, "Initial size should be 0, got %zu", size_heap(&h));
    
    push_heap(&h, 1);
    _ASSERT_MSG(size_heap(&h) == 1, "Size should be 1 after push, got %zu", size_heap(&h));
    
    push_heap(&h, 2);
    push_heap(&h, 3);
    _ASSERT_MSG(size_heap(&h) == 3, "Size should be 3 after 3 pushes, got %zu", size_heap(&h));
    
    pop_heap(&h);
    _ASSERT_MSG(size_heap(&h) == 2, "Size should be 2 after pop, got %zu", size_heap(&h));
    
    delete_heap(&h);
}

void test_is_equal_heap() {
    printf("\n=== Test is_equal_heap ===\n");
    
    Heap h1 = create_heap(10);
    Heap h2 = create_heap(10);
    
    // Пустые кучи
    _ASSERT_MSG(is_equal_heap(&h1, &h2) == 1, "Empty heaps should be equal");
    
    // Кучи с одинаковыми элементами
    push_heap(&h1, 5);
    push_heap(&h1, 3);
    push_heap(&h1, 7);
    
    push_heap(&h2, 5);
    push_heap(&h2, 3);
    push_heap(&h2, 7);
    
    _ASSERT_MSG(is_equal_heap(&h1, &h2) == 1, "Heaps with same elements should be equal");
    
    // Кучи с разными элементами
    Heap h3 = create_heap(10);
    push_heap(&h3, 5);
    push_heap(&h3, 3);
    push_heap(&h3, 8); // отличается от h1
    
    _ASSERT_MSG(is_equal_heap(&h1, &h3) == 0, "Heaps with different elements should not be equal");
    
    // Кучи разного размера
    Heap h4 = create_heap(10);
    push_heap(&h4, 5);
    push_heap(&h4, 3);
    
    _ASSERT_MSG(is_equal_heap(&h1, &h4) == 0, "Heaps of different sizes should not be equal");
    
    delete_heap(&h1);
    delete_heap(&h2);
    delete_heap(&h3);
    delete_heap(&h4);
}

void test_resize_capacity() {
    printf("\n=== Test resize capacity ===\n");
    
    Heap h = create_heap(2);
    
    _ASSERT_MSG(h.capacity == 10, "Initial capacity should be 2, got %zu", h.capacity);
    
    // Добавляем больше элементов, чем начальная вместимость
    for (int i = 0; i < 12; i++) {
        push_heap(&h, i * 10);
        _ASSERT_MSG(is_valid_min_heap(&h), "Heap should remain valid during pushes");
    }
    
    _ASSERT_MSG(h.size == 12, "Size should be 12, got %zu", h.size);
    _ASSERT_MSG(h.capacity == 20, "Capacity should be 20, got %zu", h.capacity);
    
    delete_heap(&h);
}

void test_duplicate_values() {
    printf("\n=== Test duplicate values ===\n");
    
    Heap h = create_heap(10);
    
    int duplicates[] = {5, 3, 5, 1, 3, 1, 5};
    for (size_t i = 0; i < 7; i++) {
        push_heap(&h, duplicates[i]);
        _ASSERT_MSG(is_valid_min_heap(&h), "Heap should remain valid with duplicates");
    }
    
    _ASSERT_MSG(peek_heap(&h) == 1, "Min should be 1 with duplicates");
    
    // Проверяем порядок извлечения
    int prev = pop_heap(&h);
    while (!is_empty_heap(&h)) {
        int current = pop_heap(&h);
        _ASSERT_MSG(current >= prev, "Elements should be popped in non-decreasing order");
        prev = current;
    }
    
    delete_heap(&h);
}

void test_edge_cases() {
    printf("\n=== Test edge cases ===\n");
    
    // Создание кучи с capacity = 0
    Heap h1 = create_heap(0);
    _ASSERT_MSG(h1.capacity > 0, "Heap with 0 capacity should be adjusted to positive");
    delete_heap(&h1);
    
    // Построение кучи из пустого массива
    Heap h2 = build_heap(NULL, 0);
    _ASSERT_MSG(h2.size == 0, "Heap from empty array should have size 0");
    _ASSERT_MSG(is_empty_heap(&h2) == 1, "Heap from empty array should be empty");
    delete_heap(&h2);
    
    // Построение кучи из массива с одним элементом
    int single[] = {42};
    Heap h3 = build_heap(single, 1);
    _ASSERT_MSG(h3.size == 1, "Heap from single element should have size 1");
    _ASSERT_MSG(peek_heap(&h3) == 42, "Peek should return 42");
    delete_heap(&h3);
}

int main() {
    printf("Starting Heap Tests...\n");
    
    test_create_delete_heap();
    test_is_empty();
    test_push_peek();
    test_pop();
    test_build_heap();
    test_size_heap();
    test_is_equal_heap();
    test_resize_capacity();
    test_duplicate_values();
    test_edge_cases();
    
    printf("\n=== All tests passed! ===\n");
    return 0;
}
