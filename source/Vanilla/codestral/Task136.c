#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool authenticate(const char* username, const char* password) {
    // Replace these with your secure method of user verification
    const char* correctUsername = "user";
    const char* correctPassword = "password";

    return strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0;
}

int main() {
    printf("%d\n", authenticate("user", "password"));  // 1 (true)
    printf("%d\n", authenticate("user", "wrong"));  // 0 (false)
    printf("%d\n", authenticate("wrong", "password"));  // 0 (false)
    printf("%d\n", authenticate("wrong", "wrong"));  // 0 (false)

    return 0;
}