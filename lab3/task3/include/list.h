#ifndef LIST_H
#define LIST_H

typedef void* (*CopyFunc)(const void*);
typedef int (*CompareFunc)(const void*, const void*);
typedef void (*DestroyFunc)(void*);

// Дополнительные функции для структур
typedef int (*CompareFieldFunc)(const void*, const void*, size_t);
typedef void (*CopyFieldFunc)(void*, const void*, size_t);

typedef struct {
 CopyFunc copy;
 CopyFieldFunc copy_field;
 CompareFunc compare;
 CompareFieldFunc compare_field;
 DestroyFunc destroy;
} TypeOps;


#define DECLARE_LIST(NAME, LIST_TYPE) \
/* Узел двусвязного списка */ \
typedef struct Node##NAME { \
    LIST_TYPE* data; \
    struct Node##NAME* prev; \
    struct Node##NAME* next; \
} Node##NAME; \
\
/*  Двусвязный список */ \
typedef struct { \
    Node##NAME* head; \
    Node##NAME* tail; \
    size_t size; \
    TypeOps ops; \
} LinkedList##NAME; \
 \
/*  Создание пустого списка */ \
LinkedList##NAME* create_list_##NAME(CopyFunc copy, CompareFunc compare, DestroyFunc destroy, \
CopyFieldFunc copy_field, CompareFieldFunc compare_field); \
 \
/*  Очистка содержимого списка (удаление всех элементов) */ \
void erase_list_##NAME(LinkedList##NAME* list); \
 \
/*  Полное удаление списка (освобождение ресурсов) */ \
void delete_list_##NAME(LinkedList##NAME** list); \
 \
/*  Добавление элемента в конец списка */ \
void push_back_list_##NAME(LinkedList##NAME* list, LIST_TYPE value); \
 \
/*  Добавление элемента в начало списка */ \
void push_front_list_##NAME(LinkedList##NAME* list, LIST_TYPE value); \
 \
/*  Удаление элемента с конца списка */ \
LIST_TYPE* pop_back_list_##NAME(LinkedList##NAME* list); \
 \
/*  Удаление элемента с начала списка */ \
LIST_TYPE* pop_front_list_##NAME(LinkedList##NAME* list); \
 \
/*  Заменить поле у элемента по индексу (возвращаем отредактированный элемент) */ \
LIST_TYPE* replace_field_list_##NAME(LinkedList##NAME* list, size_t index, LIST_TYPE value, size_t field); \
 \
/*  Поиск элемента */ \
int find_list_##NAME(LinkedList##NAME* list, LIST_TYPE value, size_t field); \
 \
/*  Вставка элемента с сохранением порядка (поле birthday - по возрастанию) */ \
void ordered_insert_at_list_##NAME(LinkedList##NAME* l, LIST_TYPE obj, size_t field); \
 \
/*  Вставка элемента по индексу */ \
void insert_at_list_##NAME(LinkedList##NAME* list, size_t index, LIST_TYPE value); \
 \
/*  Удаление элемента по индексу */ \
void delete_at_list_##NAME(LinkedList##NAME* list, size_t index); \
 \
/*  Получение элемента по индексу */ \
LIST_TYPE* get_at_list_##NAME(const LinkedList##NAME* list, size_t index); \
 \
/*  Сравнение двух списков (лексикографически) возвращает 1 — равны, 0 — не равны */ \
int is_equal_list_##NAME(const LinkedList##NAME* l1, const LinkedList##NAME* l2); \
 \
/*  Поместить элемент на вершину стека */ \
void push_stack_##NAME(LinkedList##NAME* stack, LIST_TYPE value); \
 \
/*  Извлечь элемент с вершины стека */ \
LIST_TYPE* pop_stack_##NAME(LinkedList##NAME* stack); \
 \
/*  Получить элемент с вершины стека без удаления */ \
LIST_TYPE* peek_stack_##NAME(const LinkedList##NAME* stack); \
 \
/*  Добавить элемент в очередь */ \
void enqueue_##NAME(LinkedList##NAME* queue, LIST_TYPE value); \
 \
/*  Извлечь элемент из очереди */ \
LIST_TYPE* dequeue_##NAME(LinkedList##NAME* queue); \
 \
/*  Получить первый элемент очереди без удаления */ \
LIST_TYPE* peek_queue_##NAME(const LinkedList##NAME* queue);

#endif // LIST_H
