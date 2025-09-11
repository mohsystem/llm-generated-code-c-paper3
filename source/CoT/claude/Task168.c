
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* tweakLetters(const char* str, int arr[], int size) {
    char* result = (char*)malloc((strlen(str) + 1) * sizeof(char));
    
    for(int i = 0; i < strlen(str); i++) {
        char c = str[i];
        int shift = arr[i];
        
        // Handle forward shift
        if(shift > 0) {
            if(c == 'z') {
                c = 'a';
            } else {
                c = c + shift;
            }
        }
        // Handle backward shift
        else if(shift < 0) {
            if(c == 'a') {
                c = 'z';
            } else {
                c = c + shift;
            }
        }
        result[i] = c;
    }
    result[strlen(str)] = '\\0';
    
    return result;
}

int main() {
    // Test cases
    int arr1[] = {0, 1, -1, 0, -1};
    printf("%s\\n", tweakLetters("apple", arr1, 5)); // "aqold"
    
    int arr2[] = {0, 0, 0, -1};
    printf("%s\\n", tweakLetters("many", arr2, 4)); // "manx"
    
    int arr3[] = {1, 1, 1, 1, 1};
    printf("%s\\n", tweakLetters("rhino", arr3, 5)); // "sijop"
    
    int arr4[] = {1, 1, 1};
    printf("%s\\n", tweakLetters("xyz", arr4, 3)); // "yza"
    
    int arr5[] = {-1, -1, -1};
    printf("%s\\n", tweakLetters("abc", arr5, 3)); // "zab"
    
    return 0;
}
