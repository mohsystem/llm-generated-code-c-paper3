#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void changePassword(const char* username, const char* newPassword) {
#ifdef _WIN32
    char command[256];
    snprintf(command, sizeof(command), "net user %s %s", username, newPassword);
    int result = system(command);
    if (result == 0) {
        printf("Password changed successfully.\n");
    } else {
        printf("Failed to change password.\n");
    }
#else
    printf("This operation is only supported on Windows systems.\n");
#endif
}

int main() {
    // This example will run only on Windows
    char username[50];
    char newPassword[50];
    for (int i = 0; i < 5; ++i) {
        printf("Enter username: ");
        scanf("%49s", username);
        printf("Enter new password: ");
        scanf("%49s", newPassword);
        changePassword(username, newPassword);
    }
    return 0;
}