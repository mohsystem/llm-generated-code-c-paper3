#include <mysql.h>
#include <stdio.h>
#include <string.h>

void getProductDetails(const char *productName) {
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    char *server = "localhost";
    char *user = "username";
    char *password = "password";
    char *database = "myDatabase";
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM products WHERE name = '%s'", productName);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("Product Name: %s\n", row[0]);
        printf("Product Price: %s\n", row[1]);
        printf("Product Description: %s\n", row[2]);
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char productName[256];
    printf("Enter product name: ");
    fgets(productName, sizeof(productName), stdin);
    strtok(productName, "\n");
    getProductDetails(productName);
    return 0;
}