#include <stdio.h>
#include <limits.h>

#include "bst.h"
#include "assert_base.h"

// Вспомогательные структуры для проверки обходов
static int traversal_buf[256];
static int traversal_idx;

static void collect_key(int key) {
    traversal_buf[traversal_idx++] = key;
}

// ======================================================

void test_create_and_destroy() {
    printf("\n=== Test 1: Create and Destroy ===\n");

    BST* tree = create_bst();
    ASSERT_MSG(tree != NULL);
    ASSERT_MSG(tree->root == NULL);
    ASSERT_MSG(tree->size == 0);

    destroy_bst(&tree);
    ASSERT_MSG(tree == NULL);

    printf("✓ Test 1 passed\n");
}

void test_insert_and_search() {
    printf("\n=== Test 2: Insert and Search ===\n");

    BST* tree = create_bst();

    insert_bst(tree, 10);
    ASSERT_MSG(tree->size == 1);
    ASSERT_MSG(search_bst(tree, 10) == 1);
    ASSERT_MSG(search_bst(tree, 5) == 0);

    insert_bst(tree, 5);
    insert_bst(tree, 15);
    ASSERT_MSG(tree->size == 3);
    ASSERT_MSG(search_bst(tree, 5) == 1);
    ASSERT_MSG(search_bst(tree, 15) == 1);
    ASSERT_MSG(search_bst(tree, 20) == 0);

    // Дубликат не увеличивает размер
    insert_bst(tree, 10);
    ASSERT_MSG(tree->size == 3);

    destroy_bst(&tree);
    printf("✓ Test 2 passed\n");
}

void test_delete() {
    printf("\n=== Test 3: Delete ===\n");

    BST* tree = create_bst();
    insert_bst(tree, 10);
    insert_bst(tree, 5);
    insert_bst(tree, 15);
    insert_bst(tree, 3);
    insert_bst(tree, 7);

    // Удаление листа
    delete_bst(tree, 3);
    ASSERT_MSG(tree->size == 4);
    ASSERT_MSG(search_bst(tree, 3) == 0);
    ASSERT_MSG(search_bst(tree, 5) == 1);

    // Удаление узла с одним ребёнком
    delete_bst(tree, 5);
    ASSERT_MSG(tree->size == 3);
    ASSERT_MSG(search_bst(tree, 5) == 0);
    ASSERT_MSG(search_bst(tree, 7) == 1);

    // Удаление корня (два ребёнка)
    delete_bst(tree, 10);
    ASSERT_MSG(tree->size == 2);
    ASSERT_MSG(search_bst(tree, 10) == 0);
    ASSERT_MSG(search_bst(tree, 15) == 1);
    ASSERT_MSG(search_bst(tree, 7) == 1);

    // Удаление несуществующего ключа
    delete_bst(tree, 99);
    ASSERT_MSG(tree->size == 2);

    destroy_bst(&tree);
    printf("✓ Test 3 passed\n");
}

void test_min_max() {
    printf("\n=== Test 4: Min and Max ===\n");

    BST* tree = create_bst();
    insert_bst(tree, 10);
    insert_bst(tree, 5);
    insert_bst(tree, 15);
    insert_bst(tree, 2);
    insert_bst(tree, 20);

    _ASSERT_MSG(min_bst(tree) == 2, "min expected 2, got %d", min_bst(tree));
    _ASSERT_MSG(max_bst(tree) == 20, "max expected 20, got %d", max_bst(tree));

    delete_bst(tree, 2);
    _ASSERT_MSG(min_bst(tree) == 5, "min expected 5, got %d", min_bst(tree));

    delete_bst(tree, 20);
    _ASSERT_MSG(max_bst(tree) == 15, "max expected 15, got %d", max_bst(tree));

    destroy_bst(&tree);
    printf("✓ Test 4 passed\n");
}

