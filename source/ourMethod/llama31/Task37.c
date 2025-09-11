#include <stdio.h>
#include <sql.h>
#include <sqlext.h>

int main() {
    SQLHENV henv;
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
    SQLRETURN ret;

    // Initialize ODBC
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        printf("SQLAllocHandle failed\n");
        return 1;
    }

    ret = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        printf("SQLSetEnvAttr failed\n");
        return 1;
    }

    ret = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        printf("SQLAllocHandle failed\n");
        return 1;
    }

    // Connect to database
    char dbUrl[256] = "DRIVER={MySQL ODBC 8.0 Driver};SERVER=localhost;DATABASE=your_database;UID=your_username;PWD=your_password";
    ret = SQLDriverConnect(hdbc, NULL, (SQLCHAR*)dbUrl, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        printf("SQLDriverConnect failed\n");
        return 1;
    }

    // Prepare and execute query
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        printf("SQLAllocHandle failed\n");
        return 1;
    }

    char query[256] = "SELECT * FROM users WHERE username = ?";
    ret = SQLPrepare(hstmt, (SQLCHAR*)query, SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        printf("SQLPrepare failed\n");
        return 1;
    }

    char username[100];
    printf("Enter the username to retrieve: ");
    scanf("%99s", username);

    ret = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 100, 0, username, 100, NULL);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        printf("SQLBindParameter failed\n");
        return 1;
    }

    ret = SQLExecute(hstmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        printf("SQLExecute failed\n");
        return 1;
    }

    // Fetch and display results
    while ((ret = SQLFetch(hstmt)) == SQL_SUCCESS) {
        printf("User found:\n");
        SQLCHAR name[100], email[100];
        ret = SQLGetData(hstmt, 2, SQL_C_CHAR, name, 100, NULL);
        ret = SQLGetData(hstmt, 3, SQL_C_CHAR, email, 100, NULL);
        printf("Username: %s\n", username);
        printf("Name: %s\n", name);
        printf("Email: %s\n", email);
    }
    if (ret == SQL_NO_DATA) {
        printf("User not found\n");
    }

    // Clean up
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    SQLDisconnect(hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);

    return 0;
}