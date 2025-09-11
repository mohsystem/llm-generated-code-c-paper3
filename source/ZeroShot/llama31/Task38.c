#include <stdio.h>

void displayGreeting(const char* name) {
    printf("Hello, %s!\n", name);
}

int main() {
    char name[100];
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove the newline character
    displayGreeting(name);
    return 0;
}