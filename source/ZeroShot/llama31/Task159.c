#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void printBuffer(int* buffer, int size) {
    printf("Buffer values: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

int readFromBuffer(int* buffer, int size, int index) {
    if (index < 0 || index >= size) {
        fprintf(stderr, "Index is out of bounds.\n");
        exit(EXIT_FAILURE);
    }
    return buffer[index];
}

void testCases(int* buffer, int size) {
    for (int i = 0; i < 5; ++i) {
        int value = readFromBuffer(buffer, size, i);
        printf("Value at index %d: %d\n", i, value);
    }
}

int main() {
    const int size = 10;
    int* buffer = malloc(size * sizeof(int));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; ++i) {
        buffer[i] = i * 10;
    }

    printBuffer(buffer, size);
    testCases(buffer, size);

    free(buffer);
    return 0;
}