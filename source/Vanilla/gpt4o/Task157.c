#include <stdio.h>
#include <stdlib.h>

void memoryManagement() {
    int* array = (int*)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }
    free(array);
}

int main() {
    for (int i = 0; i < 5; i++) {
        memoryManagement();
    }
    return 0;
}