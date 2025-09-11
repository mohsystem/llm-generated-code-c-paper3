#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    char username[50];
    char name[50];
    char email[50];
} Customer;

Customer* getCustomerInfo(const char* customerUsername) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    mysql_real_connect(conn, "localhost", "your_user", "your_password", "your_database", 0, NULL, 0);

    char query[256];
    snprintf(query, sizeof(query), "SELECT username, name, email FROM customer WHERE username = '%s'", customerUsername);
    mysql_query(conn, query);
    res = mysql_store_result(conn);

    Customer *customer = NULL;
    if ((row = mysql_fetch_row(res)) != NULL) {
        customer = (Customer*)malloc(sizeof(Customer));
        strcpy(customer->username, row[0]);
        strcpy(customer->name, row[1]);
        strcpy(customer->email, row[2]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return customer;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please provide a customer username.\n");
        return 1;
    }

    Customer* customer = getCustomerInfo(argv[1]);
    if (customer) {
        printf("Customer(username='%s', name='%s', email='%s')\n", customer->username, customer->name, customer->email);
        free(customer);
    } else {
        printf("Customer not found.\n");
    }

    return 0;
}