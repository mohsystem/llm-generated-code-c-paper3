
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASS "password"
#define DB "testdb"

char* get_user_info(const char* username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    static char result[256];
    
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASS, DB, 0, NULL, 0)) {
        snprintf(result, sizeof(result), "Database connection failed: %s", mysql_error(conn));
        return result;
    }
    
    char query[512];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username = '%s'", username);
    
    if (mysql_query(conn, query)) {
        snprintf(result, sizeof(result), "Query failed: %s", mysql_error(conn));
        mysql_close(conn);
        return result;
    }
    
    res = mysql_use_result(conn);
    if ((row = mysql_fetch_row(res)) != NULL) {
        snprintf(result, sizeof(result), "ID: %s, Username: %s, Email: %s", 
                row[0], row[1], row[2]);
    } else {
        strcpy(result, "User not found");
    }
    
    mysql_free_result(res);
    mysql_close(conn);
    return result;
}

int main() {
    // Test cases
    printf("%s\\n", get_user_info("john_doe"));
    printf("%s\\n", get_user_info("jane_smith"));
    printf("%s\\n", get_user_info("admin"));
    printf("%s\\n", get_user_info("test_user"));
    printf("%s\\n", get_user_info("nonexistent"));
    
    return 0;
}
