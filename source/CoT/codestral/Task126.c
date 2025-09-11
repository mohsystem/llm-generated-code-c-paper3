// C code
#include <stdio.h>
#include <string.h>

void redirectUser(char input[]) {
    if (strcmp(input, "home") == 0) {
        printf("Redirecting to home page...\n");
        // Add your redirecting logic here
    } else if (strcmp(input, "about") == 0) {
        printf("Redirecting to about page...\n");
        // Add your redirecting logic here
    } else if (strcmp(input, "contact") == 0) {
        printf("Redirecting to contact page...\n");
        // Add your redirecting logic here
    } else {
        printf("Invalid input. Redirecting to default page...\n");
        // Add your redirecting logic here
    }
}

int main() {
    char userInput[20];
    printf("Enter your input: ");
    scanf("%s", userInput);
    redirectUser(userInput);
    return 0;
}