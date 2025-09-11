#include <stdio.h>
#include <stdlib.h>

int* allocate(int size) {
    if (size <= 0) {
        return NULL;
    }
    return (int*)malloc(size * sizeof(int));
}

void deallocate(int* arr) {
    free(arr);
}

void test(int size) {
    int* arr = allocate(size);
    if (arr != NULL) {
        printf("Allocated array of size %d\n", size);
        deallocate(arr);
        printf("Deallocated array of size %d\n", size);
    }
}

int main() {
    test(10);
    test(20);
    test(0);
    test(100);
    test(1);
    return 0;
}