#include <stdio.h>
#include <string.h>

char* displayInputOnWebPage(const char* input) {
    char* html = (char*) malloc(strlen(input) + 100); // Allocate enough memory
    sprintf(html, "<html><head><title>User Input</title></head><body><h1>User Input:</h1><p>%s</p></body></html>", input);
    return html;
}

int main() {
    char* testCases[] = {"Hello, world!", "Test case 1", "Test case 2", "Test case 3", "Test case 4"};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        char *result = displayInputOnWebPage(testCases[i]);
        printf("%s\n", result);
        free(result); // Free allocated memory
    }

    return 0;
}