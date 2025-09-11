
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <openssl/sha.h>

#define MAX_LOGIN_ATTEMPTS 3
#define MIN_PASSWORD_LENGTH 8
#define MAX_USERNAME_LENGTH 50
#define HASH_LENGTH SHA256_DIGEST_LENGTH * 2 + 1

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password_hash[HASH_LENGTH];
    int login_attempts;
    int is_locked;
} User;

void hash_password(const char* password, char* hash_output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash_output + (i * 2), "%02x", hash[i]);
    }
    hash_output[HASH_LENGTH-1] = '\\0';
}

void init_user(User* user, const char* username, const char* password) {
    strncpy(user->username, username, MAX_USERNAME_LENGTH-1);
    user->username[MAX_USERNAME_LENGTH-1] = '\\0';
    hash_password(password, user->password_hash);
    user->login_attempts = 0;
    user->is_locked = 0;
}

int authenticate(User* user, const char* password) {
    if(!password || strlen(password) == 0) {
        return 0;
    }
    
    if(user->is_locked) {
        printf("Account is locked. Please contact admin.\\n");
        return 0;
    }
    
    char password_hash[HASH_LENGTH];
    hash_password(password, password_hash);
    
    if(strcmp(user->password_hash, password_hash) == 0) {
        user->login_attempts = 0;
        return 1;
    } else {
        user->login_attempts++;
        if(user->login_attempts >= MAX_LOGIN_ATTEMPTS) {
            user->is_locked = 1;
            printf("Account locked due to too many failed attempts\\n");
        }
        return 0;
    }
}

int validate_password(const char* password) {
    if(!password || strlen(password) < MIN_PASSWORD_LENGTH) {
        return 0;
    }
    
    int has_upper = 0, has_lower = 0, has_digit = 0;
    
    for(int i = 0; password[i]; i++) {
        if(isupper(password[i])) has_upper = 1;
        if(islower(password[i])) has_lower = 1;
        if(isdigit(password[i])) has_digit = 1;
    }
    
    return has_upper && has_lower && has_digit;
}

int main() {
    User user;
    init_user(&user, "testUser", "SecurePass123");
    
    // Test 1: Correct password
    printf("Test 1: %d\\n", authenticate(&user, "SecurePass123"));
    
    // Test 2: Wrong password
    printf("Test 2: %d\\n", authenticate(&user, "wrongpass"));
    
    // Test 3: Password validation
    printf("Test 3: %d\\n", validate_password("Weak"));
    
    // Test 4: Strong password validation
    printf("Test 4: %d\\n", validate_password("StrongPass123"));
    
    // Test 5: Account lockout
    authenticate(&user, "wrong1");
    authenticate(&user, "wrong2");
    authenticate(&user, "wrong3");
    printf("Test 5: %d\\n", authenticate(&user, "SecurePass123"));
    
    return 0;
}
