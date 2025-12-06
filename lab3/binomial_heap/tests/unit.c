#include <stdio.h>

#include "assert_base.h"
#include "binomial_heap.h"

// Вспомогательная функция для проверки минимального элемента
void test_create_and_destroy() {
    printf("Test 1: Create and Destroy\n");
    
    BinomialHeap* heap = create_binomial_heap();
    ASSERT_MSG(heap != NULL);
    ASSERT_MSG(heap->head == NULL);
    ASSERT_MSG(heap->size == 0);
    
    destroy_binomial_heap(&heap);
    ASSERT_MSG(heap == NULL);
    
    printf("✓ Test 1 passed\n\n");
}

void test_insert_and_get() {
    printf("Test 2: Insert and Get\n");
    
    BinomialHeap* heap = create_binomial_heap();
    
    // Вставка одного элемента
    insert_binomial_heap(&heap, 10);
    ASSERT_MSG(heap->size == 1);
    ASSERT_MSG(get_binomial_heap(heap) == 10);
    
    // Вставка нескольких элементов
    insert_binomial_heap(&heap, 5);
    ASSERT_MSG(heap->size == 2);
    ASSERT_MSG(get_binomial_heap(heap) == 5); // Минимум
    
    insert_binomial_heap(&heap, 15);
    ASSERT_MSG(heap->size == 3);
    ASSERT_MSG(get_binomial_heap(heap) == 5); // Минимум не изменился
    
    insert_binomial_heap(&heap, 3);
    ASSERT_MSG(heap->size == 4);
    ASSERT_MSG(get_binomial_heap(heap) == 3); // Новый минимум
    
    insert_binomial_heap(&heap, 7);
    ASSERT_MSG(heap->size == 5);
    ASSERT_MSG(get_binomial_heap(heap) == 3);
    
    destroy_binomial_heap(&heap);
    
    printf("✓ Test 2 passed\n\n");
}

void test_extract() {
    printf("Test 3: Extract\n");
    
    BinomialHeap* heap = create_binomial_heap();
    
    // Извлечение из пустой кучи (должно безопасно обрабатываться)
    extract_binomial_heap(&heap);
    ASSERT_MSG(heap->size == 0);
    
    // Вставка элементов
    insert_binomial_heap(&heap, 10);
    insert_binomial_heap(&heap, 5);
    insert_binomial_heap(&heap, 15);
    insert_binomial_heap(&heap, 3);
    insert_binomial_heap(&heap, 7);
    
    ASSERT_MSG(heap->size == 5);
    
    // Последовательное извлечение в порядке возрастания
    ASSERT_MSG(get_binomial_heap(heap) == 3);
    extract_binomial_heap(&heap);
    ASSERT_MSG(heap->size == 4);
    
    ASSERT_MSG(get_binomial_heap(heap) == 5);
    extract_binomial_heap(&heap);
    ASSERT_MSG(heap->size == 3);
    
    ASSERT_MSG(get_binomial_heap(heap) == 7);
    extract_binomial_heap(&heap);
    ASSERT_MSG(heap->size == 2);
    
    ASSERT_MSG(get_binomial_heap(heap) == 10);
    extract_binomial_heap(&heap);
    ASSERT_MSG(heap->size == 1);
    
    ASSERT_MSG(get_binomial_heap(heap) == 15);
    extract_binomial_heap(&heap);
    ASSERT_MSG(heap->size == 0);
    
    destroy_binomial_heap(&heap);
    
    printf("✓ Test 3 passed\n\n");
}

