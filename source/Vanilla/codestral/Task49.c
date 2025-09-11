#include <stdio.h>
#include <string.h>

// In C, there's no concept of classes or methods. We'll use a function instead.
void storeUserData(char *userData) {
    // In a real application, you would store the userData in a database here
    printf("User data received and stored: %s\n", userData);
}

int main() {
    // Test cases
    storeUserData("John Doe, johndoe@example.com");
    storeUserData("Jane Doe, janedoe@example.com");
    // Add more test cases as needed
    return 0;
}