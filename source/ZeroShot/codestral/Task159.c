#include <stdio.h>
#include <stdlib.h>

unsigned char* buffer;
int bufferSize;

void allocateBuffer(int size) {
    buffer = (unsigned char*)malloc(size * sizeof(unsigned char));
    bufferSize = size;
}

unsigned char readFromBuffer(int index) {
    if (index < 0 || index >= bufferSize) {
        fprintf(stderr, "Index is out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return buffer[index];
}

void freeBuffer() {
    free(buffer);
}

int main() {
    allocateBuffer(10);
    // Assume data is already filled into the buffer
    printf("%d\n", readFromBuffer(5));
    printf("%d\n", readFromBuffer(10)); // Exits with error message
    freeBuffer();
    return 0;
}