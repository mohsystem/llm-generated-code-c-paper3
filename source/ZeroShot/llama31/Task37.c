#include <stdio.h>
#include <sql.h>
#include <sqlext.h>

void getUserInfo(const char* username, const char* server, const char* database, const char* user, const char* password) {
    SQLHENV henv;
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
    SQLRETURN retcode;
    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;

    // Allocate environment handle
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (retcode != SQL_SUCCESS) {
        printf("SQLAllocHandle failed\n");
        return;
    }

    // Set ODBC version
    retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    if (retcode != SQL_SUCCESS) {
        printf("SQLSetEnvAttr failed\n");
        return;
    }

    // Allocate connection handle
    retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    if (retcode != SQL_SUCCESS) {
        printf("SQLAllocHandle failed\n");
        return;
    }

    // Connect to database
    retcode = SQLDriverConnect(hdbc, NULL, (SQLCHAR*)("DRIVER={ODBC Driver 17 for SQL Server};SERVER="),
                               (SQLSMALLINT)strlen("DRIVER={ODBC Driver 17 for SQL Server};SERVER="),
                               (SQLCHAR*)(server), (SQLSMALLINT)strlen(server),
                               (SQLCHAR*)(database), (SQLSMALLINT)strlen(database),
                               (SQLCHAR*)(user), (SQLSMALLINT)strlen(user),
                               (SQLCHAR*)(password), (SQLSMALLINT)strlen(password),
                               SQL_NTS, outstr, sizeof(outstr), &outstrlen, SQL_DRIVER_NOPROMPT);
    if (retcode != SQL_SUCCESS) {
        printf("SQLDriverConnect failed\n");
        return;
    }

    // Allocate statement handle
    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    if (retcode != SQL_SUCCESS) {
        printf("SQLAllocHandle failed\n");
        return;
    }

    // Prepare and execute query
    retcode = SQLPrepare(hstmt, (SQLCHAR*)"SELECT * FROM users WHERE username = ?", SQL_NTS);
    if (retcode != SQL_SUCCESS) {
        printf("SQLPrepare failed\n");
        return;
    }

    retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(username), 0, (SQLPOINTER)username, 0, NULL);
    if (retcode != SQL_SUCCESS) {
        printf("SQLBindParameter failed\n");
        return;
    }

    retcode = SQLExecute(hstmt);
    if (retcode != SQL_SUCCESS) {
        printf("SQLExecute failed\n");
        return;
    }

    // Fetch and display results
    while ((retcode = SQLFetch(hstmt)) != SQL_NO_DATA) {
        SQLCHAR userId[20];
        SQLCHAR userName[50];
        SQLCHAR name[100];

        retcode = SQLGetData(hstmt, 1, SQL_C_CHAR, userId, sizeof(userId), NULL);
        retcode = SQLGetData(hstmt, 2, SQL_C_CHAR, userName, sizeof(userName), NULL);
        retcode = SQLGetData(hstmt, 3, SQL_C_CHAR, name, sizeof(name), NULL);

        printf("User ID: %s\n", userId);
        printf("Username: %s\n", userName);
        printf("Name: %s\n", name);
    }

    // Free handles
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    SQLDisconnect(hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);
}

int main() {
    char username[100];
    printf("Enter the username: ");
    scanf("%99s", username);

    char* server = "your_server";
    char* database = "your_database";
    char* user = "your_username";
    char* password = "your_password";

    getUserInfo(username, server, database, user, password);
    return 0;
}