#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool authenticateUser(const char *username, const char *password) {
    // In a real application, you would typically query a database or external service
    // to verify the username and password.
    // For this example, we'll use hardcoded credentials.
    if (strcmp(username, "user123") == 0 && strcmp(password, "password456") == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    printf("%d\n", authenticateUser("user123", "password456")); // true, prints 1
    printf("%d\n", authenticateUser("user123", "wrongpassword")); // false, prints 0
    printf("%d\n", authenticateUser("wronguser", "password456")); // false, prints 0
    printf("%d\n", authenticateUser("", "")); // false, prints 0
    printf("%d\n", authenticateUser("user123 ", "password456")); // false, prints 0
    return 0;
}