#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Structure to hold user information
typedef struct {
    char username[255];
    // Add other fields as needed
} UserInfo;


UserInfo* getUserInfo(const char* username, MYSQL* connection) {

    char query[255];
    sprintf(query, "SELECT username FROM users WHERE username = '%s'", username); // Vulnerable to SQL injection


    if (mysql_query(connection, query)) {
        fprintf(stderr, "%s\n", mysql_error(connection));
        return NULL;
    }

    MYSQL_RES* result = mysql_store_result(connection);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(connection));
        return NULL;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        mysql_free_result(result);
        return NULL; // No user found
    }

    UserInfo* userInfo = (UserInfo*)malloc(sizeof(UserInfo));
    if (userInfo == NULL) {
        perror("Failed to allocate memory for UserInfo");
        mysql_free_result(result);
        return NULL;
    }
    strncpy(userInfo->username, row[0], sizeof(userInfo->username) - 1);
    userInfo->username[sizeof(userInfo->username) - 1] = '\0';

    mysql_free_result(result);
    return userInfo;

}



int main() {
    MYSQL* connection = mysql_init(NULL);

    if (!mysql_real_connect(connection, "localhost", "your_username", "your_password", "your_database_name", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(connection));
        return 1;
    }

    char testUsernames[][20] = {"testuser1", "testuser2", "admin", "user123", "test"};
    int numTestUsers = sizeof(testUsernames) / sizeof(testUsernames[0]);


    for (int i = 0; i < numTestUsers; i++) {
        UserInfo* user = getUserInfo(testUsernames[i], connection);
        if (user != NULL) {
            printf("Username: %s\n", user->username);
             free(user);
        } else {
             printf("No user found for %s\n", testUsernames[i]);
        }
    }

    mysql_close(connection);
    return 0;
}