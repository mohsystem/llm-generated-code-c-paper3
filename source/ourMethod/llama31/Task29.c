#include <stdio.h>

void twoSum(int numbers[], int target, int* indices, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (numbers[i] + numbers[j] == target) {
                indices[0] = i;
                indices[1] = j;
                return;
            }
        }
    }
    // This line should not be reached given the problem constraints
    indices[0] = -1;
    indices[1] = -1;
}

int main() {
    int numbers1[] = {1, 2, 3};
    int indices1[2];
    twoSum(numbers1, 4, indices1, 3);
    printf("Indices: (%d, %d)\n", indices1[0], indices1[1]);

    int numbers2[] = {3, 2, 4};
    int indices2[2];
    twoSum(numbers2, 6, indices2, 3);
    printf("Indices: (%d, %d)\n", indices2[0], indices2[1]);

    return 0;
}