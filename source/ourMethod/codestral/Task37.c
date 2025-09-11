#include <mysql.h>
#include <stdio.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "username";
    char *password = "password";
    char *database = "dbname";
    char *username = "testuser"; // replace with user input

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT * FROM Users WHERE Username = '%s'", username);

    if (mysql_query(conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res)) != NULL)
        printf("%s %s\n", row[0], row[1]);

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}