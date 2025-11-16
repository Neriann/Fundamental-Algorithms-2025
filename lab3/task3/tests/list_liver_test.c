#include <stdio.h>
#include <string.h>

#include "assert_base.h"

#include "list.h"
#include "../src/list.i"

#include "liver.h"

DECLARE_LIST(Liver, Liver)
IMPLEMENT_LIST(Liver, Liver)


// Тестовые данные
Liver create_test_liver(uint32_t id, const char* name, const char* surname, 
                       const char* patronymic, const char* birthday,
                       char gender, double salary) {
    Liver liver = {0};
    liver.id = id;
    strncpy(liver.name, name, NAME_SIZE - 1);
    strncpy(liver.surname, surname, NAME_SIZE - 1);
    strncpy(liver.patronymic, patronymic, NAME_SIZE - 1);
    strncpy(liver.birthday, birthday, BIRTHDAY_SIZE - 1);
    liver.gender = gender;
    liver.average_salary = salary;
    return liver;
}

void test_create_and_delete_list() {
    printf("=== Test create and delete list ===\n");
    
    LinkedListLiver* list = create_list_Liver(copy_liver, compare_liver, destroy_liver, copy_liver_field, compare_liver_one_field);
    _ASSERT_MSG(list != NULL, "List creation failed");
    _ASSERT_MSG(list->head == NULL, "New list head should be NULL");
    _ASSERT_MSG(list->tail == NULL, "New list tail should be NULL");
    _ASSERT_MSG(list->size == 0, "New list size should be 0, got %zu", list->size);
    
    delete_list_Liver(&list);
    printf("Test passed: create_and_delete_list_Liver\n\n");
}

void test_push_back_and_pop_back() {
    printf("=== Test push_back and pop_back ===\n");
    
    LinkedListLiver* list = create_list_Liver(copy_liver, compare_liver, destroy_liver, copy_liver_field, compare_liver_one_field);
    
    Liver liver1 = create_test_liver(1, "Ivan", "Ivanov", "Ivanovich", "1990-01-01", 'M', 50000.0);
    Liver liver2 = create_test_liver(2, "Maria", "Petrova", "Sergeevna", "1992-02-02", 'F', 60000.0);
    
    // Test push_back
    push_back_list_Liver(list, liver1);
    _ASSERT_MSG(list->size == 1, "Size should be 1 after first push_back, got %zu", list->size);
    _ASSERT_MSG(list->head != NULL, "Head should not be NULL");
    _ASSERT_MSG(list->tail != NULL, "Tail should not be NULL");
    _ASSERT_MSG(list->head == list->tail, "Head and tail should be same for single element");
    
    push_back_list_Liver(list, liver2);
    _ASSERT_MSG(list->size == 2, "Size should be 2 after second push_back, got %zu", list->size);
    _ASSERT_MSG(list->head != list->tail, "Head and tail should be different for two elements");
    
    // Test pop_back
    Liver* popped = pop_back_list_Liver(list);
    _ASSERT_MSG(popped != NULL, "Pop back should return non-NULL");
    _ASSERT_MSG(popped->id == 2, "Popped element should have id 2, got %u", popped->id);
    _ASSERT_MSG(list->size == 1, "Size should be 1 after pop_back, got %zu", list->size);
    
    popped = pop_back_list_Liver(list);
    _ASSERT_MSG(popped->id == 1, "Popped element should have id 1, got %u", popped->id);
    _ASSERT_MSG(list->size == 0, "Size should be 0 after second pop_back, got %zu", list->size);
    _ASSERT_MSG(list->head == NULL, "Head should be NULL after emptying list");
    _ASSERT_MSG(list->tail == NULL, "Tail should be NULL after emptying list");
    
    // Test pop_back on empty list
    popped = pop_back_list_Liver(list);
    _ASSERT_MSG(popped == NULL, "Pop back on empty list should return NULL");
    
    delete_list_Liver(&list);
    printf("Test passed: push_back_and_pop_back\n\n");
}

