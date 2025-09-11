#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    char username[50];
    char name[100];
    char email[100];
} Customer;

Customer getCustomerInfo(const char* customerUsername) {
    Customer customer = {"", "", ""};
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return customer;
    }

    if (mysql_real_connect(conn, "localhost", "your_username", "your_password", "your_database", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return customer;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT username, name, email FROM customer WHERE username = '%s'", customerUsername);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return customer;
    }

    res = mysql_store_result(conn);
    if (res) {
        while ((row = mysql_fetch_row(res))) {
            strncpy(customer.username, row[0], sizeof(customer.username) - 1);
            strncpy(customer.name, row[1], sizeof(customer.name) - 1);
            strncpy(customer.email, row[2], sizeof(customer.email) - 1);
        }
        mysql_free_result(res);
    }
    mysql_close(conn);
    return customer;
}

int main() {
    const char* testUsernames[] = {"user1", "user2", "user3", "user4", "user5"};
    for (int i = 0; i < 5; ++i) {
        Customer customer = getCustomerInfo(testUsernames[i]);
        printf("Customer{username='%s', name='%s', email='%s'}\n", customer.username, customer.name, customer.email);
    }
    return 0;
}