#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void changeUserPassword(const char* username, const char* newPassword) {
    // Using sudo command to change the password, requires sudo privileges
    char command[256];
    snprintf(command, sizeof(command), "echo -e \"%s\\n%s\" | sudo passwd %s", newPassword, newPassword, username);
    system(command);

    // Drop privileges by switching to a non-privileged user, typically requires system configuration
    setuid(getuid());
}

int main() {
    // Test cases
    changeUserPassword("user1", "newPassword1");
    changeUserPassword("user2", "newPassword2");
    changeUserPassword("user3", "newPassword3");
    changeUserPassword("user4", "newPassword4");
    changeUserPassword("user5", "newPassword5");

    return 0;
}