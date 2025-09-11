#include <stdio.h>
#include <stdlib.h>

int* allocateBuffer(int size) {
    if (size < 0) {
        fprintf(stderr, "Buffer size cannot be negative.\n");
        return NULL; 
    }
    return (int*)malloc(size * sizeof(int));
}

int readBuffer(int* buffer, int size, int index) {
    if (index < 0 || index >= size) {
        fprintf(stderr, "Index %d is out of bounds for buffer of size %d\n", index, size);
        exit(1); // Or return a special error value if exiting is not desired
    }
    return buffer[index];
}

void test(int size, int indices[], int numIndices) {
    int* buffer = allocateBuffer(size);
    if(buffer == NULL && size > 0) return;
    for (int i = 0; i < size; i++) {
        buffer[i] = i * 10;
    }

    for (int i = 0; i < numIndices; i++) {
       
            int index = indices[i];
            if (index < 0 || index >= size)
             fprintf(stderr, "Index %d is out of bounds for buffer of size %d\n", index, size);

            else {
                int value = readBuffer(buffer, size, index);
                printf("Value at index %d: %d\n", index, value);
            }

    }
    printf("----\n");
    free(buffer);
}

int main() {
    int indices1[] = {0, 1, 2, 3, 4};
    test(5, indices1, 5);

    int indices2[] = {5, 6, 7, 1};
    test(3, indices2, 4);

    int indices3[] = {};
    test(0, indices3, 0);

    int indices4[] = {10};
    test(1, indices4, 1);

     int indices5[] = {-1, -2, 0};
    test(2, indices5, 3);

    return 0;
}