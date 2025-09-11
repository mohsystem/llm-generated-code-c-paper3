
#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HOST "localhost"
#define USER "dbuser"
#define PASS "dbpass"
#define DB "userdb"
#define PORT 3306

// Function to validate username
int is_valid_username(const char* username) {
    if (!username || strlen(username) < 3 || strlen(username) > 20)
        return 0;
        
    for (int i = 0; username[i]; i++) {
        if (!isalnum(username[i]) && username[i] != '_')
            return 0;
    }
    return 1;
}

char* get_user_info(const char* username) {
    char* result = malloc(256);
    if (!result) {
        return NULL;
    }
    
    // Input validation
    if (!is_valid_username(username)) {
        strcpy(result, "Invalid username format");
        return result;
    }
    
    MYSQL* conn = mysql_init(NULL);
    if (conn == NULL) {
        strcpy(result, "MySQL initialization failed");
        return result;
    }
    
    if (!mysql_real_connect(conn, HOST, USER, PASS, DB, PORT, NULL, 0)) {
        snprintf(result, 256, "Connection error: %s", mysql_error(conn));
        mysql_close(conn);
        return result;
    }
    
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if (!stmt) {
        strcpy(result, "Statement initialization failed");
        mysql_close(conn);
        return result;
    }
    
    const char* sql = "SELECT id, username, email FROM users WHERE username = ?";
    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        snprintf(result, 256, "Prepare failed: %s", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return result;
    }
    
    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (void*)username;
    bind[0].buffer_length = strlen(username);
    
    if (mysql_stmt_bind_param(stmt, bind)) {
        snprintf(result, 256, "Bind failed: %s", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return result;
    }
    
    if (mysql_stmt_execute(stmt)) {
        snprintf(result, 256, "Execute failed: %s", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return result;
    }
    
    MYSQL_RES* prepare_meta_result = mysql_stmt_result_metadata(stmt);
    if (!prepare_meta_result) {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        strcpy(result, "No results found");
        return result;
    }
    
    int id;
    char username_buf[50];
    char email_buf[100];
    unsigned long length[3];
    my_bool is_null[3];
    MYSQL_BIND result_bind[3];
    memset(result_bind, 0, sizeof(result_bind));
    
    result_bind[0].buffer_type = MYSQL_TYPE_LONG;
    result_bind[0].buffer = &id;
    result_bind[0].is_null = &is_null[0];
    result_bind[0].length = &length[0];
    
    result_bind[1].buffer_type = MYSQL_TYPE_STRING;
    result_bind[1].buffer = username_buf;
    result_bind[1].buffer_length = sizeof(username_buf);
    result_bind[1].is_null = &is_null[1];
    result_bind[1].length = &length[1];
    
    result_bind[2].buffer_type = MYSQL_TYPE_STRING;
    result_bind[2].buffer = email_buf;
    result_bind[2].buffer_length = sizeof(email_buf);
    result_bind[2].is_null = &is_null[2];
    result_bind[2].length = &length[2];
    
    if (mysql_stmt_bind_result(stmt, result_bind)) {
        snprintf(result, 256, "Result bind failed: %s", mysql_stmt_error(stmt));
    }
    else if (mysql_stmt_fetch(stmt)) {
        strcpy(result, "User not found");
    }
    else {
        snprintf(result, 256, "ID: %d, Username: %s, Email: %s", 
                id, username_buf, email_buf);
    }
    
    mysql_free_result(prepare_meta_result);
    mysql_stmt_close(stmt);
    mysql_close(conn);
    return result;
}

int main() {
    // Test cases
    char* result;
    
    result = get_user_info("john_doe");
    printf("%s\\n", result);
    free(result);
    
    result = get_user_info("alice123");
    printf("%s\\n", result);
    free(result);
    
    result = get_user_info("admin");
    printf("%s\\n", result);
    free(result);
    
    result = get_user_info("'; DROP TABLE users;--");
    printf("%s\\n", result);
    free(result);
    
    result = get_user_info("");
    printf("%s\\n", result);
    free(result);
    
    return 0;
}
