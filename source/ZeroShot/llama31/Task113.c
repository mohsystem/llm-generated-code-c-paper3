#include <stdio.h>
#include <string.h>

void concatenateStrings(char* dest, const char* str1, const char* str2, const char* str3) {
    strcpy(dest, str1);
    strcat(dest, " ");
    strcat(dest, str2);
    strcat(dest, " ");
    strcat(dest, str3);
}

int main() {
    char result[1024];
    // Test cases
    const char* testCases[][3] = {
        {"Hello", "World", "!"},
        {"This", "is", "a"},
        {"Concatenate", "these", "strings"},
        {"C", "is", "fun"},
        {"String", "concatenation", "example"}
    };

    for (int i = 0; i < 5; ++i) {
        concatenateStrings(result, testCases[i][0], testCases[i][1], testCases[i][2]);
        printf("%s\n", result);
    }

    return 0;
}