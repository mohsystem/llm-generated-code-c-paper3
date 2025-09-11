#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool convert_to_integer(const char* input, int* result) {
    char* end;
    long value = strtol(input, &end, 10);
    if (*end == '\0' && input != end) {
        *result = (int)value;
        return true;
    }
    return false;
}

int main() {
    const char* testInputs[] = {"123", "abc", "456", "78.9", ""};
    for (int i = 0; i < 5; ++i) {
        int result;
        if (convert_to_integer(testInputs[i], &result)) {
            printf("Converted to integer: %d\n", result);
        } else {
            printf("Conversion failed for input: %s\n", testInputs[i]);
        }
    }
    return 0;
}