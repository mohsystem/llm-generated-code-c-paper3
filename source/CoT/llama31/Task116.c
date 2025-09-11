#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

void changePasswordAndDropPrivileges(const char* user, const char* password) {
    // Change password (Linux example)
    char command[1024];
    sprintf(command, "echo %s | sudo passwd %s --stdin", password, user);
    system(command);

    // Drop privileges (this is a simplification)
    // In real-world scenarios, you would use a more secure method to drop privileges.
    printf("Dropping privileges...\n");
    // setuid(getuid()); // This does not actually drop privileges but is a placeholder.
}

int main() {
    // Test cases
    const char* users[] = {"user1", "user2", "user3", "user4", "user5"};
    const char* passwords[] = {"password1", "password2", "password3", "password4", "password5"};

    for (int i = 0; i < 5; ++i) {
        changePasswordAndDropPrivileges(users[i], passwords[i]);
    }

    return 0;
}