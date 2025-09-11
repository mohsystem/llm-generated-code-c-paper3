#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mainFunction() {
    // Test cases
    char str1[] = "Hello";
    char str2[] = "World";
    char str3[] = "GeeksforGeeks";
    char str4[] = "this is init";
    char str5[] = " added now";

    printf("Original String: %s\n", str1);
    printf("Copied String: %s\n", copyString(str1));
    printf("Concatenated String: %s\n", concatenateStrings(str1, str2));
    printf("Modified String: %s\n", modifyString(str3, 6, 'F'));
    printf("Deleted Character String: %s\n", deleteCharacter(str3, 'G'));
    printf("Concatenated String: %s\n", concatenateStrings(str4, str5));
}

char* copyString(const char* str) {
    int len = strlen(str);
    char* copy = (char*)malloc(len + 1);
    strcpy(copy, str);
    return copy;
}

char* concatenateStrings(const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char* result = (char*)malloc(len1 + len2 + 1);
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

char* modifyString(const char* str, int index, char ch) {
    int len = strlen(str);
    char* modified = (char*)malloc(len + 1);
    strncpy(modified, str, index);
    modified[index] = ch;
    strcpy(modified + index + 1, str + index + 1);
    return modified;
}

char* deleteCharacter(const char* str, char ch) {
    int len = strlen(str);
    char* result = (char*)malloc(len + 1);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != ch) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    mainFunction();
    return 0;
}