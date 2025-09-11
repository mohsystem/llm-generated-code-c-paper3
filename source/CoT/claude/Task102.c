
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>
#include <regex.h>

#define PASSWORD_PATTERN "^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[@#$%^&+=])(?=\\\\S+$).{8,}$"
#define MAX_PASSWORD_LENGTH 256

bool validate_password(const char* password) {
    regex_t regex;
    int ret;
    
    if (regcomp(&regex, PASSWORD_PATTERN, REG_EXTENDED) != 0) {
        return false;
    }
    
    ret = regexec(&regex, password, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

void hash_password(const char* password, char* hashed, size_t hashed_size) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        snprintf(&hashed[i*2], hashed_size - (i*2), "%02x", hash[i]);
    }
}

bool update_password(const char* username, const char* new_password) {
    if (!username || !new_password || strlen(username) == 0) {
        return false;
    }
    
    // Validate password strength
    if (!validate_password(new_password)) {
        return false;
    }
    
    // Hash password
    char hashed_password[SHA256_DIGEST_LENGTH*2 + 1] = {0};
    hash_password(new_password, hashed_password, sizeof(hashed_password));
    
    // Database connection
    MYSQL* conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "username", "password", 
                          "database", 0, NULL, 0)) {
        return false;
    }
    
    // Prepare statement
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    const char* sql = "UPDATE users SET password = ? WHERE username = ?";
    
    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        mysql_close(conn);
        return false;
    }
    
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));
    
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)hashed_password;
    bind[0].buffer_length = strlen(hashed_password);
    
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char*)username;
    bind[1].buffer_length = strlen(username);
    
    if (mysql_stmt_bind_param(stmt, bind)) {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return false;
    }
    
    bool success = !mysql_stmt_execute(stmt);
    
    mysql_stmt_close(stmt);
    mysql_close(conn);
    
    return success;
}

int main() {
    // Test cases
    printf("Test 1: %d\\n", update_password("john_doe", "Password123@")); // Valid
    printf("Test 2: %d\\n", update_password("jane_doe", "weak")); // Invalid - too short
    printf("Test 3: %d\\n", update_password("", "Password123@")); // Invalid - empty username
    printf("Test 4: %d\\n", update_password("bob", "NoSpecialChar1")); // Invalid - no special char
    printf("Test 5: %d\\n", update_password("alice", "Pass word@1")); // Invalid - contains space
    
    return 0;
}
