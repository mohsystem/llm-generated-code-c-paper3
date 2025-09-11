#include <stdio.h>
#include <stdlib.h>

void allocateMemory(int** data, size_t size) {
    *data = (int*)malloc(size * sizeof(int));
}

void deallocateMemory(int* data) {
    free(data);
}

int main() {
    for (int i = 0; i < 5; ++i) {
        int* data = NULL;
        allocateMemory(&data, 10);
        if (data != NULL) {
            for (int j = 0; j < 10; ++j) {
                data[j] = j + 1;
            }
            deallocateMemory(data);
        }
    }
    return 0;
}