void test_inorder_sorted() {
    printf("\n=== Test 5: Inorder gives sorted sequence ===\n");

    BST* tree = create_bst();
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = (int)(sizeof(values) / sizeof(values[0]));
    for (int i = 0; i < n; i++) insert_bst(tree, values[i]);

    traversal_idx = 0;
    inorder_bst(tree, collect_key);
    _ASSERT_MSG(traversal_idx == n, "inorder count expected %d, got %d", n, traversal_idx);

    for (int i = 1; i < traversal_idx; i++) {
        _ASSERT_MSG(traversal_buf[i - 1] < traversal_buf[i],
                    "inorder not sorted at index %d: %d >= %d",
                    i, traversal_buf[i - 1], traversal_buf[i]);
    }

    destroy_bst(&tree);
    printf("✓ Test 5 passed\n");
}

void test_preorder() {
    printf("\n=== Test 6: Preorder traversal ===\n");

    BST* tree = create_bst();
    insert_bst(tree, 10);
    insert_bst(tree, 5);
    insert_bst(tree, 15);

    // Ожидаемый порядок: 10, 5, 15
    traversal_idx = 0;
    preorder_bst(tree, collect_key);
    _ASSERT_MSG(traversal_idx == 3, "preorder count expected 3, got %d", traversal_idx);
    _ASSERT_MSG(traversal_buf[0] == 10, "preorder[0] expected 10, got %d", traversal_buf[0]);
    _ASSERT_MSG(traversal_buf[1] == 5, "preorder[1] expected 5, got %d", traversal_buf[1]);
    _ASSERT_MSG(traversal_buf[2] == 15, "preorder[2] expected 15, got %d", traversal_buf[2]);

    destroy_bst(&tree);
    printf("✓ Test 6 passed\n");
}

void test_postorder() {
    printf("\n=== Test 7: Postorder traversal ===\n");

    BST* tree = create_bst();
    insert_bst(tree, 10);
    insert_bst(tree, 5);
    insert_bst(tree, 15);

    // Ожидаемый порядок: 5, 15, 10
    traversal_idx = 0;
    postorder_bst(tree, collect_key);
    _ASSERT_MSG(traversal_idx == 3, "postorder count expected 3, got %d", traversal_idx);
    _ASSERT_MSG(traversal_buf[0] == 5, "postorder[0] expected 5, got %d", traversal_buf[0]);
    _ASSERT_MSG(traversal_buf[1] == 15, "postorder[1] expected 15, got %d", traversal_buf[1]);
    _ASSERT_MSG(traversal_buf[2] == 10, "postorder[2] expected 10, got %d", traversal_buf[2]);

    destroy_bst(&tree);
    printf("✓ Test 7 passed\n");
}

void test_height() {
    printf("\n=== Test 8: Height ===\n");

    BST* tree = create_bst();
    _ASSERT_MSG(height_bst(tree) == 0, "empty tree height expected 0, got %d", height_bst(tree));

    insert_bst(tree, 10);
    _ASSERT_MSG(height_bst(tree) == 1, "height expected 1, got %d", height_bst(tree));

    insert_bst(tree, 5);
    insert_bst(tree, 15);
    _ASSERT_MSG(height_bst(tree) == 2, "height expected 2, got %d", height_bst(tree));

    insert_bst(tree, 3);
    _ASSERT_MSG(height_bst(tree) == 3, "height expected 3, got %d", height_bst(tree));

    destroy_bst(&tree);
    printf("✓ Test 8 passed\n");
}

void test_copy() {
    printf("\n=== Test 9: Copy ===\n");

    BST* original = create_bst();
    insert_bst(original, 10);
    insert_bst(original, 5);
    insert_bst(original, 15);
    insert_bst(original, 3);
    insert_bst(original, 7);

    BST* copy = copy_bst(original);
    ASSERT_MSG(copy != NULL);
    ASSERT_MSG(copy != original);
    _ASSERT_MSG(copy->size == original->size,
                "copy size expected %zu, got %zu", original->size, copy->size);

    // Изменяем копию, оригинал не должен изменяться
    delete_bst(copy, 3);
    _ASSERT_MSG(copy->size == 4, "copy size expected 4, got %zu", copy->size);
    _ASSERT_MSG(original->size == 5, "original size expected 5, got %zu", original->size);
    ASSERT_MSG(search_bst(original, 3) == 1);

    // Вставка в копию
    insert_bst(copy, 100);
    ASSERT_MSG(search_bst(copy, 100) == 1);
    ASSERT_MSG(search_bst(original, 100) == 0);

    destroy_bst(&original);
    destroy_bst(&copy);
    printf("✓ Test 9 passed\n");
}

