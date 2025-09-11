#include <stdio.h>
#include <stdlib.h>

void change_password(const char *username, const char *new_password) {
    // Elevate privileges to perform the operation
    // ...

    // Perform the password change
    char command[100];
    snprintf(command, sizeof(command), "echo '%s' | passwd --stdin %s", new_password, username);
    system(command);

    // Drop privileges
    // ...
}

int main() {
    const char *username = "user";
    const char *new_password = "newPassword";
    change_password(username, new_password);
    return 0;
}