void test_push_front_and_pop_front() {
    printf("=== Test push_front and pop_front ===\n");
    
    LinkedListLiver* list = create_list_Liver(copy_liver, compare_liver, destroy_liver, copy_liver_field, compare_liver_one_field);;
    
    Liver liver1 = create_test_liver(1, "Ivan", "Ivanov", "Ivanovich", "1990-01-01", 'M', 50000.0);
    Liver liver2 = create_test_liver(2, "Maria", "Petrova", "Sergeevna", "1992-02-02", 'F', 60000.0);
    
    // Test push_front
    push_front_list_Liver(list, liver1);
    _ASSERT_MSG(list->size == 1, "Size should be 1 after first push_front, got %zu", list->size);
    
    push_front_list_Liver(list, liver2);
    _ASSERT_MSG(list->size == 2, "Size should be 2 after second push_front, got %zu", list->size);
    _ASSERT_MSG(list->head->data->id == 2, "Head should have id 2, got %u", list->head->data->id);
    
    // Test pop_front
    Liver* popped = pop_front_list_Liver(list);
    _ASSERT_MSG(popped != NULL, "Pop front should return non-NULL");
    _ASSERT_MSG(popped->id == 2, "Popped element should have id 2, got %u", popped->id);
    _ASSERT_MSG(list->size == 1, "Size should be 1 after pop_front, got %zu", list->size);
    
    popped = pop_front_list_Liver(list);
    _ASSERT_MSG(popped->id == 1, "Popped element should have id 1, got %u", popped->id);
    _ASSERT_MSG(list->size == 0, "Size should be 0 after second pop_front, got %zu", list->size);
    
    // Test pop_front on empty list
    popped = pop_front_list_Liver(list);
    _ASSERT_MSG(popped == NULL, "Pop front on empty list should return NULL");
    
    delete_list_Liver(&list);
    printf("Test passed: push_front_and_pop_front\n\n");
}

void test_insert_and_delete_at() {
    printf("=== Test insert_at and delete_at ===\n");
    
    LinkedListLiver* list = create_list_Liver(copy_liver, compare_liver, destroy_liver, copy_liver_field, compare_liver_one_field);;
    
    Liver liver1 = create_test_liver(1, "Ivan", "Ivanov", "Ivanovich", "1990-01-01", 'M', 50000.0);
    Liver liver2 = create_test_liver(2, "Maria", "Petrova", "Sergeevna", "1992-02-02", 'F', 60000.0);
    Liver liver3 = create_test_liver(3, "Petr", "Sidorov", "Petrovich", "1988-03-03", 'M', 70000.0);
    
    push_back_list_Liver(list, liver1);
    push_back_list_Liver(list, liver3);
    
    // Insert at middle
    insert_at_list_Liver(list, 1, liver2);
    _ASSERT_MSG(list->size == 3, "Size should be 3 after insert, got %zu", list->size);
    
    Liver* middle = get_at_list_Liver(list, 1);
    _ASSERT_MSG(middle != NULL, "Get at index 1 should not return NULL");
    _ASSERT_MSG(middle->id == 2, "Element at index 1 should have id 2, got %u", middle->id);
    
    // Insert at beginning
    Liver liver0 = create_test_liver(0, "Anna", "Smirnova", "Alexeevna", "1995-04-04", 'F', 55000.0);
    insert_at_list_Liver(list, 0, liver0);
    _ASSERT_MSG(list->head->data->id == 0, "Head should have id 0 after insert at 0, got %u", list->head->data->id);
    
    // Insert at end
    Liver liver4 = create_test_liver(4, "Sergey", "Kuznetsov", "Viktorovich", "1993-05-05", 'M', 65000.0);
    insert_at_list_Liver(list, 4, liver4);
    _ASSERT_MSG(list->tail->data->id == 4, "Tail should have id 4 after insert at end, got %u", list->tail->data->id);
    
    // Test delete_at
    delete_at_list_Liver(list, 1); // Delete element with id 1
    _ASSERT_MSG(list->size == 4, "Size should be 4 after delete, got %zu", list->size);
    _ASSERT_MSG(get_at_list_Liver(list, 1)->id == 2, "Element at index 1 should now have id 2, got %u", get_at_list_Liver(list, 1)->id);

    delete_at_list_Liver(list, 0);
    _ASSERT_MSG(list->size == 3, "Size should be 3 after delete, got %zu", list->size);
    _ASSERT_MSG(get_at_list_Liver(list, 0)->id == 2, "Element at index 1 should now have id 2, got %u", get_at_list_Liver(list, 1)->id);
    _ASSERT_MSG(strcmp(get_at_list_Liver(list, 0)->name, "Maria") == 0, "");


    delete_list_Liver(&list);
    printf("Test passed: insert_and_delete_at\n\n");
}

