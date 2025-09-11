
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* tweakLetters(const char* word, const int* arr, int length) {
    if (!word || !arr || strlen(word) != length || length <= 0) {
        return NULL;
    }
    
    char* result = (char*)malloc(length + 1);
    if (!result) {
        return NULL;
    }
    
    for (int i = 0; i < length; i++) {
        // Calculate new position
        int newPos = ((word[i] - 'a' + arr[i]) % 26);
        // Handle negative shifts
        if (newPos < 0) {
            newPos += 26;
        }
        // Convert back to character
        result[i] = 'a' + newPos;
    }
    result[length] = '\\0';
    
    return result;
}

int main() {
    // Test cases
    int arr1[] = {0, 1, -1, 0, -1};
    char* result1 = tweakLetters("apple", arr1, 5);
    printf("%s\\n", result1); // "aqold"
    free(result1);
    
    int arr2[] = {0, 0, 0, -1};
    char* result2 = tweakLetters("many", arr2, 4);
    printf("%s\\n", result2); // "manx"
    free(result2);
    
    int arr3[] = {1, 1, 1, 1, 1};
    char* result3 = tweakLetters("rhino", arr3, 5);
    printf("%s\\n", result3); // "sijop"
    free(result3);
    
    int arr4[] = {1, 1, 1};
    char* result4 = tweakLetters("xyz", arr4, 3);
    printf("%s\\n", result4); // "yza"
    free(result4);
    
    int arr5[] = {-1, -1, -1};
    char* result5 = tweakLetters("abc", arr5, 3);
    printf("%s\\n", result5); // "zab"
    free(result5);
    
    return 0;
}
