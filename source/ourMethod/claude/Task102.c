
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <mysql/mysql.h>
#include <stdbool.h>

#define SALT_SIZE 16
#define MAX_PASSWORD_LENGTH 128

// Structure to hold hashing result
typedef struct {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned char salt[SALT_SIZE];
} HashResult;

// Function to generate random salt
static bool generateSalt(unsigned char* salt) {
    if(!RAND_bytes(salt, SALT_SIZE)) {
        return false;
    }
    return true;
}

// Function to hash password with salt
static bool hashPassword(const char* password, const unsigned char* salt, 
                        unsigned char* hash) {
    if(!password || !salt || !hash) {
        return false;
    }
    
    SHA256_CTX sha256;
    if(!SHA256_Init(&sha256)) {
        return false;
    }
    
    if(!SHA256_Update(&sha256, salt, SALT_SIZE)) {
        return false;
    }
    
    if(!SHA256_Update(&sha256, password, strlen(password))) {
        return false;
    }
    
    if(!SHA256_Final(hash, &sha256)) {
        return false;
    }
    
    return true;
}

// Convert binary to hex string
static void binToHex(const unsigned char* bin, size_t bin_len, char* hex) {
    for(size_t i = 0; i < bin_len; i++) {
        sprintf(hex + (i * 2), "%02x", bin[i]);
    }
}

// Function to update password in database
bool updatePassword(const char* username, const char* newPassword, MYSQL* conn) {
    if(!username || !newPassword || !conn || 
       strlen(username) == 0 || strlen(newPassword) == 0 ||
       strlen(newPassword) > MAX_PASSWORD_LENGTH) {
        return false;
    }
    
    HashResult result;
    char hashedPasswordHex[SHA256_DIGEST_LENGTH * 2 + 1];
    char saltHex[SALT_SIZE * 2 + 1];
    bool success = false;
    MYSQL_STMT* stmt = NULL;
    
    do {
        // Generate salt
        if(!generateSalt(result.salt)) {
            break;
        }
        
        // Hash password
        if(!hashPassword(newPassword, result.salt, result.hash)) {
            break;
        }
        
        // Convert binary values to hex strings
        binToHex(result.hash, SHA256_DIGEST_LENGTH, hashedPasswordHex);
        binToHex(result.salt, SALT_SIZE, saltHex);
        hashedPasswordHex[SHA256_DIGEST_LENGTH * 2] = '\\0';
        saltHex[SALT_SIZE * 2] = '\\0';
        
        // Prepare SQL statement
        stmt = mysql_stmt_init(conn);
        if(!stmt) {
            break;
        }
        
        const char* query = "UPDATE users SET password_hash = ?, salt = ? WHERE username = ?";
        if(mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
            break;
        }
        
        MYSQL_BIND bind[3];
        memset(bind, 0, sizeof(bind));
        
        bind[0].buffer_type = MYSQL_TYPE_STRING;
        bind[0].buffer = hashedPasswordHex;
        bind[0].buffer_length = strlen(hashedPasswordHex);
        
        bind[1].buffer_type = MYSQL_TYPE_STRING;
        bind[1].buffer = saltHex;
        bind[1].buffer_length = strlen(saltHex);
        
        bind[2].buffer_type = MYSQL_TYPE_STRING;
        bind[2].buffer = (void*)username;
        bind[2].buffer_length = strlen(username);
        
        if(mysql_stmt_bind_param(stmt, bind) != 0) {
            break;
        }
        
        if(mysql_stmt_execute(stmt) != 0) {
            break;
        }
        
        if(mysql_stmt_affected_rows(stmt) > 0) {
            success = true;
        }
        
    } while(0);
    
    if(stmt) {
        mysql_stmt_close(stmt);
    }
    
    return success;
}

int main() {
    // Configure proper DB connection in production
    MYSQL* conn = NULL;
    
    // Test case 1: Valid input
    printf("%d\\n", updatePassword("user1", "StrongPass123!", conn));
    
    // Test case 2: Empty username
    printf("%d\\n", updatePassword("", "password123", conn));
    
    // Test case 3: Empty password
    printf("%d\\n", updatePassword("user2", "", conn));
    
    // Test case 4: Very long password
    char longPass[1000];
    memset(longPass, 'a', 999);
    longPass[999] = '\\0';
    printf("%d\\n", updatePassword("user3", longPass, conn));
    
    // Test case 5: Special characters
    printf', type='text')