void test_get_at() {
    printf("=== Test get_at ===\n");
    
    LinkedListLiver* list = create_list_Liver(copy_liver, compare_liver, destroy_liver, copy_liver_field, compare_liver_one_field);;
    
    Liver liver1 = create_test_liver(1, "Ivan", "Ivanov", "Ivanovich", "1990-01-01", 'M', 50000.0);
    Liver liver2 = create_test_liver(2, "Maria", "Petrova", "Sergeevna", "1992-02-02", 'F', 60000.0);
    Liver liver3 = create_test_liver(3, "Petr", "Sidorov", "Petrovich", "1988-03-03", 'M', 70000.0);
    
    push_back_list_Liver(list, liver1);
    push_back_list_Liver(list, liver2);
    push_back_list_Liver(list, liver3);
    
    // Test valid indices
    Liver* first = get_at_list_Liver(list, 0);
    _ASSERT_MSG(first != NULL, "Get at index 0 should not return NULL");
    _ASSERT_MSG(first->id == 1, "Element at index 0 should have id 1, got %u", first->id);
    
    Liver* second = get_at_list_Liver(list, 1);
    _ASSERT_MSG(second->id == 2, "Element at index 1 should have id 2, got %u", second->id);
    
    Liver* third = get_at_list_Liver(list, 2);
    _ASSERT_MSG(third->id == 3, "Element at index 2 should have id 3, got %u", third->id);
    
    // Test invalid indices
    Liver* invalid = get_at_list_Liver(list, 5);
    _ASSERT_MSG(invalid == NULL, "Get at invalid index should return NULL");
    
    invalid = get_at_list_Liver(list, -1);
    _ASSERT_MSG(invalid == NULL, "Get at negative index should return NULL");
    
    delete_list_Liver(&list);
    printf("Test passed: get_at\n\n");
}

void test_is_equal_list() {
    printf("=== Test is_equal_list_Liver ===\n");
    
    LinkedListLiver* list1 = create_list_Liver(copy_liver, compare_liver, destroy_liver, copy_liver_field, compare_liver_one_field);;
    LinkedListLiver* list2 = create_list_Liver(copy_liver, compare_liver, destroy_liver, copy_liver_field, compare_liver_one_field);;
    LinkedListLiver* list3 = create_list_Liver(copy_liver, compare_liver, destroy_liver, copy_liver_field, compare_liver_one_field);;
    
    Liver liver1 = create_test_liver(1, "Ivan", "Ivanov", "Ivanovich", "1990-01-01", 'M', 50000.0);
    Liver liver2 = create_test_liver(2, "Maria", "Petrova", "Sergeevna", "1992-02-02", 'F', 60000.0);
    
    // Test empty lists
    int equal = is_equal_list_Liver(list1, list2);
    _ASSERT_MSG(equal == 1, "Two empty lists should be equal");
    
    // Test one empty, one non-empty
    push_back_list_Liver(list1, liver1);
    equal = is_equal_list_Liver(list1, list2);
    _ASSERT_MSG(equal == 0, "Empty and non-empty lists should not be equal");
    
    // Test same elements
    push_back_list_Liver(list2, liver1);
    equal = is_equal_list_Liver(list1, list2);
    _ASSERT_MSG(equal == 1, "Lists with same elements should be equal");
    
    // Test different elements
    push_back_list_Liver(list3, liver2);
    equal = is_equal_list_Liver(list1, list3);
    _ASSERT_MSG(equal == 0, "Lists with different elements should not be equal");
    
    delete_list_Liver(&list1);
    delete_list_Liver(&list2);
    delete_list_Liver(&list3);
    printf("Test passed: is_equal_list_Liver\n\n");
}

