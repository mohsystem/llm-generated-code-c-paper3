#include <stdio.h>
#include <stdlib.h>

int missingNumber(int arr[], int n) {
    int size = n + 1;
    int* hash = (int*)calloc(size + 1, sizeof(int));
    for (int i = 0; i < n; i++) {
        hash[arr[i]]++;
    }
    for (int i = 1; i <= size; i++) {
        if (hash[i] == 0) {
            free(hash);
            return i;
        }
    }
    free(hash);
    return -1;
}

int main() {
    int arr1[] = {1, 2, 4, 5};
    int arr2[] = {1, 2, 3, 5};
    int arr3[] = {1, 3, 4, 5};
    int arr4[] = {2, 3, 4, 5};
    int arr5[] = {1, 2, 3, 4};

    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    int n5 = sizeof(arr5) / sizeof(arr5[0]);

    printf("Missing number in arr1: %d\n", missingNumber(arr1, n1));
    printf("Missing number in arr2: %d\n", missingNumber(arr2, n2));
    printf("Missing number in arr3: %d\n", missingNumber(arr3, n3));
    printf("Missing number in arr4: %d\n", missingNumber(arr4, n4));
    printf("Missing number in arr5: %d\n", missingNumber(arr5, n5));

    return 0;
}