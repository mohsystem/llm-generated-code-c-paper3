#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readBufferAtIndex(int* buffer, int size, int index) {
    char* result = (char*)malloc(20 * sizeof(char)); // Allocate memory for the result string

    if (index >= 0 && index < size) {
        sprintf(result, "%d", buffer[index]); // Convert integer to string
    } else {
        strcpy(result, "Index out of bounds");
    }
    return result;
}

int main() {
    // Test cases
    int buffer1[] = {1, 2, 3, 4, 5};
    char *result1 = readBufferAtIndex(buffer1, 5, 2);
    printf("%s\n", result1); // Output: 3
    free(result1);
    result1 = readBufferAtIndex(buffer1, 5, 5);
    printf("%s\n", result1); // Output: Index out of bounds
    free(result1);


    int buffer2[] = {10, 20, 30};
    char *result2 = readBufferAtIndex(buffer2, 3, 0);
    printf("%s\n", result2); // Output: 10
    free(result2);

    result2 = readBufferAtIndex(buffer2, 3, -1);
    printf("%s\n", result2); // Output: Index out of bounds
    free(result2);

    // Example usage with dynamic allocation and user input
    int size;
    printf("Enter the size of the buffer: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Invalid buffer size\n");
        return 1;
    }

    int* buffer = (int*)malloc(size * sizeof(int));
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter the buffer elements: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &buffer[i]);
    }

    int index;
    printf("Enter the index to read: ");
    scanf("%d", &index);


    char *result = readBufferAtIndex(buffer, size, index);
    printf("%s\n", result);
    free(result);
    free(buffer);


    return 0;
}