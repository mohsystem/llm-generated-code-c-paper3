#include <stdio.h>
#include <sql.h>
#include <sqlext.h>

void getUserInfo(SQLHDBC hdbc, const char* username) {
    SQLHSTMT hstmt;
    SQLRETURN ret;
    char buffer[1024];

    ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    if (ret != SQL_SUCCESS) {
        printf("SQLAllocHandle failed\n");
        return;
    }

    ret = SQLPrepare(hstmt, (SQLCHAR*)"SELECT * FROM users WHERE username = ?", SQL_NTS);
    if (ret != SQL_SUCCESS) {
        printf("SQLPrepare failed\n");
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return;
    }

    ret = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 50, 0, (SQLPOINTER)username, 0, NULL);
    if (ret != SQL_SUCCESS) {
        printf("SQLBindParameter failed\n");
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return;
    }

    ret = SQLExecute(hstmt);
    if (ret != SQL_SUCCESS) {
        printf("SQLExecute failed\n");
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        return;
    }

    while ((ret = SQLFetch(hstmt)) != SQL_NO_DATA) {
        if (ret != SQL_SUCCESS) {
            printf("SQLFetch failed\n");
            SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
            return;
        }
        SQLGetData(hstmt, 1, SQL_C_CHAR, buffer, sizeof(buffer), NULL);
        printf("Username: %s\n", buffer);
        SQLGetData(hstmt, 2, SQL_C_CHAR, buffer, sizeof(buffer), NULL);
        printf("Full Name: %s\n", buffer);
        SQLGetData(hstmt, 3, SQL_C_CHAR, buffer, sizeof(buffer), NULL);
        printf("Email: %s\n", buffer);
        // Add other fields as needed
    }

    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
}

int main() {
    SQLHENV henv;
    SQLHDBC hdbc;
    SQLRETURN ret;
    const char* usernames[] = {"user1", "user2", "user3", "user4", "user5"};

    // Initialize ODBC
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (ret != SQL_SUCCESS) {
        printf("SQLAllocHandle failed\n");
        return 1;
    }

    ret = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    if (ret != SQL_SUCCESS) {
        printf("SQLSetEnvAttr failed\n");
        SQLFreeHandle(SQL_HANDLE_ENV, henv);
        return 1;
    }

    ret = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    if (ret != SQL_SUCCESS) {
        printf("SQLAllocHandle failed\n");
        SQLFreeHandle(SQL_HANDLE_ENV, henv);
        return 1;
    }

    ret = SQLConnect(hdbc, (SQLCHAR*)"your_server", SQL_NTS, (SQLCHAR*)"your_username", SQL_NTS, (SQLCHAR*)"your_password", SQL_NTS);
    if (ret != SQL_SUCCESS) {
        printf("SQLConnect failed\n");
        SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
        SQLFreeHandle(SQL_HANDLE_ENV, henv);
        return 1;
    }

    for (int i = 0; i < 5; ++i) {
        getUserInfo(hdbc, usernames[i]);
    }

    SQLDisconnect(hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);

    return 0;
}