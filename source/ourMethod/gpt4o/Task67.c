#include <stdio.h>
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

    const char *server = "localhost";
    const char *user = "yourusername";
    const char *password = "yourpassword";
    const char *database = "yourdatabase";

    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, server, user, password, database, 0, NULL, 0) == NULL) {
        mysql_close(conn);
        return NULL;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT username, name, email FROM customer WHERE username = '%s'", customerUsername);
    if (mysql_query(conn, query)) {
        mysql_close(conn);
        return NULL;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        mysql_close(conn);
        return NULL;
    }

    if ((row = mysql_fetch_row(res)) != NULL) {
        Customer *customer = malloc(sizeof(Customer));
        snprintf(customer->username, sizeof(customer->username), "%s", row[0]);
        snprintf(customer->name, sizeof(customer->name), "%s", row[1]);
        snprintf(customer->email, sizeof(customer->email), "%s", row[2]);
        mysql_free_result(res);
        mysql_close(conn);
        return customer;
    }

    mysql_free_result(res);
    mysql_close(conn);
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Please provide a customer username.\n");
        return 1;
    }

    Customer* customer = getCustomerInfo(argv[1]);
    if (customer) {
        printf("Customer{username='%s', name='%s', email='%s'}\n", customer->username, customer->name, customer->email);
        free(customer);
    } else {
        printf("Customer not found.\n");
    }

    return 0;
}