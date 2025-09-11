
#include <stdio.h>
#include <string.h>

void tweakLetters(char* word, int arr[], int size) {
    for(int i = 0; i < size; i++) {
        word[i] = (((word[i] - 'a' + arr[i]) % 26 + 26) % 26) + 'a';
    }
}

int main() {
    char word1[] = "apple";
    int arr1[] = {0, 1, -1, 0, -1};
    tweakLetters(word1, arr1, 5);
    printf("%s\\n", word1); // aqold
    
    char word2[] = "many";
    int arr2[] = {0, 0, 0, -1};
    tweakLetters(word2, arr2, 4);
    printf("%s\\n", word2); // manx
    
    char word3[] = "rhino";
    int arr3[] = {1, 1, 1, 1, 1};
    tweakLetters(word3, arr3, 5);
    printf("%s\\n", word3); // sijop
    
    char word4[] = "xyz";
    int arr4[] = {1, 1, 1};
    tweakLetters(word4, arr4, 3);
    printf("%s\\n", word4); // yza
    
    char word5[] = "abc";
    int arr5[] = {-1, -1, -1};
    tweakLetters(word5, arr5, 3);
    printf("%s\\n", word5); // zab
    
    return 0;
}
