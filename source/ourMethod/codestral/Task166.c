#include <stdlib.h>

void posNegSort(int* nums, int size) {
    int* pos = malloc(size * sizeof(int));
    int posIndex = 0;
    for (int i = 0; i < size; i++) {
        if (nums[i] > 0) {
            pos[posIndex] = nums[i];
            posIndex++;
        }
    }
    for (int i = 0; i < posIndex - 1; i++) {
        for (int j = i + 1; j < posIndex; j++) {
            if (pos[i] > pos[j]) {
                int temp = pos[i];
                pos[i] = pos[j];
                pos[j] = temp;
            }
        }
    }
    posIndex = 0;
    for (int i = 0; i < size; i++) {
        if (nums[i] > 0) {
            nums[i] = pos[posIndex];
            posIndex++;
        }
    }
    free(pos);
}