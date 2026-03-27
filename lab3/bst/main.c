#include <stdio.h>

#include "bst.h"

static void print_key(int key) {
    printf("%d ", key);
}

int main() {
    BST* tree = create_bst();

    int command, value;
    while (1) {
        printf("Enter command (0 - exit, 1 - insert, 2 - search, 3 - delete, 4 - min, 5 - max, 6 - inorder): ");
        if (scanf("%d", &command) != 1 || !command) {
            break;
        }
        switch (command) {
        case 1:
            printf("Enter value: ");
            if (scanf("%d", &value) != 1) break;
            insert_bst(tree, value);
            printf("Inserted %d. Size: %zu\n", value, tree->size);
            break;
        case 2:
            printf("Enter value: ");
            if (scanf("%d", &value) != 1) break;
            printf("%s\n", search_bst(tree, value) ? "Found" : "Not found");
            break;
        case 3:
            printf("Enter value: ");
            if (scanf("%d", &value) != 1) break;
            delete_bst(tree, value);
            printf("Deleted %d (if existed). Size: %zu\n", value, tree->size);
            break;
        case 4:
            printf("Min: %d\n", min_bst(tree));
            break;
        case 5:
            printf("Max: %d\n", max_bst(tree));
            break;
        case 6:
            printf("Inorder: ");
            inorder_bst(tree, print_key);
            printf("\n");
            break;
        }
    }

    destroy_bst(&tree);
    return 0;
}
