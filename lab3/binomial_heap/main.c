#include <stdio.h>


#include "binomial_heap.h"

int main() {
    BinomialHeap* heap = create_binomial_heap();


    int command, value;
    while (1) {
        printf("Enter command (0 - exit, 1 - insert, 2 - get_min, 3 - extract_min): ");
        if (scanf("%d", &command) != 1 || !command) {
            break;
        }
        switch (command) {
        case 1:
            printf("Enter value: ");
            scanf("%d", &value);
            insert_binomial_heap(&heap, value);
            break;
        case 2:
            printf("%d\n", get_binomial_heap(heap));
            break;

        case 3:
            extract_binomial_heap(&heap);
            break;
        }
    }
}
