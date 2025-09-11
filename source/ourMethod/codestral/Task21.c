#include <stdio.h>
#include <limits.h>

void removeSmallest(int numbers[], int length) {
    int smallest = INT_MAX;
    int index = -1;

    for (int i = 0; i < length; i++) {
        if (numbers[i] < smallest) {
            smallest = numbers[i];
            index = i;
        }
    }

    for (int i = index; i < length - 1; i++) {
        numbers[i] = numbers[i + 1];
    }
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int length = sizeof(numbers)/sizeof(numbers[0]);
    removeSmallest(numbers, length);
    for(int i = 0; i < length - 1; i++) printf("%d ", numbers[i]);
    printf("\n");
    return 0;
}