// C code block
#include <stdio.h>

void displayUserInput(const char* userInput) {
    printf("<html><body>\n");
    printf("<h2>User Input:</h2>\n");
    printf("<p>%s</p>\n", userInput);
    printf("</body></html>\n");
}

int main() {
    // Test cases
    displayUserInput("Test input 1");
    displayUserInput("Another input");
    displayUserInput("More test input");
    displayUserInput("Sample text");
    displayUserInput("Final test case");
    return 0;
}