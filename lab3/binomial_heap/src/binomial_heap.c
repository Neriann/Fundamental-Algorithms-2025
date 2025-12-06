#include "binomial_heap.h"

#include <stdlib.h>


int compare(int a, int b) {
    return a < b;
}

BinomialHeap* create_binomial_heap() {
    return (BinomialHeap*)calloc(1, sizeof(BinomialHeap));
}


Node* copy_tree_nodes(const Node* other, Node* parent) {
    if (!other)
        return NULL;

    Node* node = (Node*)malloc(sizeof(Node));
    node->key = other->key;
    node->degree = other->degree;
    node->parent = parent;

    node->child = copy_tree_nodes(other->child, node);
    node->sibling = copy_tree_nodes(other->sibling, node);
    return node;
}

void delete_tree_nodes(Node* node) {
    if (!node)
        return;

    delete_tree_nodes(node->child);
    delete_tree_nodes(node->sibling);

    node->parent = node->sibling = node->child = NULL;
    free(node);
}


Node* find_target_sibling(Node* node) {
    if (!node)
        return NULL;

    Node* target = node;
    node = node->sibling;
    while (node) {
        if (!compare(target->key, node->key)) {
            target = node;
        }
        node = node->sibling;
    }
    return target;
}

BinomialHeap* copy_binomial_heap(const BinomialHeap* other) {
    if (!other)
        return NULL;

    BinomialHeap* heap = create_binomial_heap();
    heap->head = copy_tree_nodes(other->head, NULL);

    heap->target = find_target_sibling(heap->head);
    heap->size = other->size;

    return heap;
}


void copy_assignment_binomial_heap(BinomialHeap** src, const BinomialHeap* dest) {
    if (!src || !dest)
        return;

    // Проверяем на присваивание на себя
    if ((*src)->head == dest->head)
        return;

    // Удаляем старую кучу
    destroy_binomial_heap(src);

    // Создаем новую кучу
    *src = copy_binomial_heap(dest);
}

void destroy_binomial_heap(BinomialHeap** heap) {
    if (!heap || !*heap)
        return;

    delete_tree_nodes((*heap)->head);
    free(*heap);
    *heap = NULL;
}

void insert_binomial_heap(BinomialHeap** heap, int key) {
    if (!heap)
        return;

    // Создаем кучу из одного элемента
    BinomialHeap* one_elem_heap = create_binomial_heap();
    one_elem_heap->head = (Node*)calloc(1, sizeof(Node));
    one_elem_heap->target = one_elem_heap->head;
    one_elem_heap->head->key = key;
    one_elem_heap->size = 1;

    // Делаем слияние
    meld_binomial_heap(heap, &one_elem_heap);
}

int get_binomial_heap(const BinomialHeap* heap) {
    if (!heap)
        return 0;

    return heap->target->key;
}

void extract_binomial_heap(BinomialHeap** heap) {
    if (!heap || !*heap || !(*heap)->head) return;


    Node* target = (*heap)->target;
    if (!target) return;

    BinomialHeap* heap_part = create_binomial_heap();
    // Берем только детей текущей target вершины
    heap_part->head = target->child;
    // Размер поддерева равен 2^k - 1
    heap_part->size = (1 << target->degree) - 1;

    // Размер текущей оставшейся кучи
    (*heap)->size -= heap_part->size;

    // Исключаем удаленный элемент
    --(*heap)->size;

    if ((*heap)->head == target) {
        // Меняем голову кучи
        (*heap)->head = (*heap)->head->sibling;
    } else {
        Node* curr = (*heap)->head;
        while (curr && curr->sibling != target) {
            curr = curr->sibling;
        }
        // Убираем из списка дерево с корнем target
        if (curr) curr->sibling = curr->sibling->sibling;
    }

    // Затираем все связи target
    target->child = target->parent = target->sibling = NULL;
    target->degree = 0;

    // Освобождаем память из под удаленной вершины
    free(target);

    // Объединяем две полученные кучи, исключая target
    meld_binomial_heap(heap, &heap_part);

    (*heap)->target = find_target_sibling((*heap)->head);
}


