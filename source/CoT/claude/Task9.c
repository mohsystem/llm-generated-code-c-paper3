
#include <stdio.h>
#include <string.h>

const char* oddOrEven(int arr[], int size) {
    if (size == 0) {
        return "even";
    }
    
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    
    return (sum % 2 == 0) ? "even" : "odd";
}

int main() {
    // Test cases
    int test1[] = {0};
    int test2[] = {0, 1, 4};
    int test3[] = {0, -1, -5};
    int test4[] = {};
    int test5[] = {1, 3, 5, 7};
    
    printf("%s\\n", oddOrEven(test1, 1));  // even
    printf("%s\\n", oddOrEven(test2, 3));  // odd
    printf("%s\\n", oddOrEven(test3, 3));  // even
    printf("%s\\n", oddOrEven(test4, 0));  // even
    printf("%s\\n", oddOrEven(test5, 4));  // even
    
    return 0;
}
