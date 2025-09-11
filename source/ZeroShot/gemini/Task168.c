#include <stdio.h>
#include <string.h>

char* tweakLetters(char* str, int arr[], int arr_size) {
    for (int i = 0; i < arr_size && i < strlen(str); i++) {
        str[i] += arr[i];
    }
    return str;
}

int main() {
    char str1[] = "apple";
    int arr1[] = {0, 1, -1, 0, -1};
    printf("%s\n", tweakLetters(str1, arr1, 5)); // aqold

    char str2[] = "many";
    int arr2[] = {0, 0, 0, -1};
    printf("%s\n", tweakLetters(str2, arr2, 4)); // manx

    char str3[] = "rhino";
    int arr3[] = {1, 1, 1, 1, 1};
    printf("%s\n", tweakLetters(str3, arr3, 5)); // sijop

    char str4[] = "xyz";
    int arr4[] = {1, 1, 1};
    printf("%s\n", tweakLetters(str4, arr4, 3)); // yza


    char str5[] = "abc";
    int arr5[] = {-1, -1, -1};
    printf("%s\n", tweakLetters(str5, arr5, 3)); // zab

    return 0;
}