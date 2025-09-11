#include <stdio.h>
#include <sql.h>
#include <sqlext.h>

void getUserInfo(const char* username) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;

    // Initialize ODBC
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    if (ret != SQL_SUCCESS) {
        printf("Error: SQLAllocHandle failed\n");
        return;
    }
    ret = SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    if (ret != SQL_SUCCESS) {
        printf("Error: SQLSetEnvAttr failed\n");
        return;
    }
    ret = SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    if (ret != SQL_SUCCESS) {
        printf("Error: SQLAllocHandle failed\n");
        return;
    }

    // Connect to the database
    const char* connectionString = "DRIVER={MySQL ODBC 8.0 Driver};SERVER=localhost;DATABASE=yourdb;USER=youruser;PASSWORD=yourpassword";
    ret = SQLDriverConnect(dbc, NULL, (SQLCHAR*)connectionString, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
    if (ret != SQL_SUCCESS) {
        printf("Error: SQLDriverConnect failed\n");
        return;
    }

    // Prepare and execute the query
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (ret != SQL_SUCCESS) {
        printf("Error: SQLAllocHandle failed\n");
        return;
    }
    const char* query = "SELECT * FROM users WHERE username = ?";
    ret = SQLPrepare(stmt, (SQLCHAR*)query, SQL_NTS);
    if (ret != SQL_SUCCESS) {
        printf("Error: SQLPrepare failed\n");
        return;
    }
    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 50, 0, (SQLPOINTER)username, 0, NULL);
    if (ret != SQL_SUCCESS) {
        printf("Error: SQLBindParameter failed\n");
        return;
    }
    ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS) {
        printf("Error: SQLExecute failed\n");
        return;
    }

    // Fetch and display the result
    while ((ret = SQLFetch(stmt)) == SQL_SUCCESS) {
        SQLCHAR userId[50];
        SQLCHAR userName[50];
        SQLCHAR name[50];
        ret = SQLGetData(stmt, 1, SQL_C_CHAR, userId, 50, NULL);
        ret = SQLGetData(stmt, 2, SQL_C_CHAR, userName, 50, NULL);
        ret = SQLGetData(stmt, 3, SQL_C_CHAR, name, 50, NULL);
        printf("User ID: %s\n", userId);
        printf("Username: %s\n", userName);
        printf("Name: %s\n", name);
    }

    // Clean up
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    SQLDisconnect(dbc);
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);
}

int main() {
    // Test cases
    const char* usernames[] = {"user1", "user2", "user3", "user4", "user5"};
    for (int i = 0; i < 5; ++i) {
        getUserInfo(usernames[i]);
    }
    return 0;
}