void test_stack_operations() {
    printf("=== Test stack operations ===\n");
    
    LinkedListLiver* stack = create_list_Liver(copy_liver, compare_liver, destroy_liver, copy_liver_field, compare_liver_one_field);;
    
    Liver liver1 = create_test_liver(1, "Ivan", "Ivanov", "Ivanovich", "1990-01-01", 'M', 50000.0);
    Liver liver2 = create_test_liver(2, "Maria", "Petrova", "Sergeevna", "1992-02-02", 'F', 60000.0);
    
    // Test push_stack_Liver
    push_stack_Liver(stack, liver1);
    _ASSERT_MSG(stack->size == 1, "Stack size should be 1 after push, got %zu", stack->size);
    
    push_stack_Liver(stack, liver2);
    _ASSERT_MSG(stack->size == 2, "Stack size should be 2 after second push, got %zu", stack->size);
    
    // Test peek_stack_Liver
    Liver* top = peek_stack_Liver(stack);
    _ASSERT_MSG(top != NULL, "Peek should not return NULL");
    _ASSERT_MSG(top->id == 2, "Top element should have id 2, got %u", top->id);
    _ASSERT_MSG(stack->size == 2, "Peek should not change size, got %zu", stack->size);
    
    // Test pop_stack_Liver
    Liver* popped = pop_stack_Liver(stack);
    _ASSERT_MSG(popped != NULL, "Pop should not return NULL");
    _ASSERT_MSG(popped->id == 2, "Popped element should have id 2, got %u", popped->id);
    _ASSERT_MSG(stack->size == 1, "Stack size should be 1 after pop, got %zu", stack->size);
    
    popped = pop_stack_Liver(stack);
    _ASSERT_MSG(popped->id == 1, "Popped element should have id 1, got %u", popped->id);
    _ASSERT_MSG(stack->size == 0, "Stack size should be 0 after second pop, got %zu", stack->size);
    
    // Test operations on empty stack
    top = peek_stack_Liver(stack);
    _ASSERT_MSG(top == NULL, "Peek on empty stack should return NULL");
    
    popped = pop_stack_Liver(stack);
    _ASSERT_MSG(popped == NULL, "Pop on empty stack should return NULL");
    
    delete_list_Liver(&stack);
    printf("Test passed: stack_operations\n\n");
}

