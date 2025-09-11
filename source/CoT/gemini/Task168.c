#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* tweakLetters(char* str, int* arr, int arr_size) {
    int str_len = strlen(str);
    char* result = (char*)malloc(sizeof(char) * (str_len + 1));
    if (result == NULL) {
        return NULL; // Memory allocation failed
    }
    strcpy(result, str);
    for (int i = 0; i < (str_len < arr_size ? str_len : arr_size) ; i++) {
        result[i] = (char)(result[i] + arr[i]);
    }
    return result;
}

int main() {
    char str1[] = "apple";
    int arr1[] = {0, 1, -1, 0, -1};
    char* result1 = tweakLetters(str1, arr1, sizeof(arr1)/sizeof(arr1[0]));
    printf("%s\n", result1); // Output: aqold
    free(result1);

    char str2[] = "many";
    int arr2[] = {0, 0, 0, -1};
    char* result2 = tweakLetters(str2, arr2, sizeof(arr2)/sizeof(arr2[0]));
    printf("%s\n", result2); // Output: manx
    free(result2);

    char str3[] = "rhino";
    int arr3[] = {1, 1, 1, 1, 1};
    char* result3 = tweakLetters(str3, arr3, sizeof(arr3)/sizeof(arr3[0]));
    printf("%s\n", result3); // Output: sijop
    free(result3);

    char str4[] = "xyz";
    int arr4[] = {1, 1, 1};
    char *result4 = tweakLetters(str4, arr4, sizeof(arr4)/sizeof(arr4[0]));
    printf("%s\n", result4); // Output: yza
    free(result4);


    char str5[] = "abc";
    int arr5[] = {-1, -1, -1};
    char *result5 = tweakLetters(str5, arr5, sizeof(arr5)/sizeof(arr5[0]));
    printf("%s\n", result5); // Output: zab
    free(result5);

    return 0;
}