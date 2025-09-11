#include <stdio.h>
#include <mysql/mysql.h>

void getUserInfo(const char *username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return;
    }

    if (mysql_real_connect(conn, "localhost", "user", "password", "yourDB", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username = '%s'", username);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "SELECT * FROM users failed\n");
        mysql_close(conn);
        return;
    }

    res = mysql_store_result(conn);
    if (res) {
        while ((row = mysql_fetch_row(res))) {
            printf("%s\n", row[1]); // Assuming the info is in the second column
        }
        mysql_free_result(res);
    }
    mysql_close(conn);
}

int main() {
    getUserInfo("testuser1");
    getUserInfo("testuser2");
    getUserInfo("testuser3");
    getUserInfo("testuser4");
    getUserInfo("testuser5");
    return 0;
}