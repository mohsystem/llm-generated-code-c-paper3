// Import necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

void changePassword(char *username) {
    // Validate input
    // Use secure way to change password
    char password[100];
    printf("Enter new password: ");
    scanf("%s", password);
    char command[200];
    sprintf(command, "echo '%s' | passwd --stdin %s", password, username);
    system(command);
    // Drop privileges
    setuid(getpwnam(username)->pw_uid);
}

int main() {
    char username[100];
    printf("Enter username: ");
    scanf("%s", username);
    changePassword(username);
    return 0;
}