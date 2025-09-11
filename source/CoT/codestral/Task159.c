#include <stdio.h>
#include <stdlib.h>

int main() {
    int size = 10;
    int* buffer = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        buffer[i] = i;
    }
    int index;
    printf("Enter an index to read from the buffer: ");
    scanf("%d", &index);
    if (index < 0 || index >= size) {
        printf("Invalid index.\n");
    } else {
        printf("Value at index %d: %d\n", index, buffer[index]);
    }
    free(buffer);
    return 0;
}