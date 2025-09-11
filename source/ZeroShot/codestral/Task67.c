#include <mysql.h>
#include <stdio.h>
#include <string.h>

struct Customer {
    int id;
    char name[50];
    char email[50];
    // add other fields as needed
};

struct Customer get_customer_info(const char* customer_username) {
    // replace with your database credentials
    MYSQL* con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "username", "password", "mydb", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    char query[100];
    sprintf(query, "SELECT * FROM customer WHERE username = '%s'", customer_username);

    if (mysql_query(con, query)) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    MYSQL_RES* result = mysql_store_result(con);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != NULL) {
        struct Customer customer;
        customer.id = atoi(row[0]);
        strcpy(customer.name, row[1]);
        strcpy(customer.email, row[2]);
        // set other fields as needed
        mysql_free_result(result);
        mysql_close(con);
        return customer;
    } else {
        mysql_free_result(result);
        mysql_close(con);
        return (struct Customer){0};
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please provide a customer username as a command line argument.\n");
        return 1;
    }

    const char* customer_username = argv[1];
    struct Customer customer = get_customer_info(customer_username);
    if (customer.id != 0) {
        printf("Customer ID: %d\n", customer.id);
        printf("Customer Name: %s\n", customer.name);
        printf("Customer Email: %s\n", customer.email);
        // print other fields as needed
    } else {
        printf("No customer found with the username: %s\n", customer_username);
    }

    return 0;
}