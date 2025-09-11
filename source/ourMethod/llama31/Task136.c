#include <stdio.h>
#include <string.h>

int authenticate(const char* username, const char* password, const char* validUsername, const char* validPassword) {
    return strcmp(username, validUsername) == 0 && strcmp(password, validPassword) == 0;
}

int main() {
    const char* validUsername = "user";
    const char* validPassword = "user";

    // Test cases
    const char* usernames[] = {"user", "invalid", "user", "user"};
    const char* passwords[] = {"user", "user", "invalid", "user"};

    for (int i = 0; i < 4; i++) {
        if (authenticate(usernames[i], passwords[i], validUsername, validPassword)) {
            printf("Authentication Successful\n");
        } else {
            printf("Authentication Failed\n");
        }
    }

    return 0;
}