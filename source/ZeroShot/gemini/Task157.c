#include <stdio.h>
#include <stdlib.h>

int* allocateIntArray(int size) {
    if (size <= 0) {
        fprintf(stderr, "Cannot allocate array of non-positive size.\n");
        return NULL;
    }

    int* arr = (int*)malloc(size * sizeof(int));

    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    return arr;

}

void deallocateIntArray(int* arr) {
    free(arr);
}


void test(int size) {
    int* arr = allocateIntArray(size);
    if (arr != NULL) {
        printf("Allocated array of size: %d\n", size);
        deallocateIntArray(arr);
        printf("Deallocated array of size: %d\n", size);

    }
}

int main() {
    test(10);
    test(20);
    test(0);
    test(5);
    test(15);
    return 0;
}