
#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HOST "localhost"
#define USER "testuser"
#define PASS "testpass"
#define DB "testdb"
#define PORT 3306
#include <stdbool.h>
typedef bool my_bool;
char* get_user_info(const char* username) {
    char* result = malloc(256);  // Allocate memory for result
    if (!result) {
        return NULL;
    }
    
    // Input validation
    if (!username || strlen(username) == 0) {
        strcpy(result, "Invalid username");
        return result;
    }

    MYSQL* conn = mysql_init(NULL);
    if (!conn) {
        strcpy(result, "MySQL initialization failed");
        return result;
    }

    // Enable automatic reconnection
    my_bool reconnect = 1;
    mysql_options(conn, MYSQL_OPT_RECONNECT, &reconnect);

    if (!mysql_real_connect(conn, HOST, USER, PASS, DB, PORT, NULL, 0)) {
        snprintf(result, 256, "Connection error: %s", mysql_error(conn));
        mysql_close(conn);
        return result;
    }

    // Prepare statement to prevent SQL injection
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if (!stmt) {
        strcpy(result, "Statement initialization failed");
        mysql_close(conn);
        return result;
    }

    const char* sql = "SELECT id, name, email FROM users WHERE username = ?";
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
        strcpy(result, "No results found");
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return result;
    }

    if (mysql_stmt_fetch(stmt) == 0) {
        MYSQL_BIND result_bind[3];
        memset(result_bind, 0, sizeof(result_bind));
        
        int id;
        char name[50];
        char email[50];
        
        result_bind[0].buffer_type = MYSQL_TYPE_LONG;
        result_bind[0].buffer = &id;
        result_bind[1].buffer_type = MYSQL_TYPE_STRING;
        result_bind[1].buffer = name;
        result_bind[1].buffer_length = sizeof(name);
        result_bind[2].buffer_type = MYSQL_TYPE_STRING;
        result_bind[2].buffer = email;
        result_bind[2].buffer_length = sizeof(email);

        if (mysql_stmt_bind_result(stmt, result_bind)) {
            strcpy(result, "Binding result failed");
        } else {
            snprintf(result, 256, "User ID: %d, Name: %s, Email: %s", 
                    id, name, email);
        }
    } else {
        strcpy(result, "User not found");
    }

    mysql_free_result(prepare_meta_result);
    mysql_stmt_close(stmt);
    mysql_close(conn);
    
    return result;
}

int main() {
    // Test cases
    const char* test_cases[] = {
        "john_doe",
        "alice123",
        "",
        "admin'--",
        "nonexistent_user"
    };

    for (int i = 0; i < 5; i++) {
        char* result = get_user_info(test_cases[i]);
        if (result) {
            printf("Test case %d: %s\\n", i + 1, result);
            free(result);
        }
    }

    return 0;
}