BinomialHeap* merge_roots_lists_sorted(const BinomialHeap* heap1, const BinomialHeap* heap2) {
    if (!heap1 || !heap1->head) return copy_binomial_heap(heap2);
    if (!heap2 || !heap2->head) return copy_binomial_heap(heap1);

    // Создаем копии куч
    BinomialHeap* copy_heap1 = copy_binomial_heap(heap1);
    BinomialHeap* copy_heap2 = copy_binomial_heap(heap2);

    BinomialHeap* sorted_heap = create_binomial_heap();
    sorted_heap->size = copy_heap1->size + copy_heap2->size;

    Node* curr_heap1 = copy_heap1->head;
    Node* curr_heap2 = copy_heap2->head;

    // Сначала привязываем голову к новой куче
    // Располагаем деревья в порядке не уменьшения порядка
    if (curr_heap1->degree < curr_heap2->degree) {
        sorted_heap->head = curr_heap1;
        curr_heap1 = curr_heap1->sibling;
    }
    else {
        sorted_heap->head = curr_heap2;
        curr_heap2 = curr_heap2->sibling;
    }

    Node* curr = sorted_heap->head;

    // Сливаем списки по степени
    while (curr_heap1 && curr_heap2) {
        if (curr_heap1->degree <= curr_heap2->degree) {
            curr->sibling = curr_heap1;
            curr_heap1 = curr_heap1->sibling;
        } else {
            curr->sibling = curr_heap2;
            curr_heap2 = curr_heap2->sibling;
        }
        curr = curr->sibling;
    }

    // Присоединяем остаток
    curr->sibling = curr_heap1 ? curr_heap1 : curr_heap2;

    copy_heap1->head = copy_heap2->head = NULL;

    // Очищаем память под объекты копий кучи
    destroy_binomial_heap(&copy_heap1);
    destroy_binomial_heap(&copy_heap2);

    sorted_heap->target = find_target_sibling(sorted_heap->head);
    return sorted_heap;
}

BinomialHeap* merge_binomial_heap(const BinomialHeap* heap1, const BinomialHeap* heap2) {
    // Если одна из куч пустая возвращаем копию другой
    if (!heap1 || !heap1->head) {
        return copy_binomial_heap(heap2);
    }
    if (!heap2 || !heap2->head) {
        return copy_binomial_heap(heap1);
    }

    BinomialHeap* merged_roots = merge_roots_lists_sorted(heap1, heap2);

    Node* prev = NULL;
    Node* curr = merged_roots->head;
    Node* next = curr->sibling;

    while (next) {
        // Если степени разные, просто двигаемся дальше или степени одинаковые, но есть ещё один такой же дальше
        if (curr->degree != next->degree || next->sibling && next->sibling->degree == curr->degree) {
            prev = curr;
            curr = next;
        }
        // Иначе нужно объединить curr и next
        else {
            Node* parent;
            Node* child;

            // Определяем, кто будет родителем (с более приоритетным ключом)
            if (compare(curr->key, next->key)) {
                parent = curr;
                child = next;
                // Обновляем связь в списке
                curr->sibling = next->sibling;
            } else {
                parent = next;
                child = curr;
                // Обновляем связь в списке
                if (prev) {
                    prev->sibling = parent;
                } else {
                    merged_roots->head = parent; // меняем начало списка
                }
                // parent->sibling = child;
            }

            // Делаем child ребёнком parent
            child->sibling = parent->child;
            parent->child = child;
            child->parent = parent;
            parent->degree++;

            // Остаёмся на parent для проверки следующего
            curr = parent;
        }
        next = curr->sibling;
    }
    merged_roots->target = find_target_sibling(merged_roots->head);
    return merged_roots;
}

void meld_binomial_heap(BinomialHeap** heap1, BinomialHeap** heap2) {
    if (!heap1 || !heap2 || !*heap2)
        return;

    // Если голова пустая второй кучи пустая, то все равно нужно очистить память из под объекта
    if (!(*heap2)->head) {
        destroy_binomial_heap(heap2);
        return;
    }
    BinomialHeap* old = *heap1;

    // Создаём полностью новую кучу из копий
    *heap1 = merge_binomial_heap(*heap1, *heap2);

    // Освобождаем старую кучу heap1
    destroy_binomial_heap(&old);
    // heap2 теперь не нужен — его копия уже в *heap1
    destroy_binomial_heap(heap2);
}

// void increase_binomial_heap(BinomialHeap* heap, int key) {}

// void decrease_binomial_heap(BinomialHeap* heap, int key) {}
