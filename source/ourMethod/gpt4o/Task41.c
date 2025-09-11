#include <stdio.h>
#include <string.h>
#include <ctype.h>

void processInput(const char* input, char* output, size_t maxLen) {
    const char* start = input;
    const char* end = input + strlen(input) - 1;

    while (isspace((unsigned char)*start)) start++;
    while (end > start && isspace((unsigned char)*end)) end--;

    size_t len = end - start + 1;
    if (len < maxLen) {
        strncpy(output, start, len);
        output[len] = '\0';
    } else {
        strncpy(output, start, maxLen - 1);
        output[maxLen - 1] = '\0';
    }
}

int main() {
    char output[100];
    const char* testCases[] = {
        "  Hello World  ",
        "C Programming",
        "   Secure Code   ",
        "Input   ",
        "   Test Case 5   "
    };

    for (int i = 0; i < 5; i++) {
        processInput(testCases[i], output, sizeof(output));
        printf("Processed: '%s'\n", output);
    }

    return 0;
}