#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readFromBuffer(int* buffer, int buffer_size, int index) {
    char* result = (char*)malloc(20 * sizeof(char)); // Allocate memory for the result string
    if (buffer == NULL) {
        strcpy(result, "Error: Buffer is null.");
        return result;
    }
    if (index < 0 || index >= buffer_size) {
        strcpy(result, "Error: Index out of bounds.");
        return result;
    }

    sprintf(result, "%d", buffer[index]);
    return result;
}

int main() {
    // Test cases
    int buffer1[5];
    for (int i = 0; i < 5; i++) {
        buffer1[i] = i * 10;
    }
    int buffer_size = sizeof(buffer1) / sizeof(buffer1[0]);

    char* output1 = readFromBuffer(buffer1, buffer_size, 2);
    printf("%s\n", output1); // Output: 20
    free(output1); // Free allocated memory

    char* output2 = readFromBuffer(buffer1, buffer_size, -1);
    printf("%s\n", output2); // Output: Error: Index out of bounds.
    free(output2);

    char* output3 = readFromBuffer(buffer1, buffer_size, 5);
    printf("%s\n", output3); // Output: Error: Index out of bounds.
    free(output3);

    char* output4 = readFromBuffer(NULL, buffer_size, 2);
    printf("%s\n", output4); // Output: Error: Buffer is null.
    free(output4);

    int buffer2[0];
    int buffer2_size = sizeof(buffer2) / sizeof(buffer2[0]);
    char* output5 = readFromBuffer(buffer2, buffer2_size, 0);
    printf("%s\n", output5); // Output: Error: Index out of bounds.
    free(output5);


    return 0;
}