void test_queue_operations() {
    printf("=== Test queue operations ===\n");
    
    LinkedListLiver* queue = create_list_Liver(copy_liver, compare_liver, destroy_liver, copy_liver_field, compare_liver_one_field);;
    
    Liver liver1 = create_test_liver(1, "Ivan", "Ivanov", "Ivanovich", "1990-01-01", 'M', 50000.0);
    Liver liver2 = create_test_liver(2, "Maria", "Petrova", "Sergeevna", "1992-02-02", 'F', 60000.0);
    Liver liver3 = create_test_liver(3, "Petr", "Sidorov", "Petrovich", "1988-03-03", 'M', 70000.0);
    
    // Test enqueue_Liver
    enqueue_Liver(queue, liver1);
    _ASSERT_MSG(queue->size == 1, "Queue size should be 1 after first enqueue_Liver, got %zu", queue->size);
    
    enqueue_Liver(queue, liver2);
    _ASSERT_MSG(queue->size == 2, "Queue size should be 2 after second enqueue_Liver, got %zu", queue->size);
    
    enqueue_Liver(queue, liver3);
    _ASSERT_MSG(queue->size == 3, "Queue size should be 3 after third enqueue_Liver, got %zu", queue->size);
    
    // Test peek_queue_Liver
    Liver* front = peek_queue_Liver(queue);
    _ASSERT_MSG(front != NULL, "Peek should not return NULL");
    _ASSERT_MSG(front->id == 1, "Front element should have id 1, got %u", front->id);
    
    // Test dequeue
    Liver* dequeued = dequeue_Liver(queue);
    _ASSERT_MSG(dequeued != NULL, "Dequeue should not return NULL");
    _ASSERT_MSG(dequeued->id == 1, "Dequeued element should have id 1, got %u", dequeued->id);
    _ASSERT_MSG(queue->size == 2, "Queue size should be 2 after dequeue, got %zu", queue->size);
    
    front = peek_queue_Liver(queue);
    _ASSERT_MSG(front->id == 2, "Front element should now have id 2, got %u", front->id);
    
    dequeued = dequeue_Liver(queue);
    _ASSERT_MSG(dequeued->id == 2, "Dequeued element should have id 2, got %u", dequeued->id);
    
    dequeued = dequeue_Liver(queue);
    _ASSERT_MSG(dequeued->id == 3, "Dequeued element should have id 3, got %u", dequeued->id);
    _ASSERT_MSG(queue->size == 0, "Queue size should be 0 after all dequeues, got %zu", queue->size);
    
    // Test operations on empty queue
    front = peek_queue_Liver(queue);
    _ASSERT_MSG(front == NULL, "Peek on empty queue should return NULL");
    
    dequeued = dequeue_Liver(queue);
    _ASSERT_MSG(dequeued == NULL, "Dequeue on empty queue should return NULL");
    
    delete_list_Liver(&queue);
    printf("Test passed: queue_operations\n\n");
}

void test_erase_list() {
    printf("=== Test erase_list_Liver ===\n");
    
    LinkedListLiver* list = create_list_Liver(copy_liver, compare_liver, destroy_liver, copy_liver_field, compare_liver_one_field);;
    
    Liver liver1 = create_test_liver(1, "Ivan", "Ivanov", "Ivanovich", "1990-01-01", 'M', 50000.0);
    Liver liver2 = create_test_liver(2, "Maria", "Petrova", "Sergeevna", "1992-02-02", 'F', 60000.0);
    
    push_back_list_Liver(list, liver1);
    push_back_list_Liver(list, liver2);
    
    _ASSERT_MSG(list->size == 2, "Size should be 2 before erase, got %zu", list->size);
    
    erase_list_Liver(list);
    _ASSERT_MSG(list->size == 0, "Size should be 0 after erase, got %zu", list->size);
    _ASSERT_MSG(list->head == NULL, "Head should be NULL after erase");
    _ASSERT_MSG(list->tail == NULL, "Tail should be NULL after erase");
    
    // Test that we can reuse the list after erase
    push_back_list_Liver(list, liver1);
    _ASSERT_MSG(list->size == 1, "Should be able to reuse list after erase, size: %zu", list->size);
    
    delete_list_Liver(&list);
    printf("Test passed: erase_list_Liver\n\n");
}

int main() {
    printf("Starting Linked List Tests...\n\n");
    
    test_create_and_delete_list();
    test_push_back_and_pop_back();
    test_push_front_and_pop_front();
    test_insert_and_delete_at();
    test_get_at();
    test_is_equal_list();
    test_stack_operations();
    test_queue_operations();
    test_erase_list();
    
    printf("All tests passed successfully!\n");
    return 0;
}
