
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

#define MAX_LOGIN_ATTEMPTS 3
#define MIN_PASSWORD_LENGTH 8
#define SALT_LENGTH 16
#define HASH_LENGTH 32
#define MAX_USERNAME 64
#define MAX_PASSWORD 64

typedef struct {
    char username[MAX_USERNAME];
    unsigned char password_hash[HASH_LENGTH];
    unsigned char salt[SALT_LENGTH];
    int login_attempts;
    int is_locked;
} User;

void generate_salt(unsigned char* salt) {
    srand(time(NULL));
    for(int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = rand() % 256;
    }
}

void hash_password(const char* password, const unsigned char* salt, unsigned char* hash) {
    PKCS5_PBKDF2_HMAC(password, strlen(password),
                      salt, SALT_LENGTH,
                      10000, // iterations
                      EVP_sha256(),
                      HASH_LENGTH,
                      hash);
}

int authenticate(User* user, const char* password) {
    if(user->is_locked) {
        printf("Account is locked. Please contact administrator.\\n");
        return 0;
    }
    
    unsigned char hash[HASH_LENGTH];
    hash_password(password, user->salt, hash);
    
    if(memcmp(hash, user->password_hash, HASH_LENGTH) != 0) {
        user->login_attempts++;
        if(user->login_attempts >= MAX_LOGIN_ATTEMPTS) {
            user->is_locked = 1;
            printf("Account locked due to too many failed attempts\\n");
        }
        return 0;
    }
    
    user->login_attempts = 0;
    return 1;
}

void init_user(User* user, const char* username, const char* password) {
    strncpy(user->username, username, MAX_USERNAME - 1);
    user->username[MAX_USERNAME - 1] = '\\0';
    
    generate_salt(user->salt);
    hash_password(password, user->salt, user->password_hash);
    
    user->login_attempts = 0;
    user->is_locked = 0;
}

int main() {
    const char* usernames[] = {"user1", "user2", "user3", "user4", "user5"};
    const char* passwords[] = {"Password123!", "weak", "TestPass456$", "Pass789#", "ShortPw"};
    const int num_users = 5;
    
    for(int i = 0; i < num_users; i++) {
        if(strlen(passwords[i]) < MIN_PASSWORD_LENGTH) {
            printf("Password too short for %s\\n", usernames[i]);
            continue;
        }
        
        User user;
        init_user(&user, usernames[i], passwords[i]);
        
        printf("\\nTesting %s\\n", usernames[i]);
        printf("Valid password: %d\\n", authenticate(&user, passwords[i]));
        
        printf("Invalid password: %d\\n", authenticate(&user, "wrongpass"));
        
        for(int j = 0; j < MAX_LOGIN_ATTEMPTS; j++) {
            authenticate(&user, "wrongpass");
        }
        
        printf("After lockout: %d\\n", authenticate(&user, passwords[i]));
    }
    
    return 0;
}
