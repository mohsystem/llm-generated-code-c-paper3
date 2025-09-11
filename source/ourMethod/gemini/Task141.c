#include <stdio.h>
#include <string.h>

char* reverseString(char* input) {
    int len = strlen(input);
    char temp;
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        temp = input[i];
        input[i] = input[j];
        input[j] = temp;
    }
    return input;
}

int main() {
    char* testCases[] = {"hello", "world", "12345", "racecar", ""};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        char input[100]; // Adjust size as needed
        strcpy(input, testCases[i]);
        char* reversed = reverseString(input);
        printf("Input: %s, Reversed: %s\n", testCases[i], reversed);
    }
    return 0;
}