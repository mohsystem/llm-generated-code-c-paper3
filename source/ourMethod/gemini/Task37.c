#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

sqlite3* db;

int connect_to_db(const char* db_path) {
    int rc = sqlite3_open(db_path, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }
    return 0;
}

void close_db_connection() {
    sqlite3_close(db);
}

int get_user_info(const char* username, char** user_info) {
    if (username == NULL || strlen(username) == 0) {
        fprintf(stderr, "Username cannot be null or empty.\n");
        return 1;
    }

     // Use sqlite3_snprintf to safely format the query 
    char query[256];
    sqlite3_snprintf(sizeof(query), query, "SELECT * FROM users WHERE username = '%q'", username);


    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int num_cols = sqlite3_column_count(stmt);
        *user_info = (char*)malloc(1024); // Allocate sufficient memory
        if (*user_info == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return SQLITE_ERROR;
        }
        strcpy(*user_info, ""); // Initialize the string
        for (int i = 0; i < num_cols; ++i) {
            strcat(*user_info, (const char*)sqlite3_column_text(stmt, i));
             if (i < num_cols - 1) {
                strcat(*user_info, " ");
            }
        }
    } else if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return rc;
}

int main() {
    const char* db_path = "your_database.db";
    if (connect_to_db(db_path) != 0) {
        return 1;
    }

    const char* usernames[5] = {"testuser1", "testuser2", "testuser3", "testuser4", "testuser5"};

    for (int i = 0; i < 5; ++i) {
        char* user_info = NULL;
        int rc = get_user_info(usernames[i], &user_info);
        if (rc == SQLITE_ROW && user_info != NULL) {
            printf("%s\n", user_info);
            free(user_info); // Free the allocated memory
        } else if (rc == SQLITE_DONE) {
            printf("No information found for username: %s\n", usernames[i]);
        } else if (user_info != NULL) {
            free(user_info);
        }
    }


    close_db_connection();
    return 0;
}