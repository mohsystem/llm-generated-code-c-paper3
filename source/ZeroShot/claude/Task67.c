
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100

struct Customer {
    int id;
    char username[MAX_USERNAME_LENGTH];
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
};

struct Customer* get_customer_info(const char* customer_username) {
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    MYSQL_BIND result_bind[5];
    MYSQL_RES *prepare_meta_result;
    struct Customer* customer = NULL;
    
    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\\n");
        return NULL;
    }
    
    // Connect to database
    if (!mysql_real_connect(conn, "localhost", "dbuser", "dbpass", 
                           "customerdb", 3306, NULL, 0)) {
        fprintf(stderr, "Connection error: %s\\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }
    
    // Prepare statement
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\\n");
        mysql_close(conn);
        return NULL;
    }
    
    const char *query = "SELECT * FROM customer WHERE username = ? LIMIT 1";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\\n");
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return NULL;
    }
    
    // Bind parameter
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (void*)customer_username;
    bind[0].buffer_length = strlen(customer_username);
    
    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\\n");
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return NULL;
    }
    
    // Execute statement
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed\\n");
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return NULL;
    }
    
    // Get result metadata
    prepare_meta_result = mysql_stmt_result_metadata(stmt);
    if (!prepare_meta_result) {
        fprintf(stderr, "mysql_stmt_result_metadata() failed\\n");
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return NULL;
    }
    
    // Allocate customer structure
    customer = (struct Customer*)malloc(sizeof(struct Customer));
    if (!customer) {
        fprintf(stderr, "Memory allocation failed\\n");
        mysql_free_result(prepare_meta_result);
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return NULL;
    }
    
    // Bind result buffers
    unsigned long length[5];
    my_bool is_null[5];
    memset(result_bind, 0, sizeof(result_bind));
    
    result_bind[0].buffer_type = MYSQL_TYPE_LONG;
    result_bind[0].buffer = &(customer->id);
    result_bind[0].is_null = &is_null[0];
    result_bind[0].length = &length[0];
    
    result_bind[1].buffer_type = MYSQL_TYPE_STRING;
    result_bind[1].buffer = customer->username;
    result_bind[1].buffer_length = MAX_USERNAME_LENGTH;
    result_bind[1].is_null = &is_null[1];
    result_bind[1].length = &length[1];
    
    result_bind[2].buffer_type = MYSQL_TYPE_STRING;
    result_bind[2].buffer = customer->first_name;
    result_bind[2].buffer_length = MAX_NAME_LENGTH;
    result_bin', type='text')