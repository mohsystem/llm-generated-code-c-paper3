
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MAX_PASSWORD_LENGTH 256
#define HASH_LENGTH SHA256_DIGEST_LENGTH * 2 + 1

char* hash_password(const char* password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    char* output = (char*)malloc(HASH_LENGTH);
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[HASH_LENGTH-1] = 0;
    return output;
}

int update_password(const char* username, const char* new_password) {
    MYSQL* conn;
    MYSQL_STMT* stmt;
    int success = 0;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("Error initializing MySQL connection\\n");
        return 0;
    }

    if (!mysql_real_connect(conn, "localhost", "root", "password", 
                           "userdb", 0, NULL, 0)) {
        printf("Error connecting to database: %s\\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    char* hashed_password = hash_password(new_password);
    const char* sql = "UPDATE users SET password = ? WHERE username = ?";
    
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        printf("Error initializing statement: %s\\n", mysql_error(conn));
        free(hashed_password);
        mysql_close(conn);
        return 0;
    }

    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        printf("Error preparing statement: %s\\n", mysql_stmt_error(stmt));
        free(hashed_password);
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }

    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (void*)hashed_password;
    bind[0].buffer_length = strlen(hashed_password);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (void*)username;
    bind[1].buffer_length = strlen(username);

    if (mysql_stmt_bind_param(stmt, bind)) {
        printf("Error binding parameters: %s\\n", mysql_stmt_error(stmt));
    } else if (mysql_stmt_execute(stmt)) {
        printf("Error executing statement: %s\\n", mysql_stmt_error(stmt));
    } else {
        success = mysql_stmt_affected_rows(stmt) > 0;
    }

    free(hashed_password);
    mysql_stmt_close(stmt);
    mysql_close(conn);

    return success;
}

int main() {
    // Test cases
    struct {
        const char* username;
        const char* password;
    } test_cases[] = {
        {"john_doe", "newPass123"},
        {"jane_smith", "securePass456"},
        {"admin", "adminPass789"},
        {"user1", "userPass321"},
        {"test_user", "testPass654"}
    };

    for (int i = 0; i < 5; i++) {
        int result = update_password(test_cases[i].username, test_cases[i].password);
        printf("Update password for %s: %s\\n", 
               test_cases[i].username, 
               result ? "Success" : "Failed");
    }

    return 0;
}
