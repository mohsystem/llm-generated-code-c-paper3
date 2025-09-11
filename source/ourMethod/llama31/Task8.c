#include <stdio.h>
#include <string.h>

char findMissingLetter(const char** chars, int length) {
    for (int i = 0; i < length - 1; ++i) {
        if (chars[i + 1][0] - chars[i][0] > 1) {
            return (char)(chars[i][0] + 1);
        }
    }
    return '\0'; // Return a null character if no missing letter is found
}

int main() {
    const char* testCases[][5] = {
        {"a", "b", "c", "d", "f"},
        {"O", "Q", "R", "S"},
        {"a", "b", "d", "e"},
        {"A", "B", "D", "E"},
        {"p", "r", "s", "t"}
    };

    int testCaseLengths[] = {5, 4, 4, 4, 4};

    for (int i = 0; i < 5; ++i) {
        char missingLetter = findMissingLetter(testCases[i], testCaseLengths[i]);
        if (missingLetter != '\0') {
            printf("Missing letter in the array: %c\n", missingLetter);
        } else {
            printf("No missing letter found.\n");
        }
    }

    return 0;
}