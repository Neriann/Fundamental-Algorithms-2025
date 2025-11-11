#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "assert_base.h"

// Сложная структура для тестирования
typedef struct {
    char* name;
    int id;
    double value;
} ComplexData;

// Объявляем вектор для ComplexData
DECLARE_VECTOR(ComplexData)
IMPLEMENT_VECTOR(ComplexData)

// Функции копирования и удаления для ComplexData
ComplexData CopyComplexData(ComplexData data) {
    ComplexData copy;
    copy.name = malloc(strlen(data.name) + 1);
    strcpy(copy.name, data.name);
    copy.id = data.id;
    copy.value = data.value;
    return copy;
}

int CompareComplexData(ComplexData data1, ComplexData data2) {
    return !strcmp(data1.name, data2.name) && data1.id == data2.id && data1.value == data2.value;
}

void DeleteComplexData(ComplexData data) {
    free(data.name); // Освобождаем динамически выделенную память
}


void test_complex_create_destroy() {
    printf("\n=== Complex Test 1: Create and Destroy ===\n");
    Vector* v = create_vector(5, CopyComplexData, CompareComplexData, DeleteComplexData);

    _ASSERT_MSG(v != NULL, "Vector should not be NULL");
    _ASSERT_MSG(v->data != NULL, "Complex vector data should not be NULL");
    _ASSERT_MSG(v->size == 0, "Initial size should be 0");
    _ASSERT_MSG(v->capacity >= 5, "Capacity should be at least 5, got %zu", v->capacity);
    _ASSERT_MSG(v->CopyVoidPtr == CopyComplexData, "Copy function should be set correctly");
    _ASSERT_MSG(v->DeleteVoidPtr == DeleteComplexData, "Delete function should be set correctly");

    delete_vector(&v);
    _ASSERT_MSG(v == NULL, "After delete, vector pointer should be NULL");
}

void test_complex_push_back() {
    printf("\n=== Complex Test 2: Push Back ===\n");
    Vector* v = create_vector(2, CopyComplexData, CompareComplexData, DeleteComplexData);
    _ASSERT_MSG(v != NULL, "Vector creation should succeed");

    ComplexData data1 = {strdup("First"), 1, 10.5};
    ComplexData data2 = {strdup("Second"), 2, 20.7};
    ComplexData data3 = {strdup("Third"), 3, 30.9};

    push_back_vector(v, data1);
    push_back_vector(v, data2);
    push_back_vector(v, data3);

    _ASSERT_MSG(v->size == 3, "Size should be 3 after 3 pushes, got %zu", v->size);
    _ASSERT_MSG(v->capacity >= 3, "Capacity should be at least 3, got %zu", v->capacity);

    ComplexData retrieved1 = get_at_vector(v, 0);
    ComplexData retrieved2 = get_at_vector(v, 1);
    ComplexData retrieved3 = get_at_vector(v, 2);

    _ASSERT_MSG(strcmp(retrieved1.name, "First") == 0, "First element name should be 'First'");
    _ASSERT_MSG(retrieved1.id == 1, "First element id should be 1");
    _ASSERT_MSG(retrieved1.value == 10.5, "First element value should be 10.5");

    _ASSERT_MSG(strcmp(retrieved2.name, "Second") == 0, "Second element name should be 'Second'");
    _ASSERT_MSG(retrieved2.id == 2, "Second element id should be 2");
    _ASSERT_MSG(retrieved2.value == 20.7, "Second element value should be 20.7");

    _ASSERT_MSG(strcmp(retrieved3.name, "Third") == 0, "Third element name should be 'Third'");
    _ASSERT_MSG(retrieved3.id == 3, "Third element id should be 3");
    _ASSERT_MSG(retrieved3.value == 30.9, "Third element value should be 30.9");

    // Освобождаем оригинальные данные
    free(data1.name);
    free(data2.name);
    free(data3.name);

    delete_vector(&v);
    _ASSERT_MSG(v == NULL, "Vector should be NULL after deletion");
}

void test_complex_delete_at() {
    printf("\n=== Complex Test 3: Delete At ===\n");
    Vector* v = create_vector(5, CopyComplexData, CompareComplexData, DeleteComplexData);
    _ASSERT_MSG(v != NULL, "Vector creation should succeed");

    ComplexData data1 = {strdup("Alpha"), 100, 1.1};
    ComplexData data2 = {strdup("Beta"), 200, 2.2};
    ComplexData data3 = {strdup("Gamma"), 300, 3.3};

    push_back_vector(v, data1);
    push_back_vector(v, data2);
    push_back_vector(v, data3);

    // Удаляем средний элемент
    delete_at_vector(v, 1);
    _ASSERT_MSG(v->size == 2, "Size should be 2 after deletion, got %zu", v->size);
    _ASSERT_MSG(CompareComplexData(data1, v->data[0]), "First element name should be 'Alpha': '%s'", data1.name);
    _ASSERT_MSG(CompareComplexData(data3, v->data[1]), "Second element name should be 'Gamma': '%s'", data3.name);

    // Проверяем оставшиеся элементы
    ComplexData first = get_at_vector(v, 0);
    ComplexData second = get_at_vector(v, 1);

    _ASSERT_MSG(strcmp(first.name, "Alpha") == 0, "First element should be 'Alpha'");
    _ASSERT_MSG(strcmp(second.name, "Gamma") == 0, "Second element should be 'Gamma'");

    // Освобождаем память
    free(data1.name);
    free(data2.name);
    free(data3.name);

    delete_vector(&v);
    _ASSERT_MSG(v == NULL, "Vector should be NULL after deletion");
}

