
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openssl/sha.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 32
#define MAX_PASSWORD_LENGTH 64
#define MIN_PASSWORD_LENGTH 8

typedef enum {
    ROLE_ADMIN,
    ROLE_MANAGER,
    ROLE_USER
} Role;

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
    Role role;
    bool is_active;
} User;

typedef struct {
    User users[MAX_USERS];
    int user_count;
} Task138;

void init_task138(Task138* manager) {
    manager->user_count = 0;
}

void hash_password(const char* password, unsigned char* hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

bool create_user(Task138* manager, const char* username, const char* password) {
    if (!username || !password || strlen(username) == 0 || 
        strlen(password) < MIN_PASSWORD_LENGTH || 
        manager->user_count >= MAX_USERS) {
        return false;
    }
    
    // Check if username already exists
    for (int i = 0; i < manager->user_count; i++) {
        if (strcmp(manager->users[i].username, username) == 0) {
            return false;
        }
    }
    
    User* new_user = &manager->users[manager->user_count];
    strncpy(new_user->username, username, MAX_USERNAME_LENGTH - 1);
    new_user->username[MAX_USERNAME_LENGTH - 1] = '\\0';
    hash_password(password, new_user->password_hash);
    new_user->role = ROLE_USER;
    new_user->is_active = true;
    
    manager->user_count++;
    return true;
}

bool authenticate(Task138* manager, const char* username, const char* password) {
    if (!username || !password) return false;
    
    unsigned char test_hash[SHA256_DIGEST_LENGTH];
    hash_password(password, test_hash);
    
    for (int i = 0; i < manager->user_count; i++) {
        if (strcmp(manager->users[i].username, username) == 0 && 
            manager->users[i].is_active) {
            return memcmp(manager->users[i].password_hash, test_hash, 
                         SHA256_DIGEST_LENGTH) == 0;
        }
    }
    return false;
}

bool check_permission(Task138* manager, const char* username, const char* permission) {
    if (!username || !permission) return false;
    
    for (int i = 0; i < manager->user_count; i++) {
        if (strcmp(manager->users[i].username, username) == 0 && 
            manager->users[i].is_active) {
            switch (manager->users[i].role) {
                case ROLE_ADMIN:
                    return true;
                case ROLE_MANAGER:
                    return strcmp(permission, "MANAGE_USERS") != 0;
                case ROLE_USER:
                    return strcmp(permission, "READ") == 0 || 
                           strcmp(permission, "WRITE") == 0;
                default:
                    return false;
            }
        }
    }
    return false;
}

bool set_role(Task138* manager, const char* admin_username, 
              const char* target_username, Role new_role) {
    if (!admin_username || !target_username) return false;
    
    int admin_idx = -1, target_idx = -1;
    
    for (int i = 0; i < manager->user_count; i++) {
        if (strcmp(manager->users[i].username, admin_username) == 0) {
            admin_idx = i;
        }
        if (strcmp(manager->users[i].username, target_username) == 0) {
            target_idx = i;
        }
    }
    
    if (admin_idx == -1 || target_idx == -1 || 
        !manager->users[admin_idx].is_active || 
        !manager->users[target_idx].is_active || 
        manager->users[admin_idx].role != ROLE_ADMIN) {
        return false;
    }', type='text')