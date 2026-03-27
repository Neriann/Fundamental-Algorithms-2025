#include <stdlib.h>
#include <limits.h>

#include "bst.h"

// Используем long long для граничных значений, чтобы поддерживать
// вставку INT_MIN и INT_MAX как корректных ключей
typedef long long ll;

// ---------- вспомогательные функции ----------

static BSTNode* create_node(int key) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    if (!node) return NULL;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void destroy_node_recursive(BSTNode* node) {
    if (!node) return;
    destroy_node_recursive(node->left);
    destroy_node_recursive(node->right);
    free(node);
}

static BSTNode* copy_node_recursive(const BSTNode* node) {
    if (!node) return NULL;
    BSTNode* new_node = create_node(node->key);
    if (!new_node) return NULL;
    new_node->left = copy_node_recursive(node->left);
    new_node->right = copy_node_recursive(node->right);
    return new_node;
}

static BSTNode* insert_node(BSTNode* node, int key, int* inserted) {
    if (!node) {
        *inserted = 1;
        return create_node(key);
    }
    if (key < node->key) {
        node->left = insert_node(node->left, key, inserted);
    } else if (key > node->key) {
        node->right = insert_node(node->right, key, inserted);
    }
    // дубликаты игнорируются
    return node;
}

static int search_node(const BSTNode* node, int key) {
    if (!node) return 0;
    if (key == node->key) return 1;
    if (key < node->key) return search_node(node->left, key);
    return search_node(node->right, key);
}

static BSTNode* min_node(BSTNode* node) {
    if (!node) return NULL;
    while (node->left) node = node->left;
    return node;
}

static BSTNode* delete_node(BSTNode* node, int key, int* deleted) {
    if (!node) return NULL;
    if (key < node->key) {
        node->left = delete_node(node->left, key, deleted);
    } else if (key > node->key) {
        node->right = delete_node(node->right, key, deleted);
    } else {
        *deleted = 1;
        if (!node->left) {
            BSTNode* right = node->right;
            free(node);
            return right;
        }
        if (!node->right) {
            BSTNode* left = node->left;
            free(node);
            return left;
        }
        // Два ребёнка: заменяем минимальным из правого поддерева
        BSTNode* successor = min_node(node->right);
        node->key = successor->key;
        int dummy = 0;
        node->right = delete_node(node->right, successor->key, &dummy);
    }
    return node;
}

static void inorder_node(const BSTNode* node, void (*callback)(int)) {
    if (!node) return;
    inorder_node(node->left, callback);
    callback(node->key);
    inorder_node(node->right, callback);
}

static void preorder_node(const BSTNode* node, void (*callback)(int)) {
    if (!node) return;
    callback(node->key);
    preorder_node(node->left, callback);
    preorder_node(node->right, callback);
}

static void postorder_node(const BSTNode* node, void (*callback)(int)) {
    if (!node) return;
    postorder_node(node->left, callback);
    postorder_node(node->right, callback);
    callback(node->key);
}

static int height_node(const BSTNode* node) {
    if (!node) return 0;
    int lh = height_node(node->left);
    int rh = height_node(node->right);
    return 1 + (lh > rh ? lh : rh);
}

static int is_valid_node(const BSTNode* node, ll min, ll max) {
    if (!node) return 1;
    if ((ll)node->key <= min || (ll)node->key >= max) return 0;
    return is_valid_node(node->left, min, (ll)node->key) &&
           is_valid_node(node->right, (ll)node->key, max);
}

// ---------- публичные функции ----------

BST* create_bst() {
    BST* tree = (BST*)malloc(sizeof(BST));
    if (!tree) return NULL;
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

void destroy_bst(BST** tree) {
    if (!tree || !*tree) return;
    destroy_node_recursive((*tree)->root);
    free(*tree);
    *tree = NULL;
}

BST* copy_bst(const BST* tree) {
    if (!tree) return NULL;
    BST* new_tree = create_bst();
    if (!new_tree) return NULL;
    new_tree->root = copy_node_recursive(tree->root);
    new_tree->size = tree->size;
    return new_tree;
}

void insert_bst(BST* tree, int key) {
    if (!tree) return;
    int inserted = 0;
    tree->root = insert_node(tree->root, key, &inserted);
    if (inserted) tree->size++;
}

int search_bst(const BST* tree, int key) {
    if (!tree) return 0;
    return search_node(tree->root, key);
}

void delete_bst(BST* tree, int key) {
    if (!tree) return;
    int deleted = 0;
    tree->root = delete_node(tree->root, key, &deleted);
    if (deleted) tree->size--;
}

int min_bst(const BST* tree) {
    if (!tree || !tree->root) return INT_MIN;
    return min_node(tree->root)->key;
}

int max_bst(const BST* tree) {
    if (!tree || !tree->root) return INT_MAX;
    BSTNode* node = tree->root;
    while (node->right) node = node->right;
    return node->key;
}

void inorder_bst(const BST* tree, void (*callback)(int key)) {
    if (!tree || !callback) return;
    inorder_node(tree->root, callback);
}

void preorder_bst(const BST* tree, void (*callback)(int key)) {
    if (!tree || !callback) return;
    preorder_node(tree->root, callback);
}

void postorder_bst(const BST* tree, void (*callback)(int key)) {
    if (!tree || !callback) return;
    postorder_node(tree->root, callback);
}

int height_bst(const BST* tree) {
    if (!tree) return 0;
    return height_node(tree->root);
}

int is_valid_bst(const BST* tree) {
    if (!tree) return 0;
    return is_valid_node(tree->root, (ll)INT_MIN - 1, (ll)INT_MAX + 1);
}
