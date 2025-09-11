#include <stdio.h>
#include <stdlib.h>

int readBuffer(int* buffer, int bufferSize, int index) {
    if (index < 0 || index >= bufferSize) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return buffer[index];
}

int main() {
    int bufferSize = 10;
    int* buffer = malloc(bufferSize * sizeof(int));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < bufferSize; ++i) {
        buffer[i] = i * 10;
    }

    printf("Buffer contents: ");
    for (int i = 0; i < bufferSize; ++i) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    // Test cases
    int indices[] = {0, 3, 7, 9, 10};
    for (int i = 0; i < 5; ++i) {
        int index = indices[i];
        try {
            printf("Value at index %d: %d\n", index, readBuffer(buffer, bufferSize, index));
        } catch (...) {
            printf("Index %d is out of bounds.\n", index);
        }
    }

    free(buffer);
    return 0;
}