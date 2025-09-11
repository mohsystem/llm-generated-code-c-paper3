#include <stdio.h>
#include <stdlib.h>

char *oddOrEven(int *array, int size) {
    if (size == 0) {
        return "even";
    }
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return (sum % 2 == 0) ? "even" : "odd";
}

int main() {
    int arr1[] = {0};
    int arr2[] = {0, 1, 4};
    int arr3[] = {0, -1, -5};
    int arr4[] = {1, 2, 3, 4, 5};
    
    printf("%s\n", oddOrEven(arr1, sizeof(arr1)/sizeof(arr1[0])));
    printf("%s\n", oddOrEven(arr2, sizeof(arr2)/sizeof(arr2[0])));
    printf("%s\n", oddOrEven(arr3, sizeof(arr3)/sizeof(arr3[0])));
    printf("%s\n", oddOrEven(arr4, sizeof(arr4)/sizeof(arr4[0])));
    printf("%s\n", oddOrEven(NULL, 0));
    return 0;
}