#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate(const char** strings, int count) {
    int totalLength = 0;
    for (int i = 0; i < count; i++) {
        totalLength += strlen(strings[i]);
        if (i < count - 1) {
            totalLength += 1; // for the space
        }
    }

    char* result = (char*)malloc(totalLength + 1);
    result[totalLength] = '\0';

    int offset = 0;
    for (int i = 0; i < count; i++) {
        strcpy(result + offset, strings[i]);
        offset += strlen(strings[i]);
        if (i < count - 1) {
            result[offset] = ' ';
            offset += 1;
        }
    }

    return result;
}

void mainFunction() {
    const char* testCases[][5] = {
        {"Hello", "World", NULL},
        {"This", "is", "a", "test", NULL},
        {"Concatenating", "multiple", "strings", NULL},
        {"C", "is", "fun", NULL},
        {"Programming", "is", "awesome", NULL}
    };

    for (int i = 0; i < 5; i++) {
        int count = 0;
        while (testCases[i][count] != NULL) {
            count++;
        }
        char* result = concatenate((const char**)testCases[i], count);
        printf("%s\n", result);
        free(result);
    }
}

int main() {
    mainFunction();
    return 0;
}