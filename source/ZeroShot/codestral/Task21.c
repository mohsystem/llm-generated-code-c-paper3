#include <stdio.h>
#include <stdlib.h>

int* removeSmallest(int* numbers, int len, int* newLen) {
    if (len == 0) {
        *newLen = 0;
        return numbers;
    }

    int min = numbers[0];
    int minIndex = 0;
    for (int i = 1; i < len; i++) {
        if (numbers[i] < min) {
            min = numbers[i];
            minIndex = i;
        }
    }

    int* result = (int*)malloc(sizeof(int) * (len - 1));
    for (int i = 0, j = 0; i < len; i++) {
        if (i != minIndex) {
            result[j++] = numbers[i];
        }
    }

    *newLen = len - 1;
    return result;
}

int main() {
    int len1, len2, len3, len4, len5;
    int* result;

    int numbers1[] = {1, 2, 3, 4, 5};
    len1 = sizeof(numbers1) / sizeof(numbers1[0]);
    result = removeSmallest(numbers1, len1, &len1);
    for (int i = 0; i < len1; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    free(result);

    int numbers2[] = {5, 3, 2, 1, 4};
    len2 = sizeof(numbers2) / sizeof(numbers2[0]);
    result = removeSmallest(numbers2, len2, &len2);
    for (int i = 0; i < len2; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    free(result);

    int numbers3[] = {2, 2, 1, 2, 1};
    len3 = sizeof(numbers3) / sizeof(numbers3[0]);
    result = removeSmallest(numbers3, len3, &len3);
    for (int i = 0; i < len3; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    free(result);

    int numbers4[] = {};
    len4 = sizeof(numbers4) / sizeof(numbers4[0]);
    result = removeSmallest(numbers4, len4, &len4);
    for (int i = 0; i < len4; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    free(result);

    int numbers5[] = {1, 1, 1, 1, 1};
    len5 = sizeof(numbers5) / sizeof(numbers5[0]);
    result = removeSmallest(numbers5, len5, &len5);
    for (int i = 0; i < len5; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    free(result);

    return 0;
}