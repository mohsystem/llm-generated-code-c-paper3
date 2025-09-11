
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <regex.h>
#include <stdbool.h>
#include <errno.h>

#define MAX_USERNAME_LEN 21
#define MAX_PASSWORD_LEN 21
#define COMMAND_BUFFER_SIZE 256

typedef struct {
    regex_t username_regex;
    regex_t password_regex;
} Validator;

static Validator* initialize_validator() {
    Validator* v = malloc(sizeof(Validator));
    if (!v) return NULL;
    
    if (regcomp(&v->username_regex, "^[a-zA-Z0-9_-]{3,20}$", REG_EXTENDED) != 0) {
        free(v);
        return NULL;
    }
    
    if (regcomp(&v->password_regex, "^[a-zA-Z0-9@#$%^&+=]{8,20}$", REG_EXTENDED) != 0) {
        regfree(&v->username_regex);
        free(v);
        return NULL;
    }
    
    return v;
}

static void cleanup_validator(Validator* v) {
    if (v) {
        regfree(&v->username_regex);
        regfree(&v->password_regex);
        free(v);
    }
}

static bool validate_input(Validator* v, const char* username, const char* password) {
    if (!username || !password || !v) return false;
    
    return (regexec(&v->username_regex, username, 0, NULL, 0) == 0 &&
            regexec(&v->password_regex, password, 0, NULL, 0) == 0);
}

static bool is_root() {
    return geteuid() == 0;
}

static void drop_privileges() {
    struct passwd* nobody = getpwnam("nobody");
    if (nobody) {
        if (setuid(nobody->pw_uid) != 0) {
            fprintf(stderr, "Error dropping privileges: %s\\n", strerror(errno));
        }
    }
}

bool change_password(const char* username, const char* new_password) {
    if (!username || !new_password) {
        return false;
    }
    
    Validator* validator = initialize_validator();
    if (!validator) {
        fprintf(stderr, "Failed to initialize validator\\n");
        return false;
    }
    
    if (!validate_input(validator, username, new_password)) {
        cleanup_validator(validator);
        return false;
    }
    
    if (!is_root()) {
        fprintf(stderr, "Error: Root privileges required\\n");
        cleanup_validator(validator);
        return false;
    }
    
    char cmd[COMMAND_BUFFER_SIZE];
    snprintf(cmd, sizeof(cmd), "/usr/bin/passwd %s", username);
    
    FILE* process = popen(cmd, "w");
    if (!process) {
        fprintf(stderr, "Failed to execute passwd command\\n");
        cleanup_validator(validator);
        return false;
    }
    
    fprintf(process, "%s\\n%s\\n", new_password, new_password);
    int result = pclose(process);
    
    // Drop privileges
    drop_privileges();
    
    cleanup_validator(validator);
    return result == 0;
}

int main() {
    // Test cases
    struct {
        const char* username;
        const char* password;
    } test_cases[] = {
        {"user1", "Password123"},
        {"admin", "Admin@123"},
        {"test_user", "Test#1234"},
        {"root", "Root$1234"},
        {"system", "System@123"}
    };
    
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        printf("\\nTesting with username: %s, password: %s\\n", 
               test_cases[i].username, test_cases[i].password);
        bool result = change_password(test_cases[i].username, test_cases[i].password);
        printf("Password change %s\\n", result ? "successful" : "failed");
    }
    
    return 0;
}