void test_merge() {
    printf("Test 4: Merge\n");
    
    BinomialHeap* heap1 = create_binomial_heap();
    BinomialHeap* heap2 = create_binomial_heap();
    
    // Заполняем первую кучу
    insert_binomial_heap(&heap1, 10);
    insert_binomial_heap(&heap1, 20);
    insert_binomial_heap(&heap1, 5);
    
    // Заполняем вторую кучу
    insert_binomial_heap(&heap2, 15);
    insert_binomial_heap(&heap2, 3);
    insert_binomial_heap(&heap2, 7);
    
    // Объединяем кучи
    BinomialHeap* merged = merge_binomial_heap(heap1, heap2);
    
    ASSERT_MSG(merged != NULL);
    ASSERT_MSG(merged->size == 6);
    
    // Проверяем порядок извлечения
    ASSERT_MSG(get_binomial_heap(merged) == 3); // Минимум из обеих куч
    
    extract_binomial_heap(&merged);
    ASSERT_MSG(get_binomial_heap(merged) == 5);
    
    extract_binomial_heap(&merged);
    ASSERT_MSG(get_binomial_heap(merged) == 7);
    
    extract_binomial_heap(&merged);
    ASSERT_MSG(get_binomial_heap(merged) == 10);
    
    extract_binomial_heap(&merged);
    ASSERT_MSG(get_binomial_heap(merged) == 15);
    
    extract_binomial_heap(&merged);
    ASSERT_MSG(get_binomial_heap(merged) == 20);
    
    extract_binomial_heap(&merged);
    ASSERT_MSG(merged->size == 0);
    
    destroy_binomial_heap(&heap1);
    destroy_binomial_heap(&heap2);
    destroy_binomial_heap(&merged);
    
    printf("✓ Test 4 passed\n\n");
}

void test_meld() {
    printf("Test 5: Meld (деструктивное объединение)\n");
    
    BinomialHeap* heap1 = create_binomial_heap();
    BinomialHeap* heap2 = create_binomial_heap();
    
    insert_binomial_heap(&heap1, 10);
    insert_binomial_heap(&heap1, 20);
    insert_binomial_heap(&heap1, 5);
    
    insert_binomial_heap(&heap2, 15);
    insert_binomial_heap(&heap2, 3);
    insert_binomial_heap(&heap2, 7);
    
    int size1 = heap1->size;
    int size2 = heap2->size;
    
    // Деструктивное объединение
    meld_binomial_heap(&heap1, &heap2);
    
    ASSERT_MSG(heap1 != NULL);
    ASSERT_MSG(heap1->size == size1 + size2); // Все элементы в heap1
    ASSERT_MSG(heap2 == NULL); // heap2 должен быть уничтожен
    
    // Проверяем порядок
    ASSERT_MSG(get_binomial_heap(heap1) == 3);
    extract_binomial_heap(&heap1);
    ASSERT_MSG(get_binomial_heap(heap1) == 5);
    extract_binomial_heap(&heap1);
    ASSERT_MSG(get_binomial_heap(heap1) == 7);
    extract_binomial_heap(&heap1);
    ASSERT_MSG(get_binomial_heap(heap1) == 10);
    extract_binomial_heap(&heap1);
    ASSERT_MSG(get_binomial_heap(heap1) == 15);
    extract_binomial_heap(&heap1);
    ASSERT_MSG(get_binomial_heap(heap1) == 20);
    
    destroy_binomial_heap(&heap1);
    
    printf("✓ Test 5 passed\n\n");
}

void test_copy() {
    printf("Test 6: Copy\n");
    
    BinomialHeap* original = create_binomial_heap();
    
    insert_binomial_heap(&original, 10);
    insert_binomial_heap(&original, 5);
    insert_binomial_heap(&original, 15);
    insert_binomial_heap(&original, 3);
    insert_binomial_heap(&original, 7);
    
    // Тестируем копирование
    BinomialHeap* copy = copy_binomial_heap(original);
    
    ASSERT_MSG(copy != NULL);
    ASSERT_MSG(copy != original); // Должны быть разные объекты
    ASSERT_MSG(copy->size == original->size);
    
    // Извлекаем из копии, оригинал не должен измениться
    extract_binomial_heap(&copy);
    ASSERT_MSG(copy->size == 4);
    ASSERT_MSG(original->size == 5); // Оригинал не изменился
    
    // Проверяем, что минимум в оригинале остался прежним
    ASSERT_MSG(get_binomial_heap(original) == 3);
    
    destroy_binomial_heap(&original);
    destroy_binomial_heap(&copy);
    
    printf("✓ Test 6 passed\n\n");
}

