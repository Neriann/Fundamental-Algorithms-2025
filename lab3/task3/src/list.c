#include <stdlib.h>
#include <math.h>

#define IMPLEMENT_LIST(NAME, LIST_TYPE) \
/* Функция хелпер для поиска ноды */ \
Node##NAME* get_node_at_list_##NAME(const LinkedList##NAME* list, size_t index); \
 \
 \
/* Создание пустого списка */ \
LinkedList##NAME* create_list_##NAME(CopyFunc copy, CompareFunc compare, DestroyFunc destroy, CopyFieldFunc copy_field, CompareFieldFunc compare_field) { \
    LinkedList##NAME* list = (LinkedList##NAME*)malloc(sizeof(LinkedList##NAME)); \
    list->head = list->tail = NULL; \
    list->ops.copy = copy; \
    list->ops.copy_field = copy_field; \
    list->ops.compare = compare; \
    list->ops.compare_field = compare_field; \
    list->ops.destroy = destroy; \
    list->size = 0; \
    return list; \
} \
 \
/* Очистка содержимого списка (удаление всех элементов) */ \
void erase_list_##NAME(LinkedList##NAME* list) { \
    if (list && list->head) { \
        Node##NAME* curr = list->head; \
        for (size_t i = 0; i < list->size; ++i) { \
            Node##NAME* tmp = curr; \
            curr = curr->next; \
 \
            list->ops.destroy(tmp->data); \
            free(tmp); \
        } \
        list->size = 0; \
        list->head = list->tail = NULL; \
    } \
} \
 \
/* Полное удаление списка (освобождение ресурсов) */ \
void delete_list_##NAME(LinkedList##NAME** list) { \
    erase_list_##NAME(*list); \
    free(*list); \
    *list = NULL; \
} \
 \
 \
/* Добавление элемента в конец списка */ \
void push_back_list_##NAME(LinkedList##NAME* list, LIST_TYPE value) { \
    if (!list) { \
        return; \
    } \
    Node##NAME* node = (Node##NAME*)malloc(sizeof(Node##NAME)); \
    if (!node) { \
        return; \
    } \
    node->data = list->ops.copy(&value); \
    if (!list->tail) { \
        node->prev = node->next = NULL; \
        list->head = list->tail = node; \
    } \
    else { \
        node->prev = list->tail; \
        list->tail->next = node; \
 \
        node->next = list->head; \
        list->head->prev = node; \
 \
        list->tail = node; \
    } \
    ++list->size; \
} \
 \
/* Добавление элемента в начало списка */ \
void push_front_list_##NAME(LinkedList##NAME* list, LIST_TYPE value) { \
    if (!list) { \
        return; \
    } \
    Node##NAME* node = (Node##NAME*)malloc(sizeof(Node##NAME)); \
    if (!node) { \
        return; \
    } \
    node->data = list->ops.copy(&value); \
    if (!list->head || !list->size) { \
        node->prev = node->next = NULL; \
        list->head = list->tail = node; \
    } \
    else { \
        node->prev = list->tail; \
        list->tail->next = node; \
 \
        node->next = list->head; \
        list->head->prev = node; \
 \
        list->head = node; \
    } \
    ++list->size; \
} \
 \
/* Удаление элемента с конца списка */ \
LIST_TYPE* pop_back_list_##NAME(LinkedList##NAME* list) { \
    if (!list) { \
        return NULL; \
    } \
    if (!list->tail || !list->size) { \
        return NULL; \
    } \
    Node##NAME* tmp = list->tail; \
    /* выносим случай когда остается один элемент и head совпадает с tail */ \
    if (list->head == list->tail) { \
        list->tail = list->head = NULL; \
    } \
    else { \
        list->tail = list->tail->prev; \
        list->tail->next = list->head; \
        list->head->prev = list->tail; \
    } \
 \
    LIST_TYPE* copy = list->ops.copy(tmp->data); \
    list->ops.destroy(tmp->data); \
    free(tmp); \
 \
    --list->size; \
    return copy; \
} \
 \
