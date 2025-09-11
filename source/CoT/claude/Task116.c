
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Function to check if running with privileged access
int is_privileged_user() {
    #ifdef _WIN32
        BOOL is_elevated = FALSE;
        HANDLE h_token = NULL;
        if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &h_token)) {
            TOKEN_ELEVATION elevation;
            DWORD size;
            if (GetTokenInformation(h_token, TokenElevation, &elevation, sizeof(elevation), &size)) {
                is_elevated = elevation.TokenIsElevated;
            }
            CloseHandle(h_token);
        }
        return is_elevated;
    #else
        return (geteuid() == 0);
    #endif
}

// Function to drop privileges
int drop_privileges() {
    #ifdef _WIN32
        system("runas /user:standard_user cmd.exe");
        return 1;
    #else
        const char* username = "nobody";
        struct passwd* pw = getpwnam(username);
        
        if (pw == NULL) {
            fprintf(stderr, "Failed to get user info for %s\\n", username);
            return 0;
        }

        if (setgroups(0, NULL) != 0) {
            fprintf(stderr, "Failed to clear supplementary groups\\n");
            return 0;
        }

        if (setgid(pw->pw_gid) != 0) {
            fprintf(stderr, "Failed to set GID\\n");
            return 0;
        }

        if (setuid(pw->pw_uid) != 0) {
            fprintf(stderr, "Failed to set UID\\n");
            return 0;
        }

        return 1;
    #endif
}

// Function to change user password
int change_user_password(const char* username, const char* new_password) {
    if (!is_privileged_user()) {
        fprintf(stderr, "Error: Requires privileged access\\n");
        return 0;
    }

    int success = 0;
    char command[256];

    #ifdef _WIN32
        snprintf(command, sizeof(command), "net user %s %s", username, new_password);
    #else
        snprintf(command, sizeof(command), "echo '%s:%s' | chpasswd", username, new_password);
    #endif

    if (system(command) == 0) {
        success = 1;
    }

    // Clear sensitive data from memory
    memset(command, 0, sizeof(command));

    // Drop privileges after operation
    if (!drop_privileges()) {
        fprintf(stderr, "Warning: Failed to drop privileges\\n");
    }

    return success;
}

int main() {
    // Test cases
    const char* test_users[] = {"user1", "testuser", "admin", "guest", "system"};
    const char* test_passwords[] = {"newpass123", "securepass456", "adminpass789", "guestpass321", "syspass987"};
    int num_tests = 5;

    for (int i = 0; i < num_tests; i++) {
        printf("Attempting to change password for user: %s\\n", test_users[i]);
        int success = change_user_password(test_users[i], test_passwords[i]);
        printf("Password change %s\\n", success ? "successful" : "failed");
        printf("------------------------\\n");
    }

    return 0;
}
