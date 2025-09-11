#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char* tweakLetters(char* str, int* arr, int arr_size) {
    if (str == NULL || arr == NULL || strlen(str) != arr_size) {
        return NULL; // Or handle the error appropriately
    }

    char* result = (char*)malloc(strlen(str) + 1); // Allocate memory for the result
    if (result == NULL) {
        return NULL; // Handle memory allocation failure
    }
    strcpy(result, str);


    for (int i = 0; i < strlen(str); i++) {
        result[i] = (char)(result[i] + arr[i]);
    }

    return result;
}

int main() {
    char str1[] = "apple";
    int arr1[] = {0, 1, -1, 0, -1};
    char* result1 = tweakLetters(str1, arr1, sizeof(arr1)/sizeof(arr1[0]));
    printf("Test 1: %s\n", result1 ? result1 : "NULL"); // Output: aqold
    free(result1);


    char str2[] = "many";
    int arr2[] = {0, 0, 0, -1};
    char* result2 = tweakLetters(str2, arr2, sizeof(arr2)/sizeof(arr2[0]));
    printf("Test 2: %s\n", result2 ? result2 : "NULL"); // Output: manx
    free(result2);

    char str3[] = "rhino";
    int arr3[] = {1, 1, 1, 1, 1};
    char* result3 = tweakLetters(str3, arr3, sizeof(arr3)/sizeof(arr3[0]));
    printf("Test 3: %s\n", result3? result3 : "NULL"); // Output: sijop
    free(result3);

    char str4[] = "hello";
    int arr4[] = {0, 1, 0, -1, 0};
    char* result4 = tweakLetters(str4, arr4, sizeof(arr4)/sizeof(arr4[0]));
    printf("Test 4: %s\n", result4 ? result4 : "NULL"); // Output: hfmkp
    free(result4);

    char str5[] = "world";
    int arr5[] = {-1, 0, 1, 0, -1};
    char* result5 = tweakLetters(str5, arr5, sizeof(arr5)/sizeof(arr5[0]));
    printf("Test 5: %s\n", result5 ? result5 : "NULL"); // Output: vnqsc
    free(result5);

    return 0;
}