/* Удаление элемента с начала списка */ \
LIST_TYPE* pop_front_list_##NAME(LinkedList##NAME* list) { \
    if (!list) { \
        return NULL; \
    } \
    if (!list->head) { \
        return NULL; \
    } \
    Node##NAME* tmp = list->head; \
    /* выносим случай когда остается один элемент и head совпадает с tail */ \
    if (list->head == list->tail) { \
        list->tail = list->head = NULL; \
    } \
    else { \
        list->head = list->head->next; \
        list->tail->next = list->head; \
        list->head->prev = list->tail; \
    } \
    LIST_TYPE* copy = list->ops.copy(tmp->data); \
    list->ops.destroy(tmp->data); \
    free(tmp); \
 \
    --list->size; \
    return copy; \
} \
 \
/* Заменить поле у элемента по индексу */ \
LIST_TYPE* replace_field_list_##NAME(LinkedList##NAME* list, size_t index, LIST_TYPE value, size_t field) {\
    Node##NAME* target = get_node_at_list_##NAME(list, index);\
    if (!target) {\
        return NULL;\
    }\
    list->ops.copy_field(target->data, &value, field);\
    return list->ops.copy(target->data);\
}\
\
/* Поиск элемента */\
int find_list_##NAME(LinkedList##NAME* list, LIST_TYPE value, size_t field) {\
    if (!list) {\
        return -2;\
    }\
    if (!list->head || !list->size) {\
        return -3;\
    }\
    Node##NAME* curr = list->head;\
    for (int i = 0; i < list->size; ++i) {\
        if (list->ops.compare_field && list->ops.compare_field(curr->data, &value, field) == 0) { \
            return i; \
        } \
        curr = curr->next;\
    }\
    return -4;\
}\
\
\
/* Вставка элемента по индексу */\
void insert_at_list_##NAME(LinkedList##NAME* list, size_t index, LIST_TYPE value) {\
    if (!list) {\
        return;\
    }\
    if (index > list->size) {\
        return;\
    }\
    Node##NAME* new_node = (Node##NAME*)malloc(sizeof(Node##NAME));\
    if (!new_node) {\
        return;\
    }\
    new_node->data = list->ops.copy(&value);\
    if (!list->head || !list->tail) {\
        new_node->prev = new_node->next = NULL;\
        list->head = list->tail = new_node;\
        ++list->size;\
        return;\
    }\
    Node##NAME* head = !index ? new_node : NULL;\
    Node##NAME* tail = index == list->size ? new_node : NULL;\
\
\
    if (list->head == list->tail && list->size == 1) {\
        if (head)\
            list->head = new_node;\
        if (tail)\
            list->tail = new_node;\
\
        list->head->prev = list->head->next = list->tail;\
\
        list->tail->prev = list->tail->next = list->head;\
\
        ++list->size;\
        return;\
    }\
    /* Ищем позицию перед нужным местом для вставки */\
    Node##NAME* curr_node = list->tail;\
    while (index--) {\
        curr_node = curr_node->next;\
    }\
\
    new_node->next = curr_node->next;\
    curr_node->next->prev = new_node;\
\
    curr_node->next = new_node;\
    new_node->prev = curr_node;\
\
    if (head)\
        list->head = new_node;\
    if (tail)\
        list->tail = new_node;\
\
    ++list->size;\
}\
\
/* Вставка элемента с сохранением порядка (поле birthday - по возрастанию) */\
void ordered_insert_at_list_##NAME(LinkedList##NAME* l, LIST_TYPE obj, size_t field) {\
    if (!l) {\
        return;\
    }\
    Node##NAME* curr = l->head;\
