#include <stdio.h>
#include <stdlib.h>

void allocate_deallocate(int size) {
    int* ptr = malloc(size * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    printf("Allocated memory of size %d\n", size);
    free(ptr);
    ptr = NULL;
    printf("Deallocated memory of size %d\n", size);
}

int main() {
    int test_cases[] = {10, 20, 30, 40, 50};
    int n = sizeof(test_cases) / sizeof(test_cases[0]);
    for (int i = 0; i < n; i++) {
        allocate_deallocate(test_cases[i]);
    }
    return 0;
}