
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

#define ADMIN_USER "root"
#define MAX_CMD_LENGTH 1024

static int is_privileged = 0;

void drop_privileges() {
    is_privileged = 0;
    
    // If running as root, drop to nobody
    if (geteuid() == 0) {
        struct passwd *nobody = getpwnam("nobody");
        if (nobody != NULL) {
            if (setgid(nobody->pw_gid) != 0) {
                fprintf(stderr, "Failed to drop group privileges\\n");
            }
            if (setuid(nobody->pw_uid) != 0) {
                fprintf(stderr, "Failed to drop user privileges\\n");
            }
        }
    }
}

int change_user_password(const char *username, const char *new_password) {
    if (!is_privileged) {
        fprintf(stderr, "Error: Insufficient privileges\\n");
        return 0;
    }
    
    if (username == NULL || new_password == NULL || 
        strlen(username) == 0 || strlen(new_password) == 0) {
        return 0;
    }
    
    char cmd[MAX_CMD_LENGTH];
    int result;
    
    // Sanitize inputs to prevent command injection
    for (const char *s = username; *s; s++) {
        if (!isalnum(*s) && *s != '_' && *s != '-') {
            fprintf(stderr, "Invalid username characters\\n");
            return 0;
        }
    }
    
    for (const char *s = new_password; *s; s++) {
        if (*s == '\\'' || *s == '\\"' || *s == '\\\\' || *s == '`') {\n            fprintf(stderr, "Invalid password characters\\n");\n            return 0;\n        }\n    }\n    \n    // Construct and execute command\n    snprintf(cmd, sizeof(cmd), "echo '%s:%s' | chpasswd", \n             username, new_password);\n    \n    result = system(cmd);\n    \n    // Drop privileges immediately after operation\n    drop_privileges();\n    \n    return (result == 0);\n}\n\nint main() {\n    // Test cases\n    is_privileged = 1; // Simulate privileged access\n    \n    // Test 1: Valid change\n    printf("Test 1: %d\
", change_user_password("testuser1", "newpass123"));\n    \n    // Test 2: Empty username\n    printf("Test 2: %d\
", change_user_password("", "newpass123"));\n    \n    // Test 3: Empty password\n    printf("Test 3: %d\
", change_user_password("testuser2", ""));\n    \n    // Test 4: NULL values\n    printf("Test 4: %d\
", change_user_password(NULL, NULL));\n    \n    // Test 5: Without privileges\n    is_privileged = 0;\n    printf("Test 5: %d\
", change_user_password("testuser3", "newpass123"));
    
    return 0;
}
