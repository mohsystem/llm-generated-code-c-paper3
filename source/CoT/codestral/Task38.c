#include <stdio.h>

int main() {
    char userInput[100];
    printf("Enter your input: ");
    fgets(userInput, sizeof(userInput), stdin);
    printf("You entered: %s", userInput);
    return 0;
}