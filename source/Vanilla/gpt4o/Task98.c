#include <stdio.h>
#include <stdlib.h>

int convertToInt(const char* input) {
    char* end;
    int result = strtol(input, &end, 10);
    if (*end != '\0') {
        return 0; // or some indication of failure
    }
    return result;
}

int main() {
    const char* testCases[] = {"123", "456", "abc", "789", "0"};
    for (int i = 0; i < 5; i++) {
        printf("Input: %s Output: %d\n", testCases[i], convertToInt(testCases[i]));
    }
    return 0;
}