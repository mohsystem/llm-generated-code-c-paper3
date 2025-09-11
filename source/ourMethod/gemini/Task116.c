#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/wait.h>


int changePassword(const char *username, const char *newPassword) {
    // Check if user exists
    struct passwd* pw = getpwnam(username);
    if (pw == nullptr) {
        fprintf(stderr, "User %s does not exist.\n", username);
        return 1;
    }

    char *args[] = {"/usr/bin/passwd", (char*)username, NULL}; // Explicit path

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execv(args[0], args);
        perror("execv failed"); 
        _exit(1);
    } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            int exitCode = WEXITSTATUS(status);
            if (exitCode == 0) {
                printf("Password for %s changed successfully.\n", username);
            } else {
                fprintf(stderr, "Password change failed. Exit code: %d\n", exitCode);
            }
           return exitCode;
        } else {
           fprintf(stderr, "Password change failed.\n");
           return 1;
        }
    } else {
        perror("fork failed");
        return 1;
    }
    return 0;
}

int main() {
    // Test cases
    changePassword("testuser1", "new_password1");
    changePassword("testuser2", "new_password2");
    changePassword("testuser3", "new_password3");
    changePassword("testuser4", "new_password4");
    changePassword("testuser5", "new_password5");

    printf("All test cases completed.\n");

    return 0;
}