void test_complex_copy_operations() {
    printf("\n=== Complex Test 4: Copy Operations ===\n");
    Vector* original = create_vector(3, CopyComplexData, CompareComplexData, DeleteComplexData);
    _ASSERT_MSG(original != NULL, "Original vector creation should succeed");

    ComplexData data1 = {strdup("Original1"), 1, 1.0};
    ComplexData data2 = {strdup("Original2"), 2, 2.0};

    push_back_vector(original, data1);
    push_back_vector(original, data2);

    // Тестируем глубокое копирование
    Vector* copy = copy_vector_new(original);
    _ASSERT_MSG(copy != NULL, "Copy should not be NULL");
    _ASSERT_MSG(copy->size == original->size, "Copy size should match original, got %zu vs %zu", copy->size, original->size);

    // Проверяем, что данные действительно скопированы (разные указатели)
    ComplexData orig_first = get_at_vector(original, 0);
    ComplexData copy_first = get_at_vector(copy, 0);

    _ASSERT_MSG(orig_first.name != copy_first.name, "Names should be different pointers (deep copy)");
    _ASSERT_MSG(strcmp(orig_first.name, copy_first.name) == 0, "Name content should be identical");
    _ASSERT_MSG(orig_first.id == copy_first.id, "IDs should be equal");
    _ASSERT_MSG(orig_first.value == copy_first.value, "Values should be equal");

    // Изменяем копию и проверяем, что оригинал не изменился
    ComplexData new_data = {strdup("NewInCopy"), 99, 99.9};
    push_back_vector(copy, new_data);
    _ASSERT_MSG(original->size == 2, "Original size should remain 2 after modifying copy");
    _ASSERT_MSG(copy->size == 3, "Copy size should be 3 after addition");

    // Освобождаем память
    free(data1.name);
    free(data2.name);
    free(new_data.name);

    delete_vector(&original);
    delete_vector(&copy);
    _ASSERT_MSG(original == NULL, "Original should be NULL after deletion");
    _ASSERT_MSG(copy == NULL, "Copy should be NULL after deletion");
}

void test_complex_memory_management() {
    printf("\n=== Complex Test 5: Memory Management ===\n");

    Vector* v = create_vector(2, CopyComplexData, CompareComplexData, DeleteComplexData);
    _ASSERT_MSG(v != NULL, "Vector creation should succeed");

    // Создаем данные с динамической памятью
    ComplexData dynamic_data = {strdup("Dynamic"), 999, 99.9};
    push_back_vector(v, dynamic_data);

    // Проверяем, что данные корректно сохранились
    ComplexData retrieved = get_at_vector(v, 0);
    _ASSERT_MSG(strcmp(retrieved.name, "Dynamic") == 0, "Dynamic data should be preserved");
    _ASSERT_MSG(retrieved.name != dynamic_data.name, "Should be different memory locations");
    _ASSERT_MSG(retrieved.id == 999, "ID should be preserved");
    _ASSERT_MSG(retrieved.value == 99.9, "Value should be preserved");

    // Удаляем элемент и проверяем, что память освобождается корректно
    delete_at_vector(v, 0);
    _ASSERT_MSG(v->size == 0, "Size should be 0 after deletion, got %zu", v->size);

    // Освобождаем оригинальные данные и удаленный элемент
    free(dynamic_data.name);

    delete_vector(&v);
    _ASSERT_MSG(v == NULL, "Vector should be properly destroyed");
}

void test_complex_edge_cases() {
    printf("\n=== Complex Test 6: Edge Cases ===\n");

    // Создание с capacity 0
    Vector* v = create_vector(0, CopyComplexData, CompareComplexData, DeleteComplexData);
    _ASSERT_MSG(v != NULL, "Vector with 0 capacity should still be created");
    _ASSERT_MSG(v->capacity >= 1, "Capacity should be at least 1, got %zu", v->capacity);
    _ASSERT_MSG(v->size == 0, "Size should be 0");

    // Добавление в пустой вектор
    ComplexData data = {strdup("Single"), 42, 42.0};
    push_back_vector(v, data);
    _ASSERT_MSG(v->size == 1, "Size should be 1 after push to empty vector");

    ComplexData retrieved = get_at_vector(v, 0);
    _ASSERT_MSG(strcmp(retrieved.name, "Single") == 0, "Element should be correctly stored");

    // Удаление из вектора с одним элементом
    delete_at_vector(v, 0);
    _ASSERT_MSG(v->size == 0, "Size should be 0 after deleting only element");

    // Освобождаем память
    free(data.name);

    delete_vector(&v);
    _ASSERT_MSG(v == NULL, "Vector should be NULL after deletion");
}

int main() {
    printf("Starting complex vector tests...\n");

    test_complex_create_destroy();
    test_complex_push_back();
    test_complex_delete_at();
    test_complex_copy_operations();
    test_complex_memory_management();
    test_complex_edge_cases();

    printf("\n✅ All complex vector tests passed!\n");
    return 0;
}
