// C
#include <stdio.h>
#include <string.h>

char* concatenateStrings(char* result, const char* str1, const char* str2, const char* str3, const char* str4, const char* str5) {
    strcpy(result, str1);
    strcat(result, str2);
    strcat(result, str3);
    strcat(result, str4);
    strcat(result, str5);
    return result;
}

int main() {
    char result[1024];
    printf("%s\n", concatenateStrings(result, "Hello", " ", "World", "!", ""));
    printf("%s\n", concatenateStrings(result, "This", " ", "is", " ", "a test."));
    printf("%s\n", concatenateStrings(result, "Concatenating", " ", "multiple", " ", "strings."));
    printf("%s\n", concatenateStrings(result, "C", " ", "is", " ", "fun."));
    printf("%s\n", concatenateStrings(result, "Programming", " ", "is", " ", "awesome."));
    return 0;
}