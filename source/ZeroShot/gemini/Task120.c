#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// A simple HTML escaping function (similar to C++ version)
char* escapeHtml(const char* input) {
    if (!input) return ""; // Handle null input


    char* safeInput = malloc(strlen(input) * 6 + 1); // Allocate enough space (worst case)
    if (!safeInput) return ""; // Handle allocation failure

    char* dest = safeInput;
    while (*input) {
        switch (*input) {
            case '<': strcpy(dest, "&lt;"); dest += 4; break;
            case '>': strcpy(dest, "&gt;"); dest += 4; break;
            case '&': strcpy(dest, "&amp;"); dest += 5; break;
            case '"': strcpy(dest, "&quot;"); dest += 6; break;
            case '\'': strcpy(dest, "&#x27;"); dest += 6; break;
            case '/': strcpy(dest, "&#x2F;"); dest += 6; break;
            default: *dest++ = *input;
        }
        input++;
    }
    *dest = '\0';
    return safeInput;
}

int main() {
    char* testCases[] = {
        "<script>alert('XSS')</script>",
        "<b>bold text</b>",
        "plain text",
        "1 < 2 > 3",
        NULL // Testing null input
    };

    for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); i++) {
        char* testCase = testCases[i];
        printf("Input: %s\n", testCase ? testCase : "NULL");
        char *escaped = escapeHtml(testCase);
        printf("Escaped Output: %s\n", escaped);

        free(escaped); // Free the allocated memory
        printf("---\n");
    }

    return 0;
}