\
    size_t pos = l->size;\
    for (int i = 0; i < l->size; ++i) {\
        /* Eсли лексикографически больше, то значит obj надо записать перед текущим, т.к. он младше */ \
        if (l->ops.compare_field(&obj, curr->data, field) > 0) {\
            pos = i;\
            break;\
        }\
        curr = curr->next;\
    }\
    insert_at_list_##NAME(l, pos, obj);\
}\
\
/* Удаление элемента по индексу */\
void delete_at_list_##NAME(LinkedList##NAME* list, size_t index) {\
    if (!list || index >= list->size) {\
        return;\
    }\
    Node##NAME* target_node;\
    if (list->size == 1) {\
        target_node = list->head;\
        list->tail = list->head = NULL;\
    }\
    else {\
        /* ищем ноду, которую нужно удалить */\
        target_node = get_node_at_list_##NAME(list, index);\
        if (!target_node) return; \
        \
        if (target_node == list->head) { \
            list->head = target_node->next; \
        } \
        if (target_node == list->tail) { \
            list->tail = target_node->prev; \
        } \
\
        target_node->prev->next = target_node->next;\
        target_node->next->prev = target_node->prev;\
    }\
    list->ops.destroy(target_node->data);\
    free(target_node);\
\
    --list->size;\
}\
\
/* Получение элемента по индексу */\
LIST_TYPE* get_at_list_##NAME(const LinkedList##NAME* list, size_t index) {\
    if (!list) {\
        return NULL;\
    }\
    if (index >= list->size) {\
        return NULL;\
    }\
    Node##NAME* target_node = get_node_at_list_##NAME(list, index);\
\
    return list->ops.copy(target_node->data);\
}\
\
/* Функция хелпер для поиска ноды */\
Node##NAME* get_node_at_list_##NAME(const LinkedList##NAME* list, size_t index) {\
    Node##NAME* curr = list->head;\
    while (index--) {\
        if (curr)\
            curr = curr->next;\
    }\
    return curr;\
}\
\
\
/* Сравнение двух списков (лексикографически) возвращает 1 — равны, 0 — не равны */\
int is_equal_list_##NAME(const LinkedList##NAME* l1, const LinkedList##NAME* l2) {\
    if (!l1 || !l2) {\
        return 0;\
    }\
    if (l1->ops.compare != l2->ops.compare) return 0; \
    if (l1->size != l2->size) {\
        return 0;\
    }\
    Node##NAME *lhs = l1->head, *rhs = l2->head;\
    for (size_t i = 0; i < l1->size; ++i) {\
        if (!l1->ops.compare(lhs->data, rhs->data)) {\
            return 0;\
        }\
        lhs = lhs->next;\
        rhs = rhs->next;\
    }\
    return 1;\
}\
\
/* Поместить элемент на вершину стека */\
void push_stack_##NAME(LinkedList##NAME* stack, LIST_TYPE value) {\
    if (!stack) {\
        return;\
    }\
    push_front_list_##NAME(stack, value);\
}\
\
/* Извлечь элемент с вершины стека */\
LIST_TYPE* pop_stack_##NAME(LinkedList##NAME* stack) {\
    if (!stack) {\
        return NULL;\
    }\
    return pop_front_list_##NAME(stack);\
}\
\
/* Получить элемент с вершины стека без удаления */\
LIST_TYPE* peek_stack_##NAME(const LinkedList##NAME* stack) {\
    if (!stack) {\
        return NULL;\
    }\
    /* пустой стек */\
    if (!stack->head)\
        return NULL;\
    return stack->head->data;\
}\
\
/* Добавить элемент в очередь */\
void enqueue_##NAME(LinkedList##NAME* queue, LIST_TYPE value) {\
    if (!queue) {\
        return;\
    }\
    push_back_list_##NAME(queue, value);\
}\
\
/* Извлечь элемент из очереди */\
LIST_TYPE* dequeue_##NAME(LinkedList##NAME* queue) {\
    if (!queue) {\
        return NULL;\
    }\
    return pop_front_list_##NAME(queue);\
}\
\
/* Получить первый элемент очереди без удаления */\
LIST_TYPE* peek_queue_##NAME(const LinkedList##NAME* queue) {\
    if (!queue) {\
        return NULL;\
    }\
    /* пустая очередь */\
    if (!queue->tail)\
        return NULL;\
    return queue->head->data;\
}
