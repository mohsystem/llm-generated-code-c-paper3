#include <stdio.h>
#include <stdlib.h>

int* buffer;
int buffer_size;

void allocate_buffer(int size) {
    buffer = (int*)malloc(size * sizeof(int));
    buffer_size = size;
    for (int i = 0; i < size; i++) {
        buffer[i] = i;
    }
}

int read_from_buffer(int index) {
    if (index >= 0 && index < buffer_size) {
        return buffer[index];
    } else {
        fprintf(stderr, "Index is out of bounds.\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    allocate_buffer(10);
    printf("%d\n", read_from_buffer(5));  // Should print 5
    read_from_buffer(10);  // Should print an error message and exit
    return 0;
}