void test_is_valid_bst() {
    printf("\n=== Test 10: is_valid_bst ===\n");

    BST* tree = create_bst();
    ASSERT_MSG(is_valid_bst(tree) == 1);

    insert_bst(tree, 10);
    insert_bst(tree, 5);
    insert_bst(tree, 15);
    ASSERT_MSG(is_valid_bst(tree) == 1);

    destroy_bst(&tree);
    printf("✓ Test 10 passed\n");
}

void test_edge_cases() {
    printf("\n=== Test 11: Edge Cases ===\n");

    // Удаление из пустого дерева
    BST* tree = create_bst();
    delete_bst(tree, 10);
    ASSERT_MSG(tree->size == 0);

    // Поиск в пустом дереве
    ASSERT_MSG(search_bst(tree, 10) == 0);

    // Вставка и удаление единственного элемента
    insert_bst(tree, 42);
    ASSERT_MSG(tree->size == 1);
    ASSERT_MSG(search_bst(tree, 42) == 1);
    delete_bst(tree, 42);
    ASSERT_MSG(tree->size == 0);
    ASSERT_MSG(tree->root == NULL);
    ASSERT_MSG(search_bst(tree, 42) == 0);

    // Множество вставок и удалений
    for (int i = 1; i <= 20; i++) insert_bst(tree, i);
    _ASSERT_MSG((int)tree->size == 20, "size expected 20, got %d", (int)tree->size);
    for (int i = 1; i <= 20; i += 2) delete_bst(tree, i);
    _ASSERT_MSG((int)tree->size == 10, "size expected 10, got %d", (int)tree->size);
    for (int i = 1; i <= 20; i += 2) ASSERT_MSG(search_bst(tree, i) == 0);
    for (int i = 2; i <= 20; i += 2) ASSERT_MSG(search_bst(tree, i) == 1);

    destroy_bst(&tree);
    printf("✓ Test 11 passed\n");
}

void test_large_tree() {
    printf("\n=== Test 12: Large Tree ===\n");

    BST* tree = create_bst();

    int values[] = {50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56, 68, 81, 93};
    int n = (int)(sizeof(values) / sizeof(values[0]));
    for (int i = 0; i < n; i++) insert_bst(tree, values[i]);

    _ASSERT_MSG((int)tree->size == n, "size expected %d, got %d", n, (int)tree->size);
    ASSERT_MSG(is_valid_bst(tree) == 1);

    _ASSERT_MSG(min_bst(tree) == 6, "min expected 6, got %d", min_bst(tree));
    _ASSERT_MSG(max_bst(tree) == 93, "max expected 93, got %d", max_bst(tree));

    // Inorder must be sorted
    traversal_idx = 0;
    inorder_bst(tree, collect_key);
    for (int i = 1; i < traversal_idx; i++) {
        _ASSERT_MSG(traversal_buf[i - 1] < traversal_buf[i],
                    "large tree inorder not sorted at %d", i);
    }

    destroy_bst(&tree);
    printf("✓ Test 12 passed\n");
}

int main() {
    printf("=== Running BST Tests ===\n");

    test_create_and_destroy();
    test_insert_and_search();
    test_delete();
    test_min_max();
    test_inorder_sorted();
    test_preorder();
    test_postorder();
    test_height();
    test_copy();
    test_is_valid_bst();
    test_edge_cases();
    test_large_tree();

    printf("\n=== All BST tests passed! ===\n");
    return 0;
}
