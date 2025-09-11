#include <stdio.h>
#include <string.h>

// Fictional function to generate JWT token
char* generate_jwt(const char* username, const char* secret, int expire_time) {
    // This is a placeholder and does not actually generate a JWT token.
    // In a real application, you would need to implement Base64 encoding and signing.
    static char token[1024];
    sprintf(token, "Placeholder token for %s", username);
    return token;
}

int main() {
    const char* secret = "supersecret";
    int expire_time = 120; // 2 minutes
    const char* usernames[] = {"user1", "user2", "user3", "user4", "user5"};
    for (int i = 0; i < 5; i++) {
        char* token = generate_jwt(usernames[i], secret, expire_time);
        printf("Token for %s: %s\n", usernames[i], token);
    }
    return 0;
}