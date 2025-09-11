
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <mysql/mysql.h>
#include <stdbool.h>

#define MAX_PASSWORD_LENGTH 256

void hash_password(const char* password, char* hashed_output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_output + (i * 2), "%02x", hash[i]);
    }
    hashed_output[SHA256_DIGEST_LENGTH * 2] = '\\0';
}

bool update_password(const char* username, const char* new_password) {
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    bool success = false;
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    
    hash_password(new_password, hashed_password);
    
    conn = mysql_init(NULL);
    if (conn) {
        if (mysql_real_connect(conn, "localhost", "dbuser", "dbpass", 
                             "userdb", 0, NULL, 0)) {
            
            stmt = mysql_stmt_init(conn);
            if (stmt) {
                const char* sql = "UPDATE users SET password = ? WHERE username = ?";
                if (!mysql_stmt_prepare(stmt, sql, strlen(sql))) {
                    memset(bind, 0, sizeof(bind));
                    
                    bind[0].buffer_type = MYSQL_TYPE_STRING;
                    bind[0].buffer = (void*)hashed_password;
                    bind[0].buffer_length = strlen(hashed_password);
                    
                    bind[1].buffer_type = MYSQL_TYPE_STRING;
                    bind[1].buffer = (void*)username;
                    bind[1].buffer_length = strlen(username);
                    
                    if (!mysql_stmt_bind_param(stmt, bind)) {
                        if (!mysql_stmt_execute(stmt)) {
                            success = (mysql_stmt_affected_rows(stmt) > 0);
                        }
                    }
                }
                mysql_stmt_close(stmt);
            }
        }
        mysql_close(conn);
    }
    
    return success;
}

int main() {
    // Test cases
    printf("%d\\n", update_password("john_doe", "SecurePass123!"));
    printf("%d\\n", update_password("jane_smith", "StrongP@ss456"));
    printf("%d\\n", update_password("admin", "Admin@2023"));
    printf("%d\\n", update_password("test_user", "Test123!"));
    printf("%d\\n", update_password("guest", "Guest@2023"));
    
    return 0;
}