void test_copy_assignment() {
    printf("Test 7: Copy Assignment\n");
    
    BinomialHeap* heap1 = create_binomial_heap();
    BinomialHeap* heap2 = create_binomial_heap();
    
    insert_binomial_heap(&heap1, 10);
    insert_binomial_heap(&heap1, 5);
    
    insert_binomial_heap(&heap2, 20);
    insert_binomial_heap(&heap2, 15);
    insert_binomial_heap(&heap2, 25);
    
    // Присваиваем heap1 значение heap2
    copy_assignment_binomial_heap(&heap1, heap2);
    
    ASSERT_MSG(heap1->size == heap2->size);
    
    // Изменяем heap2, heap1 не должен измениться
    insert_binomial_heap(&heap2, 100);
    ASSERT_MSG(heap2->size == 4);
    ASSERT_MSG(heap1->size == 3); // heap1 не изменился
    
    destroy_binomial_heap(&heap1);
    destroy_binomial_heap(&heap2);
    
    printf("✓ Test 7 passed\n\n");
}


void test_edge_cases() {
    printf("Test 8: Edge Cases\n");
    
    // Пустая куча
    BinomialHeap* heap = create_binomial_heap();
    ASSERT_MSG(heap->size == 0);
    
    // Вставка и извлечение одного элемента
    insert_binomial_heap(&heap, 42);
    ASSERT_MSG(heap->size == 1);
    ASSERT_MSG(get_binomial_heap(heap) == 42);
    extract_binomial_heap(&heap);
    ASSERT_MSG(heap->size == 0);
    
    // Вставка одинаковых элементов
    insert_binomial_heap(&heap, 10);
    insert_binomial_heap(&heap, 10);
    insert_binomial_heap(&heap, 10);
    ASSERT_MSG(heap->size == 3);
    
    extract_binomial_heap(&heap);
    extract_binomial_heap(&heap);
    extract_binomial_heap(&heap);
    ASSERT_MSG(heap->size == 0);
    
    // Слияние с пустой кучей
    BinomialHeap* heap2 = create_binomial_heap();
    insert_binomial_heap(&heap, 1);
    insert_binomial_heap(&heap, 2);
    insert_binomial_heap(&heap, 3);
    
    BinomialHeap* merged1 = merge_binomial_heap(heap, heap2);
    ASSERT_MSG(merged1->size == 3);
    
    BinomialHeap* merged2 = merge_binomial_heap(heap2, heap);
    ASSERT_MSG(merged2->size == 3);
    
    destroy_binomial_heap(&heap);
    destroy_binomial_heap(&heap2);
    destroy_binomial_heap(&merged1);
    destroy_binomial_heap(&merged2);
    
    printf("✓ Test 8 passed\n\n");
}

void test_large_heap() {
    printf("Test 9: Large Heap\n");
    
    BinomialHeap* heap = create_binomial_heap();
    
    // Вставляем много элементов в случайном порядке
    int elements[] = {23, 1, 45, 67, 3, 99, 12, 56, 78, 34};
    int n = sizeof(elements) / sizeof(elements[0]);
    
    for (int i = 0; i < n; i++) {
        insert_binomial_heap(&heap, elements[i]);
    }
    
    ASSERT_MSG(heap->size == n);
    
    // Извлекаем и проверяем порядок (по возрастанию)
    int prev = get_binomial_heap(heap);
    extract_binomial_heap(&heap);
    
    while (heap->size > 0) {
        int current = get_binomial_heap(heap);
        ASSERT_MSG(prev <= current); // Для min-heap
        extract_binomial_heap(&heap);
        prev = current;
    }
    
    destroy_binomial_heap(&heap);
    
    printf("✓ Test 9 passed\n\n");
}

int main() {
    printf("=== Running Binomial Heap Tests ===\n\n");
    
    test_create_and_destroy();
    test_insert_and_get();
    test_extract();
    test_merge();
    test_meld();
    test_copy();
    test_copy_assignment();
    test_edge_cases();
    test_large_heap();
    
    printf("=== All tests completed ===\n");
    
    return 0;
}
