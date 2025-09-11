#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int* convertToInt(const char* input) {
    char* endptr;
    errno = 0; 
    long val = strtol(input, &endptr, 10);

    if (endptr == input || *endptr != '\0' || errno == ERANGE) {
        return NULL;
    } else {
        int* result = (int*)malloc(sizeof(int));
        if (result != NULL) {
            *result = (int)val;
        }
        return result;
    }
}

int main() {
    const char* testInputs[] = {"123", "abc", "456", "78.9", "1000"};
    size_t testCount = sizeof(testInputs) / sizeof(testInputs[0]);

    for (size_t i = 0; i < testCount; ++i) {
        int* result = convertToInt(testInputs[i]);
        if (result != NULL) {
            printf("Converted: %d\n", *result);
            free(result);
        } else {
            printf("Conversion failed for input: %s\n", testInputs[i]);
        }
    }

    return 0;
}