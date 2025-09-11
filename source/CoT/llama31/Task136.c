#include <stdio.h>
#include <string.h>

int authenticateUser(const char* username, const char* password, const char* validUsername, const char* validPassword) {
    return strcmp(username, validUsername) == 0 && strcmp(password, validPassword) == 0;
}

int main() {
    const char* validUsername = "user123";
    const char* validPassword = "password";

    // Test cases
    printf("%s\n", authenticateUser("user123", "password", validUsername, validPassword) ? "Authentication Successful" : "Authentication Failed");
    printf("%s\n", authenticateUser("user123", "wrongpassword", validUsername, validPassword) ? "Authentication Successful" : "Authentication Failed");
    printf("%s\n", authenticateUser("wronguser", "password", validUsername, validPassword) ? "Authentication Successful" : "Authentication Failed");
    printf("%s\n", authenticateUser("wronguser", "wrongpassword", validUsername, validPassword) ? "Authentication Successful" : "Authentication Failed");
    printf("%s\n", authenticateUser("user123", "password", validUsername, validPassword) ? "Authentication Successful" : "Authentication Failed");

    return 0;
}