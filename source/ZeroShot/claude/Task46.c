
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>
#include <regex.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 50
#define MIN_PASSWORD_LENGTH 8
#define HASH_LENGTH 65

const char* DB_HOST = "localhost";
const char* DB_USER = "root";
const char* DB_PASS = "password";
const char* DB_NAME = "userdb";

int validate_email(const char* email) {
    regex_t regex;
    int ret;
    
    ret = regcomp(&regex, "^[A-Za-z0-9+_.-]+@(.+)$", REG_EXTENDED);
    if (ret) {
        return 0;
    }
    
    ret = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

int validate_password(const char* password) {
    int has_upper = 0, has_lower = 0, has_digit = 0;
    size_t len = strlen(password);
    
    if (len < MIN_PASSWORD_LENGTH) {
        return 0;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (isupper(password[i])) has_upper = 1;
        if (islower(password[i])) has_lower = 1;
        if (isdigit(password[i])) has_digit = 1;
    }
    
    return has_upper && has_lower && has_digit;
}

void hash_password(const char* password, char* hashed) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", hash[i]);
    }
    hashed[64] = '\\0';
}

int register_user(const char* name, const char* email, const char* password) {
    if (!name || strlen(name) == 0 || strlen(name) > MAX_NAME_LENGTH) {
        return 0;
    }
    
    if (!validate_email(email)) {
        return 0;
    }
    
    if (!validate_password(password)) {
        return 0;
    }
    
    MYSQL* conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        mysql_close(conn);
        return 0;
    }
    
    char hashed_password[HASH_LENGTH];
    hash_password(password, hashed_password);
    
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if (!stmt) {
        mysql_close(conn);
        return 0;
    }
    
    const char* sql = "INSERT INTO users (name, email, password) VALUES (?, ?, ?)";
    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }
    
    MYSQL_BIND bind[3];
    memset(bind, 0, sizeof(bind));
    
    unsigned long name_length = strlen(name);
    unsigned long email_length = strlen(email);
    unsigned long password_length = strlen(hashed_password);
    
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (void*)name;
    bind[0].buffer_length = name_length;
    bind[0].length = &name_length;
    
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (void*)email;
    bind[1].buffer_length = email_length;
    bind[1].length = &email_length;
    
    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (void*)hashed_password;
    bind[2].buffer_length = password_length;
    bind[2].length = &password_length;
    
    if (mysql_stmt_bind_param(stmt, bind)) {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }
    
    int success = (mysql_stmt_execute(stmt) == 0);
    
    mysql_stmt_close(stmt);
    mysql_close(conn);
    
    return success;
}

int main() {
    // Test cases
    printf("%d\\n", register_user("John Doe", "john@example.com", "Password123")); // Valid input
    printf("%d\\n", register_user("", "invalid", "weak")); // Invalid input
    printf("%d\\n",', type='text')