#include <stdio.h>

void mergeSortedArrays(int arr1[], int size1, int arr2[], int size2, int mergedArray[]) {
    int i = 0, j = 0, k = 0;
    
    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            mergedArray[k++] = arr1[i++];
        } else {
            mergedArray[k++] = arr2[j++];
        }
    }
    
    while (i < size1) {
        mergedArray[k++] = arr1[i++];
    }
    
    while (j < size2) {
        mergedArray[k++] = arr2[j++];
    }
}

int main() {
    int result1[6];
    int result2[3];
    int result3[3];
    int result4[5];
    int result5[0];
    
    mergeSortedArrays((int[]){1, 3, 5}, 3, (int[]){2, 4, 6}, 3, result1);
    mergeSortedArrays((int[]){}, 0, (int[]){1, 2, 3}, 3, result2);
    mergeSortedArrays((int[]){1, 2, 3}, 3, (int[]){}, 0, result3);
    mergeSortedArrays((int[]){1, 3, 5}, 3, (int[]){7, 9}, 2, result4);
    mergeSortedArrays((int[]){}, 0, (int[]){}, 0, result5);
    
    for (int i = 0; i < 6; i++) printf("%d ", result1[i]);
    printf("\n");
    for (int i = 0; i < 3; i++) printf("%d ", result2[i]);
    printf("\n");
    for (int i = 0; i < 3; i++) printf("%d ", result3[i]);
    printf("\n");
    for (int i = 0; i < 5; i++) printf("%d ", result4[i]);
    printf("\n");
    for (int i = 0; i < 0; i++) printf("%d ", result5[i]);
    
    return 0;
}