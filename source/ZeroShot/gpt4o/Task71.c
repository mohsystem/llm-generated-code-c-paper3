#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int convertStringToInt(const char* input) {
    char* endptr;
    errno = 0; // To distinguish success/failure after call
    long result = strtol(input, &endptr, 10);
    
    if (errno == 0 && *endptr == '\0') {
        return (int)result;
    } else {
        return 0; // Return 0 if conversion fails
    }
}

int main() {
    const char* testInputs[] = {"123", "456", "789", "abc", "1000"};
    for (int i = 0; i < 5; ++i) {
        int result = convertStringToInt(testInputs[i]);
        if (result != 0 || testInputs[i][0] == '0') {
            printf("Conversion succeeded: %d\n", result);
        } else {
            printf("Conversion failed for input: %s\n", testInputs[i]);
        }
    }
    return 0;
}