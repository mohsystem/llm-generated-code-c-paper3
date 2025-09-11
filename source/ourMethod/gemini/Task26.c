#include <stdio.h>
#include <stdlib.h>

// Implementing a simplified hash map for C (limited functionality)
struct HashMap {
    int key;
    int value;
    struct HashMap *next;
};

struct HashMap* newHashMapNode(int key) {
    struct HashMap* node = (struct HashMap*)malloc(sizeof(struct HashMap));
    if (!node) return NULL; // Handle memory allocation failure
    node->key = key;
    node->value = 1;
    node->next = NULL;
    return node;
}


int findOdd(int arr[], int n) {
    struct HashMap *map = NULL;

     for (int i = 0; i < n; i++) {
        int num = arr[i];
        struct HashMap *current = map;
        struct HashMap *prev = NULL;
        while(current != NULL) {
            if(current->key == num) {
                current->value++;
                break;
            }
            prev = current;
            current = current->next;
        }
        if(current == NULL) {
            struct HashMap *newNode = newHashMapNode(num);
            if(prev == NULL) {
                map = newNode;
            } else {
                prev->next = newNode;
            }
        }
     }

    struct HashMap *current = map;
    while (current != NULL) {
        if (current->value % 2 != 0) {
            int result = current->key;
            // Free memory (important to avoid memory leaks)
            while (map != NULL) {
                struct HashMap* temp = map;
                map = map->next;
                free(temp);
            }
            return result;
        }
        current = current->next;
    }


    // Free memory (important to avoid memory leaks)
    while (map != NULL) {
        struct HashMap* temp = map;
        map = map->next;
        free(temp);
    }
    
    return -1; // Should not happen
}

int main() {
    int test1[] = {7};
    int test2[] = {0};
    int test3[] = {1, 1, 2};
    int test4[] = {0, 1, 0, 1, 0};
    int test5[] = {1, 2, 2, 3, 3, 3, 4, 3, 3, 3, 2, 2, 1};

    printf("%d\n", findOdd(test1, sizeof(test1) / sizeof(test1[0]))); // Expected: 7
    printf("%d\n", findOdd(test2, sizeof(test2) / sizeof(test2[0]))); // Expected: 0
    printf("%d\n", findOdd(test3, sizeof(test3) / sizeof(test3[0]))); // Expected: 2
    printf("%d\n", findOdd(test4, sizeof(test4) / sizeof(test4[0]))); // Expected: 0
    printf("%d\n", findOdd(test5, sizeof(test5) / sizeof(test5[0]))); // Expected: 4
    return 0;
}