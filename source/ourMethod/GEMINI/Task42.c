#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>
#include <openssl/err.h>

#define MAX_USERS 10
#define USERNAME_MAX_LEN 50
#define SALT_BYTES 16
#define KEY_BYTES 32 // 256 bits
#define ITERATIONS 210000

typedef struct {
    char username[USERNAME_MAX_LEN];
    unsigned char salt[SALT_BYTES];
    unsigned char hashedPassword[KEY_BYTES];
    bool in_use;
} UserData;

// In a real application, this would be a database.
// Using a simple global array for this example.
static UserData g_user_store[MAX_USERS];
static int g_user_count = 0;

void handle_openssl_errors(void) {
    ERR_print_errors_fp(stderr);
}

bool hash_password(const char* password, const unsigned char* salt, unsigned char* hash_out) {
    int result = PKCS5_PBKDF2_HMAC(
        password,
        strlen(password),
        salt,
        SALT_BYTES,
        ITERATIONS,
        EVP_sha256(),
        KEY_BYTES,
        hash_out
    );

    if (result != 1) {
        handle_openssl_errors();
        return false;
    }
    return true;
}

int find_user_by_username(const char* username) {
    for (int i = 0; i < g_user_count; ++i) {
        if (g_user_store[i].in_use && strncmp(g_user_store[i].username, username, USERNAME_MAX_LEN) == 0) {
            return i;
        }
    }
    return -1; // Not found
}

bool register_user(const char* username, const char* password) {
    if (username == NULL || password == NULL || strlen(username) == 0 || strlen(password) == 0) {
        fprintf(stderr, "Error: Username and password cannot be empty.\n");
        return false;
    }
    if (strlen(username) >= USERNAME_MAX_LEN) {
        fprintf(stderr, "Error: Username too long.\n");
        return false;
    }
    if (g_user_count >= MAX_USERS) {
        fprintf(stderr, "Error: User store is full.\n");
        return false;
    }
    if (find_user_by_username(username) != -1) {
        fprintf(stderr, "Error: User '%s' already exists.\n", username);
        return false;
    }

    int user_idx = g_user_count;
    
    // Generate salt
    if (RAND_bytes(g_user_store[user_idx].salt, SALT_BYTES) != 1) {
        fprintf(stderr, "Error: Failed to generate random salt.\n");
        handle_openssl_errors();
        return false;
    }

    // Hash password
    if (!hash_password(password, g_user_store[user_idx].salt, g_user_store[user_idx].hashedPassword)) {
        return false;
    }

    // Store user
    strncpy(g_user_store[user_idx].username, username, USERNAME_MAX_LEN - 1);
    g_user_store[user_idx].username[USERNAME_MAX_LEN - 1] = '\0';
    g_user_store[user_idx].in_use = true;
    g_user_count++;
    
    return true;
}

bool login_user(const char* username, const char* password) {
    if (username == NULL || password == NULL) {
        return false;
    }

    int user_idx = find_user_by_username(username);
    if (user_idx == -1) {
        return false; // User not found
    }

    unsigned char computed_hash[KEY_BYTES];
    if (!hash_password(password, g_user_store[user_idx].salt, computed_hash)) {
        return false;
    }
    
    // Constant-time comparison
    int diff = CRYPTO_memcmp(computed_hash, g_user_store[user_idx].hashedPassword, KEY_BYTES);
    
    // Securely clear computed hash from memory
    OPENSSL_cleanse(computed_hash, KEY_BYTES);

    return diff == 0;
}

void initialize_user_store() {
    for (int i = 0; i < MAX_USERS; ++i) {
        g_user_store[i].in_use = false;
        memset(g_user_store[i].username, 0, USERNAME_MAX_LEN);
    }
}

int main(void) {
    initialize_user_store();

    // Test Case 1: Register a new user
    printf("Test 1: Register 'alice'\n");
    bool registered = register_user("alice", "Password123!");
    printf("Registration successful: %s\n", registered ? "true" : "false");
    printf("--------------------\n");

    // Test Case 2: Successful login
    printf("Test 2: Successful login for 'alice'\n");
    bool login_success = login_user("alice", "Password123!");
    printf("Login successful: %s\n", login_success ? "true" : "false");
    printf("--------------------\n");

    // Test Case 3: Failed login with wrong password
    printf("Test 3: Failed login for 'alice' (wrong password)\n");
    bool login_fail_password = login_user("alice", "WrongPassword");
    printf("Login successful: %s\n", login_fail_password ? "true" : "false");
    printf("--------------------\n");

    // Test Case 4: Failed login with non-existent user
    printf("Test 4: Failed login for non-existent user 'bob'\n");
    bool login_fail_user = login_user("bob", "SomePassword");
    printf("Login successful: %s\n", login_fail_user ? "true" : "false");
    printf("--------------------\n");

    // Test Case 5: Register a second user and login successfully
    printf("Test 5: Register 'bob' and log in\n");
    bool registered_bob = register_user("bob", "anotherSecureP@ssw0rd");
    printf("Registration of 'bob' successful: %s\n", registered_bob ? "true" : "false");
    bool login_bob_success = login_user("bob", "anotherSecureP@ssw0rd");
    printf("Login for 'bob' successful: %s\n", login_bob_success ? "true" : "false");
    printf("--------------------\n");

    return 0;
}