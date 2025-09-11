
#include <stdio.h>
#include <string.h>

void tweakLetters(char* str, int arr[], int size, char* result) {
    strcpy(result, str);
    for (int i = 0; i < size; i++) {
        int newPos = ((result[i] - 'a' + arr[i]) % 26 + 26) % 26;
        result[i] = 'a' + newPos;
    }
}

int main() {
    char result[100];
    
    // Test case 1
    int arr1[] = {0, 1, -1, 0, -1};
    tweakLetters("apple", arr1, 5, result);
    printf("%s\\n", result);
    
    // Test case 2
    int arr2[] = {0, 0, 0, -1};
    tweakLetters("many", arr2, 4, result);
    printf("%s\\n", result);
    
    // Test case 3
    int arr3[] = {1, 1, 1, 1, 1};
    tweakLetters("rhino", arr3, 5, result);
    printf("%s\\n", result);
    
    // Test case 4
    int arr4[] = {1, 1, 1};
    tweakLetters("xyz", arr4, 3, result);
    printf("%s\\n", result);
    
    // Test case 5
    int arr5[] = {-1, -1, -1};
    tweakLetters("abc", arr5, 3, result);
    printf("%s\\n", result);
    
    return 0;
}
