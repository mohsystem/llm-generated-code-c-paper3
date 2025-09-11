#include <stdio.h>
#include <mysql.h>
#include <string.h>

MYSQL* connectToDatabase(const char* url, const char* user, const char* password, const char* database) {
    MYSQL* connection = mysql_init(NULL);
    if (!mysql_real_connect(connection, url, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(connection));
        return NULL;
    }
    return connection;
}

MYSQL_RES* getUserInfo(const char* username, MYSQL* connection) {
    char sql[256]; // Adjust size as needed
    snprintf(sql, sizeof(sql), "SELECT * FROM users WHERE username = '%s'", username); // Replace "users"

    if (mysql_query(connection, sql)) {
        fprintf(stderr, "Error executing query: %s\n", mysql_error(connection));
        return NULL;
    }

    return mysql_store_result(connection);
}


int main() {
    const char* url = "localhost";
    const char* user = "your_username";
    const char* password = "your_password";
    const char* database = "your_database_name";


    MYSQL* connection = connectToDatabase(url, user, password, database);
    if (!connection) {
        return 1;
    }

    const char* testUsernames[] = {"testuser1", "testuser2", "testuser3", "testuser4", "testuser5"};
    for (int i = 0; i < sizeof(testUsernames) / sizeof(testUsernames[0]); i++) {
        MYSQL_RES* result = getUserInfo(testUsernames[i], connection);
        if (result) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                 printf("Username: %s\n", row[0]); // Assuming username is the first column
                 // Print other columns as needed
            }
            mysql_free_result(result);
        }
    }

    mysql_close(connection);
    return 0;
}