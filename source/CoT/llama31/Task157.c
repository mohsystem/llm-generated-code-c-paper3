#include <stdio.h>
#include <stdlib.h>

void allocateAndDeallocate(int size) {
    int* data = malloc(size * sizeof(int));
    if (data == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    printf("Allocated memory of size %d\n", size);
    free(data);
    data = NULL;
    printf("Memory deallocated.\n");
}

int main() {
    // Test cases
    for (int i = 1; i <= 5; ++i) {
        allocateAndDeallocate(i * 10);
    }
    return 0;
}