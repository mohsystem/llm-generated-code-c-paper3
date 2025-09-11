#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int* convertStringToInt(const char* input) {
    char* end;
    errno = 0;
    long value = strtol(input, &end, 10);
    if (end == input || errno != 0) {
        return NULL;
    }
    int* result = (int*)malloc(sizeof(int));
    if (result != NULL) {
        *result = (int)value;
    }
    return result;
}

int main() {
    const char* testCases[] = {"123", "abc", "456", "78.9", "-10"};
    size_t testCasesSize = sizeof(testCases) / sizeof(testCases[0]);
    
    for (size_t i = 0; i < testCasesSize; i++) {
        int* result = convertStringToInt(testCases[i]);
        printf("Input: %s | Output: %s\n", testCases[i], result ? (char[12]){0} + sprintf((char[12]){0}, "%d", *result) : "null");
        free(result);
    }
    
    return 0;
}