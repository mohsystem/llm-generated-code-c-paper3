#include <stdio.h>
#include <string.h>

void displayUserInput(const char* input) {
    printf("<b>%s</b>\n", input);
}

int main() {
    char userInput[100];
    for (int i = 0; i < 5; ++i) {
        printf("Enter your name: ");
        fgets(userInput, sizeof(userInput), stdin);
        userInput[strcspn(userInput, "\n")] = 0; // Remove the newline character
        displayUserInput(userInput);
    }
    return 0;
}