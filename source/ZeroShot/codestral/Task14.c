#include <stdio.h>

int find_even_index(int arr[], int size) {
    int left = 0, right = 0;
    for (int i = 0; i < size; i++) {
        right += arr[i];
    }
    for (int i = 0; i < size; i++) {
        right -= arr[i];
        if (left == right) {
            return i;
        }
        left += arr[i];
    }
    return -1;
}

int main() {
    int arr1[] = {1,2,3,4,3,2,1};
    printf("%d\n", find_even_index(arr1, sizeof(arr1)/sizeof(arr1[0]))); // 3
    int arr2[] = {1,100,50,-51,1,1};
    printf("%d\n", find_even_index(arr2, sizeof(arr2)/sizeof(arr2[0]))); // 1
    int arr3[] = {20,10,-80,10,10,15,35};
    printf("%d\n", find_even_index(arr3, sizeof(arr3)/sizeof(arr3[0]))); // 0
    int arr4[] = {1,2,3,4,5,6};
    printf("%d\n", find_even_index(arr4, sizeof(arr4)/sizeof(arr4[0]))); // -1
    int arr5[] = {20,10,30,10,10,15,35};
    printf("%d\n", find_even_index(arr5, sizeof(arr5)/sizeof(arr5[0]))); // 3
    return 0;
}