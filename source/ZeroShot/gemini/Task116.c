#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>


int change_password(const char *username, const char *new_password) {
    // Construct the command using snprintf to prevent buffer overflows
    char command[256]; // Make sure this buffer is large enough
    snprintf(command, sizeof(command), "echo -e '%s\\n%s' | passwd %s", new_password, new_password, username);

    // Execute the command
    int result = system(command);

    if (result == 0) {
        printf("Password changed successfully (Privileged operation completed).\n");
    } else {
        fprintf(stderr, "Error changing password. Return code: %d\n", result);
    }
    return result;
}



int main() {

    // Test cases (replace with actual user input)
    change_password("testuser", "newpass1"); // Example, replace with actual username and new password
    change_password("testuser", "newpass2"); // Example, replace with actual username and new password
    change_password("testuser", "newpass3"); // Example, replace with actual username and new password
    change_password("testuser", "newpass4"); // Example, replace with actual username and new password
    change_password("testuser", "newpass5"); // Example, replace with actual username and new password


    return 0;
}