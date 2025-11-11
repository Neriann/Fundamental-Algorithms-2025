#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "assert_base.h"

// Объявляем вектор для int
DECLARE_VECTOR(int)
IMPLEMENT_VECTOR(int)

// Функции копирования и удаления для int
int CopyInt(int value) {
    return value; // Для int просто возвращаем значение
}

int CompareInt(int a, int b) {
    return a == b;
}

void DeleteInt(int value) {
    // Для int не нужно освобождать память
    (void)value;
}

void test_create_and_destroy() {
    printf("\n=== Test 1: Create and Destroy ===\n");
    Vector* v = create_vector(10, CopyInt, CompareInt, DeleteInt);

    _ASSERT_MSG(v->data != NULL, "Vector data should not be NULL");
    _ASSERT_MSG(v->size == 0, "Initial size should be 0, got %zu", v->size);
    _ASSERT_MSG(v->capacity >= 10, "Capacity should be at least 10, got %zu", v->capacity);
    _ASSERT_MSG(v->CopyVoidPtr == CopyInt, "Copy function should be set correctly");
    _ASSERT_MSG(v->DeleteVoidPtr == DeleteInt, "Delete function should be set correctly");

    erase_vector(v);
    _ASSERT_MSG(v->data == NULL, "After erase, data should be NULL");
    _ASSERT_MSG(v->size == 0, "After erase, size should be 0");
    _ASSERT_MSG(v->capacity == 0, "After erase, capacity should be 0");

    delete_vector(&v);
    _ASSERT_MSG(v == NULL, "After delete, data should be NULL");
}

void test_push_back() {
    printf("\n=== Test 2: Push Back ===\n");
    Vector* v = create_vector(2, CopyInt, CompareInt, DeleteInt);

    // Добавляем элементы
    push_back_vector(v, 10);
    push_back_vector(v, 20);
    push_back_vector(v, 30); // Должно вызвать реаллокацию

    _ASSERT_MSG(v->size == 3, "Size should be 3 after 3 pushes, got %zu", v->size);
    _ASSERT_MSG(v->capacity >= 3, "Capacity should be at least 3, got %zu", v->capacity);
    _ASSERT_MSG(get_at_vector(v, 0) == 10, "First element should be 10, got %d", get_at_vector(v, 0));
    _ASSERT_MSG(get_at_vector(v, 1) == 20, "Second element should be 20, got %d", get_at_vector(v, 1));
    _ASSERT_MSG(get_at_vector(v, 2) == 30, "Third element should be 30, got %d", get_at_vector(v, 2));

    delete_vector(&v);
}

void test_delete_at() {
    printf("\n=== Test 3: Delete At ===\n");
    Vector* v = create_vector(5, CopyInt, CompareInt, DeleteInt);

    push_back_vector(v, 100);
    push_back_vector(v, 200);
    push_back_vector(v, 300);
    push_back_vector(v, 400);

    // Удаляем элемент в середине
    delete_at_vector(v, 1);
    _ASSERT_MSG(v->size == 3, "Size should be 3 after deletion, got %zu", v->size);
    _ASSERT_MSG(get_at_vector(v, 0) == 100, "First element should remain 100");
    _ASSERT_MSG(get_at_vector(v, 1) == 300, "Second element should now be 300");
    _ASSERT_MSG(get_at_vector(v, 2) == 400, "Third element should remain 400");

    // Удаляем первый элемент
    delete_at_vector(v, 0);
    _ASSERT_MSG(v->size == 2, "Size should be 2 after second deletion");
    _ASSERT_MSG(get_at_vector(v, 0) == 300, "First element should now be 300");
    _ASSERT_MSG(get_at_vector(v, 1) == 400, "Second element should remain 400");

    // Удаляем последний элемент
    delete_at_vector(v, 1);
    _ASSERT_MSG(v->size == 1, "Size should be 1 after third deletion");
    _ASSERT_MSG(get_at_vector(v, 0) == 300, "First element should now be 300");

    delete_vector(&v);
}

void test_copy_operations() {
    printf("\n=== Test 4: Copy Operations ===\n");
    Vector* original = create_vector(5, CopyInt, CompareInt, DeleteInt);

    push_back_vector(original, 1);
    push_back_vector(original, 2);
    push_back_vector(original, 3);

    // Тестируем copy_vector
    Vector* copy = create_vector(0, CopyInt, CompareInt, DeleteInt);
    copy_vector(copy, original);

    _ASSERT_MSG(is_equal_vector(original, copy), "Copied vector should be equal to original");
    _ASSERT_MSG(copy->size == original->size, "Copy size should match original");
    _ASSERT_MSG(copy->capacity == original->capacity, "Copy capacity should match original");

    // Изменяем копию и проверяем, что оригинал не изменился
    push_back_vector(copy, 999);
    _ASSERT_MSG(!is_equal_vector(original, copy), "Vectors should not be equal after modification");
    _ASSERT_MSG(original->size == 3, "Original size should remain 3");
    _ASSERT_MSG(copy->size == 4, "Copy size should be 4");

    // Тестируем copy_vector_new
    Vector* new_copy = copy_vector_new(original);
    _ASSERT_MSG(new_copy != NULL, "New copy should not be NULL");
    _ASSERT_MSG(is_equal_vector(original, new_copy), "New copy should be equal to original");
    _ASSERT_MSG(new_copy->size == original->size, "New copy size should match original");

    delete_vector(&original);
    delete_vector(&copy);
    delete_vector(&new_copy);
}

void test_edge_cases() {
    printf("\n=== Test 5: Edge Cases ===\n");

    // Создание с capacity 0
    Vector* v = create_vector(0, CopyInt, CompareInt, DeleteInt);
    _ASSERT_MSG(v->data != NULL, "Vector with 0 capacity should still have data");
    _ASSERT_MSG(v->size == 0, "Size should be 0");

    // Добавление в пустой вектор
    push_back_vector(v, 42);
    _ASSERT_MSG(v->size == 1, "Size should be 1 after push to empty vector");
    _ASSERT_MSG(get_at_vector(v, 0) == 42, "Element should be 42");

    // Удаление из вектора с одним элементом
    delete_at_vector(v, 0);
    _ASSERT_MSG(v->size == 0, "Size should be 0 after deleting only element");

    delete_vector(&v);
}

int main() {
    printf("Starting simple vector tests...\n");

    test_create_and_destroy();
    test_push_back();
    test_delete_at();
    test_copy_operations();
    test_edge_cases();

    printf("\n✅ All vector tests passed!\n");
    return 0;
}
