#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>


MYSQL* connectToDatabase(const char* user, const char* password, const char* database) {
    MYSQL* connection = mysql_init(NULL);

    if (!mysql_real_connect(connection, "localhost", user, password, database, 3306, NULL, 0)) {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(connection));
        return NULL;
    }
    return connection;
}

MYSQL_RES* getUserInfo(const char* username, MYSQL* connection) {

    char escaped_username[256];  // Adjust size as needed
    mysql_real_escape_string(connection, escaped_username, username, strlen(username));

    char query[512]; // Adjust size as needed
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username = '%s'", escaped_username);


    if (mysql_query(connection, query)) {
        fprintf(stderr, "Error executing query: %s\n", mysql_error(connection));
        return NULL;
    }

    return mysql_store_result(connection);
}


int main() {
    // Database credentials
    const char* dbUser = "your_username";
    const char* dbPassword = "your_password";
    const char* dbName = "your_database_name";

    MYSQL* connection = connectToDatabase(dbUser, dbPassword, dbName);
    if (!connection) {
        return 1;
    }


    char username[256];
    printf("Enter username: ");
    scanf("%s", username);


    MYSQL_RES* result = getUserInfo(username, connection);

    if (result) {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            printf("User ID: %s\n", row[0]);
            printf("Username: %s\n", row[1]);
            // ... other user info
        }
        mysql_free_result(result);
    } else {
        printf("User not found or error occurred.\n");
    }

    mysql_close(connection);
    return 0;

}