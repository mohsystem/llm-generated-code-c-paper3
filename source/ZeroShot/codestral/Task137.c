#include <mysql.h>
#include <stdio.h>

void getProductDetails(const char* productName) {
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

    char* server = "localhost";
    char* user = "username";
    char* password = "password";
    char* database = "myDatabase";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM Products WHERE Name = '%s'", productName);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res)) != NULL) {
        printf("Name: %s, Price: %s\n", row[0], row[1]);
    } else {
        printf("Product not found\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    // Test cases
    getProductDetails("Product1");
    getProductDetails("Product2");
    // Add more test cases as needed

    return 0;
}