#ifndef BST_H
#define BST_H

#include <stddef.h>

typedef struct BSTNode {
    int key;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

typedef struct {
    BSTNode* root;
    size_t size;
} BST;

// Создание пустого дерева
BST* create_bst();

// Уничтожение дерева и освобождение памяти
void destroy_bst(BST** tree);

// Копирование дерева (глубокая копия)
BST* copy_bst(const BST* tree);

// Вставка ключа в дерево (дубликаты игнорируются)
void insert_bst(BST* tree, int key);

// Поиск ключа в дереве (1 — найден, 0 — не найден)
int search_bst(const BST* tree, int key);

// Удаление ключа из дерева
void delete_bst(BST* tree, int key);

// Получение минимального ключа
int min_bst(const BST* tree);

// Получение максимального ключа
int max_bst(const BST* tree);

// Обходы дерева: callback вызывается для каждого узла
void inorder_bst(const BST* tree, void (*callback)(int key));
void preorder_bst(const BST* tree, void (*callback)(int key));
void postorder_bst(const BST* tree, void (*callback)(int key));

// Высота дерева (пустое дерево имеет высоту 0)
int height_bst(const BST* tree);

// Проверка, является ли дерево корректным BST
int is_valid_bst(const BST* tree);

#endif // BST_H
