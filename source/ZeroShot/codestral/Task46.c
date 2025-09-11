// Since C doesn't have built-in support for high-level functionalities such as Object-Oriented Programming and Exception handling, the code is more complex and error-prone.
// A secure implementation would require using a library such as libmysqlclient or mysql++, which is out of the scope of this task.
// The provided code is a simple, non-secure example of how to insert data into a MySQL database using C.

#include <mysql.h>
#include <stdio.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "username";
    char *password = "password";
    char *database = "myDatabase";

    char query[200];
    sprintf(query, "INSERT INTO users (name, email, password) VALUES ('%s', '%s', '%s')", "John Doe", "john.doe@example.com", "password123"); // Make sure you're hashing this password

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
    return 0;
}