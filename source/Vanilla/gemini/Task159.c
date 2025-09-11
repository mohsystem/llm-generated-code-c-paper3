#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readFromBuffer(int* buffer, int bufferSize, int index) {
    if (index >= 0 && index < bufferSize) {
        char* str = (char*)malloc(20 * sizeof(char)); // Allocate memory for the string
        sprintf(str, "%d", buffer[index]); // Convert int to string
        return str;
    } else {
        return "Error: Index out of bounds"; 
    }
}

int main() {
    int buffer[10];
    for (int i = 0; i < 10; i++) {
        buffer[i] = i * 10;
    }

    printf("Test cases:\n");

    char* result1 = readFromBuffer(buffer, 10, 5);
    printf("readFromBuffer(buffer, 5): %s\n", result1);
    free(result1); // Free allocated memory


    printf("readFromBuffer(buffer, 0): %s\n", readFromBuffer(buffer, 10, 0));
    printf("readFromBuffer(buffer, 9): %s\n", readFromBuffer(buffer, 10, 9));
    printf("readFromBuffer(buffer, -1): %s\n", readFromBuffer(buffer, 10, -1));
    printf("readFromBuffer(buffer, 10): %s\n", readFromBuffer(buffer, 10, 10));

    return 0;
}