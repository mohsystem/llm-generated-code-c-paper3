#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void printBuffer(int* buffer, int bufferSize) {
    printf("Buffer content: ");
    for (int i = 0; i < bufferSize; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

int readFromBuffer(int* buffer, int bufferSize, int index) {
    if (index >= 0 && index < bufferSize) {
        return buffer[index];
    } else {
        printf("Index out of bounds.\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int bufferSize = 10;
    int* buffer = (int*)malloc(bufferSize * sizeof(int));
    if (buffer == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < bufferSize; i++) {
        buffer[i] = i * 10;
    }

    printBuffer(buffer, bufferSize);

    // Test cases
    int indices[] = {0, 3, 7, 9};
    for (int index : indices) {
        printf("Value at index %d: %d\n", index, readFromBuffer(buffer, bufferSize, index));
    }

    free(buffer);
    return 0;
}