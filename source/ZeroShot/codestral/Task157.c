#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate memory
    int* arr = (int*) malloc(5 * sizeof(int));
    // Use the memory
    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }
    // Deallocate memory
    free(arr);
    return 0;
}