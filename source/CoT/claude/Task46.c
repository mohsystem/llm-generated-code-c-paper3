
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>
#include <regex.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 256
#define MIN_PASSWORD_LENGTH 8

typedef struct {
    char name[MAX_INPUT_LENGTH];
    char email[MAX_INPUT_LENGTH];
    char password[MAX_INPUT_LENGTH];
} UserData;

// Database configuration
const char* DB_HOST = "localhost";
const char* DB_USER = "root";
const char* DB_PASS = "password";
const char* DB_NAME = "userdb";
const int DB_PORT = 3306;

int is_valid_email(const char* email) {
    regex_t regex;
    int result;
    
    regcomp(&regex, "^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+$", REG_EXTENDED);
    result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    
    return result == 0;
}

void sanitize_input(char* input) {
    char* src = input;
    char* dst = input;
    
    while (*src) {
        if (isalnum((unsigned char)*src) || *src == '@' || *src == '.' || 
            *src == '_' || *src == '-') {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\\0';
}

void hash_password(const char* password, char* hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    hashed_password[SHA256_DIGEST_LENGTH * 2] = '\0';
}

int is_valid_input(const UserData* user_data) {
    if (!user_data->name[0] || !user_data->email[0] || !user_data->password[0]) {
        return 0;
    }
    
    if (!is_valid_email(user_data->email)) {
        return 0;
    }
    
    if (strlen(user_data->password) < MIN_PASSWORD_LENGTH) {
        return 0;
    }
    
    return 1;
}

int register_user(const char* name, const char* email, const char* password) {
    UserData user_data;
    MYSQL* conn;
    MYSQL_STMT* stmt;
    MYSQL_BIND bind[3];
    int success = 0;
    
    // Copy and validate input
    strncpy(user_data.name, name, MAX_INPUT_LENGTH - 1);
    strncpy(user_data.email, email, MAX_INPUT_LENGTH - 1);
    strncpy(user_data.password, password, MAX_INPUT_LENGTH - 1);
    user_data.name[MAX_INPUT_LENGTH - 1] = '\\0';
    user_data.email[MAX_INPUT_LENGTH - 1] = '\\0';
    user_data.password[MAX_INPUT_LENGTH - 1] = '\\0';
    
    if (!is_valid_input(&user_data)) {
        return 0;
    }
    
    // Sanitize inputs
    sanitize_input(user_data.name);
    sanitize_input(user_data.email);
    
    // Hash password
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(user_data.password, hashed_password);
    
    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (!conn) {
        return 0;
    }
    
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0)) {
        mysql_close(conn);
        return 0;
    }
    
    // Prepare statement
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        mysql_close(conn);
        return 0;
    }
  //todo    //incomplete code
    // const char* query = "INSERT INTO users (name, email, passwor', type='text')
}