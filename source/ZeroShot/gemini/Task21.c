#include <stdio.h>
#include <stdlib.h>

int* removeSmallest(int numbers[], int count, int* newCount) {
    if (count == 0) {
        *newCount = 0;
        return NULL;
    }

    int minVal = numbers[0];
    int minIndex = 0;

    for (int i = 1; i < count; i++) {
        if (numbers[i] < minVal) {
            minVal = numbers[i];
            minIndex = i;
        }
    }

    int* result = (int*)malloc((count - 1) * sizeof(int));
    *newCount = count - 1;

    int j = 0;
    for (int i = 0; i < count; i++) {
        if (i != minIndex) {
            result[j++] = numbers[i];
        }
    }
    return result;
}

int main() {
    int test1[] = {1, 2, 3, 4, 5};
    int count1 = sizeof(test1) / sizeof(test1[0]);
    int newCount1;
    int* result1 = removeSmallest(test1, count1, &newCount1);
    for (int i = 0; i < newCount1; i++) printf("%d ", result1[i]);
    printf("\n"); // Output: 2 3 4 5
    free(result1);


    int test2[] = {5, 3, 2, 1, 4};
    int count2 = sizeof(test2) / sizeof(test2[0]);
    int newCount2;
    int* result2 = removeSmallest(test2, count2, &newCount2);
    for (int i = 0; i < newCount2; i++) printf("%d ", result2[i]);
    printf("\n"); // Output: 5 3 2 4
    free(result2);

    int test3[] = {2, 2, 1, 2, 1};
    int count3 = sizeof(test3) / sizeof(test3[0]);
    int newCount3;
    int* result3 = removeSmallest(test3, count3, &newCount3);
    for (int i = 0; i < newCount3; i++) printf("%d ", result3[i]);
    printf("\n"); // Output: 2 2 2 1
    free(result3);

    int test4[] = {};
    int count4 = sizeof(test4) / sizeof(test4[0]);
    int newCount4;
    int* result4 = removeSmallest(test4, count4, &newCount4);
    for (int i = 0; i < newCount4; i++) printf("%d ", result4[i]);
    printf("\n"); // Output: 
    free(result4);


    int test5[] = {5};
    int count5 = sizeof(test5) / sizeof(test5[0]);
    int newCount5;
    int* result5 = removeSmallest(test5, count5, &newCount5);
    for (int i = 0; i < newCount5; i++) printf("%d ", result5[i]);
    printf("\n"); // Output:
    free(result5);

    return 0;
}