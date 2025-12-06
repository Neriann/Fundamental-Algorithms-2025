#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H


typedef struct Node {
    int key; // вес элемента
    struct Node* parent; // указатель на родителя узла
    struct Node* child; // указатель на левого ребенка узла
    struct Node* sibling; // указатель на правого брата узла
    int degree; // количество дочерних узлов данного элемента
} Node;

typedef struct {
    Node* head;
    Node* target;
    int size;
} BinomialHeap;

BinomialHeap* create_binomial_heap();

BinomialHeap* copy_binomial_heap(const BinomialHeap* other);

void copy_assignment_binomial_heap(BinomialHeap** src, const BinomialHeap* dest);

void destroy_binomial_heap(BinomialHeap** heap);

void insert_binomial_heap(BinomialHeap** heap, int key);

int get_binomial_heap(const BinomialHeap* heap);

void extract_binomial_heap(BinomialHeap** heap);

BinomialHeap* merge_binomial_heap(const BinomialHeap* heap1, const BinomialHeap* heap2);

void meld_binomial_heap(BinomialHeap** heap1, BinomialHeap** heap2);

// void increase_binomial_heap(BinomialHeap* heap, int key);

// void decrease_binomial_heap(BinomialHeap* heap, int key);



#endif //BINOMIAL_HEAP_H
