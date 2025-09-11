#include <stdio.h>
#include <string.h>

void displayOnWebPage(char *input) {
    // In a real-world application, this would involve sending the input to a web page.
    printf("Displaying on web page: %s\n", input);
}

int main() {
    char userInput[100];
    printf("Please enter some input: ");
    fgets(userInput, sizeof(userInput), stdin);
    // Remove trailing newline character
    userInput[strcspn(userInput, "\n")] = 0;
    displayOnWebPage(userInput);
    return 0;
}