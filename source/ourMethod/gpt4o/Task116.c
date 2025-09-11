#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int changePassword(const char* username, const char* newPassword) {
    if (!username || !newPassword || strlen(username) == 0 || strlen(newPassword) == 0) {
        return 0;
    }

    char command[256];
    snprintf(command, sizeof(command), "echo '%s' | sudo passwd %s --stdin", newPassword, username);
    int result = system(command);

    return (result == 0);
}

int main() {
    // Test cases
    printf("%d\n", changePassword("user1", "newPassword1")); // Test case 1
    printf("%d\n", changePassword("user2", "newPassword2")); // Test case 2
    printf("%d\n", changePassword("", "newPassword3"));      // Test case 3
    printf("%d\n", changePassword("user4", ""));             // Test case 4
    printf("%d\n", changePassword(NULL, NULL));              // Test case 5
    return 0;
}