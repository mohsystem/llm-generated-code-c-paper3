#include <stdio.h>
#include <stdlib.h>

int readBuffer(int* buffer, int size, int index) {
    if (index < 0 || index >= size) {
        return -1; // Out of bounds
    }
    return buffer[index];
}

void printBuffer(int* buffer, int size) {
    printf("Buffer contents: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

int main() {
    int size = 10;
    int* buffer = (int*)malloc(size * sizeof(int));
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    for (int i = 0; i < size; i++) {
        buffer[i] = i * 10;
    }

    printBuffer(buffer, size);

    // Test cases
    printf("Value at index 3: %d\n", readBuffer(buffer, size, 3));
    printf("Value at index 7: %d\n", readBuffer(buffer, size, 7));
    printf("Value at index 9: %d\n", readBuffer(buffer, size, 9));
    printf("Value at index 10 (out of bounds): %d\n", readBuffer(buffer, size, 10));
    printf("Value at index -1 (out of bounds): %d\n", readBuffer(buffer, size, -1));

    free(buffer);
    return 0;
}