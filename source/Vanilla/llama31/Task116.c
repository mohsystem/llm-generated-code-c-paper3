#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

void change_password_and_drop_privileges(const char* username, const char* host, const char* newPassword, const char* dbUrl, const char* dbUsername, const char* dbPassword) {
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

    conn = mysql_init(0);
    if (!mysql_real_connect(conn, dbUrl, dbUsername, dbPassword, NULL, 0, NULL, 0)) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(conn));
        return;
    }

    // Change password
    char changePasswordQuery[256];
    sprintf(changePasswordQuery, "ALTER USER %s@%s IDENTIFIED BY '%s'", username, host, newPassword);
    if (mysql_query(conn, changePasswordQuery)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(conn));
        return;
    }

    // Drop user privileges
    char dropPrivilegesQuery[256];
    sprintf(dropPrivilegesQuery, "REVOKE ALL ON mydb.* FROM %s@%s", username, host);
    if (mysql_query(conn, dropPrivilegesQuery)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(conn));
        return;
    }

    // Drop user
    char dropUserQuery[256];
    sprintf(dropUserQuery, "DROP USER %s@%s", username, host);
    if (mysql_query(conn, dropUserQuery)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(conn));
        return;
    }

    mysql_close(conn);
}

int main() {
    const char* dbUrl = "localhost";
    const char* dbUsername = "root";
    const char* dbPassword = "password";
    const char* userToModify = "example_user";
    const char* host = "%";
    const char* newPassword = "new_password";

    change_password_and_drop_privileges(userToModify, host, newPassword, dbUrl, dbUsername, dbPassword);

    return 0;
}