#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void changeUserPassword(const char *username, const char *newPassword) {
    // Perform privileged operation
    char command[256];
    snprintf(command, sizeof(command), "echo '%s:%s' | sudo chpasswd", username, newPassword);
    int result = system(command);

    // Check if the operation was successful
    if (result == 0) {
        printf("Password changed successfully for user: %s\n", username);
    } else {
        printf("Failed to change password for user: %s\n", username);
    }

    // Drop privileges
    if (setuid(getuid()) == -1) {
        perror("Failed to drop privileges");
    }
}

int main() {
    changeUserPassword("user1", "newPassword1");
    changeUserPassword("user2", "newPassword2");
    changeUserPassword("user3", "newPassword3");
    changeUserPassword("user4", "newPassword4");
    changeUserPassword("user5", "newPassword5");
    return 0;
}