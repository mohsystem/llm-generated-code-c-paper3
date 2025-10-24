#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <regex.h>

#include <openssl/evp.h>
#include <openssl/rand.h>

#define SALT_LENGTH_BYTES 16
#define HASH_LENGTH_BYTES 32 
#define PBKDF2_ITERATIONS 210000
#define MAX_NAME_LEN 50
#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 100


typedef struct User {
    char name[MAX_NAME_LEN + 1];
    char email[MAX_EMAIL_LEN + 1];
    unsigned char password_hash[HASH_LENGTH_BYTES];
    unsigned char salt[SALT_LENGTH_BYTES];
    struct User* next;
} User;

// In-memory "database" as a linked list
User* user_database_head = NULL;

void cleanup_database() {
    User* current = user_database_head;
    while (current != NULL) {
        User* next = current->next;
        free(current);
        current = next;
    }
}

bool is_valid_name(const char* name) {
    if (name == NULL) return false;
    size_t len = strlen(name);
    return len >= 2 && len <= MAX_NAME_LEN;
}

bool is_valid_email(const char* email) {
    if (email == NULL || strlen(email) > MAX_EMAIL_LEN) return false;
    regex_t regex;
    int reti;
    bool result = false;

    reti = regcomp(&regex, "^[a-zA-Z0-9_!#$%&'*+/=?`{|}~^.-]+@[a-zA-Z0-9.-]+$", REG_EXTENDED | REG_NOSUB);
    if (reti) {
        fprintf(stderr, "Could not compile email regex\n");
        return false;
    }
    
    if (regexec(&regex, email, 0, NULL, 0) == 0) {
        result = true;
    }

    regfree(&regex);
    return result;
}

bool is_valid_password(const char* password) {
    if (password == NULL || strlen(password) < 12 || strlen(password) > MAX_PASSWORD_LEN) return false;
    regex_t regex;
    bool result = false;
    
    const char* pattern = "^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[@$!%*?&]).{12,}$";

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile password regex\n");
        return false;
    }

    if (regexec(&regex, password, 0, NULL, 0) == 0) {
        result = true;
    }

    regfree(&regex);
    return result;
}


bool hash_password(const char* password, unsigned char* hash, unsigned char* salt) {
    if (RAND_bytes(salt, SALT_LENGTH_BYTES) != 1) {
        fprintf(stderr, "Failed to generate secure salt.\n");
        return false;
    }

    int result = PKCS5_PBKDF2_HMAC(
        password,
        (int)strlen(password),
        salt,
        SALT_LENGTH_BYTES,
        PBKDF2_ITERATIONS,
        EVP_sha256(),
        HASH_LENGTH_BYTES,
        hash
    );

    return result == 1;
}

bool register_user(const char* name, const char* email, const char* password) {
    if (!is_valid_name(name)) {
        fprintf(stderr, "Registration failed: Invalid name.\n");
        return false;
    }
    if (!is_valid_email(email)) {
        fprintf(stderr, "Registration failed: Invalid email format.\n");
        return false;
    }
    if (!is_valid_password(password)) {
        fprintf(stderr, "Registration failed: Password does not meet policy requirements (min 12 chars, 1 uppercase, 1 lowercase, 1 digit, 1 special char).\n");
        return false;
    }

    for (User* current = user_database_head; current != NULL; current = current->next) {
        if (strncmp(current->email, email, MAX_EMAIL_LEN) == 0) {
            fprintf(stderr, "Registration failed: Email already exists.\n");
            return false;
        }
    }

    User* new_user = (User*)malloc(sizeof(User));
    if (new_user == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return false;
    }

    if (!hash_password(password, new_user->password_hash, new_user->salt)) {
        fprintf(stderr, "Critical error during password hashing.\n");
        free(new_user);
        return false;
    }

    strncpy(new_user->name, name, MAX_NAME_LEN);
    new_user->name[MAX_NAME_LEN] = '\0';
    strncpy(new_user->email, email, MAX_EMAIL_LEN);
    new_user->email[MAX_EMAIL_LEN] = '\0';
    
    new_user->next = user_database_head;
    user_database_head = new_user;

    printf("User '%s' registered successfully.\n", name);
    return true;
}

bool is_user_registered(const char* email) {
    for (User* current = user_database_head; current != NULL; current = current->next) {
        if (strncmp(current->email, email, MAX_EMAIL_LEN) == 0) {
            return true;
        }
    }
    return false;
}

int main(void) {
    atexit(cleanup_database);

    printf("--- Test Case 1: Successful Registration ---\n");
    register_user("Alice Smith", "alice.smith@example.com", "Password@12345");
    
    printf("\n--- Test Case 2: Duplicate Email ---\n");
    register_user("Alice Jones", "alice.smith@example.com", "AnotherP@ss123");
    
    printf("\n--- Test Case 3: Weak Password (too short) ---\n");
    register_user("Bob Johnson", "bob.j@example.com", "Weak@1");
    
    printf("\n--- Test Case 4: Invalid Email ---\n");
    register_user("Carol White", "carol.white@", "StrongPass!123");
    
    printf("\n--- Test Case 5: Successful Registration 2 ---\n");
    register_user("David Green", "david.green@example.com", "SecurePassword#2024");

    // Verify database state
    printf("\n--- Verifying Database State ---\n");
    printf("Is alice.smith@example.com registered? %s\n", is_user_registered("alice.smith@example.com") ? "Yes" : "No");
    printf("Is david.green@example.com registered? %s\n", is_user_registered("david.green@example.com") ? "Yes" : "No");
    printf("Is bob.j@example.com registered? %s\n", is_user_registered("bob.j@example.com") ? "Yes" : "No");

    return 0;
}