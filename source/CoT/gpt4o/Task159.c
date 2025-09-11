#include <stdio.h>
#include <stdlib.h>

int readBuffer(int *buffer, int size, int index, int *value) {
    if (index < 0 || index >= size) {
        return 0;
    }
    *value = buffer[index];
    return 1;
}

void runTest(int *buffer, int size, int index) {
    int result;
    if (readBuffer(buffer, size, index, &result)) {
        printf("Value at index %d: %d\n", index, result);
    } else {
        printf("Invalid index: %d\n", index);
    }
}

int main() {
    int buffer1[] = {1, 2, 3, 4, 5};
    int buffer2[] = {10, 20, 30, 40, 50};
    int buffer3[] = {100, 200, 300};
    int buffer4[] = {7, 8, 9};
    int buffer5[] = {11, 22, 33};

    // Test cases
    runTest(buffer1, 5, 2); // Valid index
    runTest(buffer2, 5, 0); // First index
    runTest(buffer3, 3, 2); // Last index
    runTest(buffer4, 3, 5); // Invalid index
    runTest(buffer5, 3, -1); // Invalid index

    return 0;
}