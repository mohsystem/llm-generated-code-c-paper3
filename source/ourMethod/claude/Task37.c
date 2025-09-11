
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_USERNAME_LENGTH 100
#define MAX_EMAIL_LENGTH 100

// Database configuration
const char* DB_HOST = "localhost";
const char* DB_USER = "dbuser";
const char* DB_PASSWORD = "dbpassword";
const char* DB_NAME = "userdb";
const unsigned int DB_PORT = 3306;

MYSQL* connect_to_database() {
    MYSQL* conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "MySQL initialization failed\\n");
        return NULL;
    }

    // Enable automatic reconnection
    my_bool reconnect = 1;
    mysql_options(conn, MYSQL_OPT_RECONNECT, &reconnect);

    // Use SSL for secure connection
    mysql_ssl_set(conn, NULL, NULL, NULL, NULL, NULL);

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASSWORD, 
                          DB_NAME, DB_PORT, NULL, 0)) {
        fprintf(stderr, "Connection failed\\n");
        mysql_close(conn);
        return NULL;
    }
    return conn;
}

void get_user_info(const char* username) {
    if (username == NULL || strlen(username) == 0) {
        printf("Username cannot be empty\\n");
        return;
    }

    if (strlen(username) >= MAX_USERNAME_LENGTH) {
        printf("Username is too long\\n");
        return;
    }

    MYSQL* conn = connect_to_database();
    if (conn == NULL) {
        printf("Error occurred while accessing database\\n");
        return;
    }

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if (stmt == NULL) {
        mysql_close(conn);
        printf("Error occurred while accessing database\\n");
        return;
    }

    const char* query = "SELECT id, username, email FROM users WHERE username = ?";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        printf("Error occurred while accessing database\\n");
        return;
    }

    // Bind parameters
    MYSQL_BIND bind[1] = {0};
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (void*)username;
    bind[0].buffer_length = strlen(username);

    if (mysql_stmt_bind_param(stmt, bind)) {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        printf("Error occurred while accessing database\\n");
        return;
    }

    if (mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        printf("Error occurred while accessing database\\n");
        return;
    }

    MYSQL_RES* prepare_meta_result = mysql_stmt_result_metadata(stmt);
    if (!prepare_meta_result) {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        printf("Error occurred while accessing database\\n");
        return;
    }

    // Bind result buffers
    MYSQL_BIND result_bind[3] = {0};
    int id;
    char username_buf[MAX_USERNAME_LENGTH];
    char email_buf[MAX_EMAIL_LENGTH];
    unsigned long username_length, email_length;

    result_bind[0].buffer_type = MYSQL_TYPE_LONG;
    result_bind[0].buffer = &id;

    result_bind[1].buffer_type = MYSQL_TYPE_STRING;
    result_bind[1].buffer = username_buf;
    result_bind[1].buffer_length = sizeof(username_buf);
    result_bind[1].length = &username_length;

    result_bind[2].buffer_type = MYSQL_TYPE_STRING;
    result_bind[2].buffer = email_buf;
    result_bind[2].buffer_length = sizeof(email_buf);
    result_bind[2].length = &email_length;

    if (mysql_stmt_bind_result(stmt, result_bind)) {
        mysql_free_result(prepare_meta_result);
        mysql_stmt_close(stmt);
        mysql_close(conn);
        printf("Error occurred while accessing database\\n");
        return;
    }

    // Fetch and display results
    if (mysql_stmt_fetch(stmt) == 0) {
        printf("User found:\\n");
        printf("ID: %d\\n", id);
        printf("Username: %s\\n", username_buf);
        printf("Email: %s\\n", email_buf);
    } else {
        printf("User not found\\n");
    }

    mysql_free_result(prepare_meta_result);
    mysql_stmt_close(stmt);
    mysql_close(conn);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    
    // Interactive input
    printf("Enter username to search: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove trailing newline
        username[strcspn(username, "\\n")] = 0;
        get_user_info(username);
    }
    
    // Test cases
    printf("\\nTest Cases:\\n");
    get_user_info("validUser");
    get_user_info("");  // Empty username
    get_user_info("user'; DROP TABLE users; --");  // SQL injection attempt
    get_user_info("normalUser123");
    
    return 0;
}
