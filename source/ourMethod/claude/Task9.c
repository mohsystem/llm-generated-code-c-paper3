
#include <stdio.h>
#include <string.h>

const char* oddOrEven(const int arr[], int size) {
    if(size == 0) {
        return "even";
    }
    
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += arr[i];
    }
    
    return (sum % 2 == 0) ? "even" : "odd";
}

int main() {
    // Test cases
    int arr1[] = {0};
    int arr2[] = {0, 1, 4}; 
    int arr3[] = {0, -1, -5};
    int arr4[] = {2, 2, 2};
    
    printf("%s\\n", oddOrEven(arr1, 1)); // even
    printf("%s\\n", oddOrEven(arr2, 3)); // odd
    printf("%s\\n", oddOrEven(arr3, 3)); // even
    printf("%s\\n", oddOrEven(NULL, 0)); // even
    printf("%s\\n", oddOrEven(arr4, 3)); // even
    
    return 0;
}
