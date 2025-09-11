
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_NAME_LEN 50
#define MAX_EMAIL_LEN 100

typedef struct {
    int id;
    char username[MAX_USERNAME_LEN];
    char firstname[MAX_NAME_LEN];
    char lastname[MAX_NAME_LEN];
    char email[MAX_EMAIL_LEN];
} Customer;

#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_PASSWORD "password"
#define DB_NAME "customerdb"
#define DB_PORT 3306

Customer* get_customer_by_username(const char* username, int* error_code) {
    *error_code = 0;
    
    // Validate input
    if (!username || strlen(username) == 0 || strlen(username) >= MAX_USERNAME_LEN) {
        *error_code = 1;
        return NULL;
    }

    MYSQL* conn = mysql_init(NULL);
    if (!conn) {
        *error_code = 2;
        return NULL;
    }

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, DB_PORT, NULL, 0)) {
        mysql_close(conn);
        *error_code = 3;
        return NULL;
    }

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if (!stmt) {
        mysql_close(conn);
        *error_code = 4;
        return NULL;
    }

    const char* query = "SELECT id, username, firstname, lastname, email FROM customer WHERE username = ?";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        *error_code = 5;
        return NULL;
    }

    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));
    
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (void*)username;
    bind[0].buffer_length = strlen(username);

    if (mysql_stmt_bind_param(stmt, bind)) {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        *error_code = 6;
        return NULL;
    }

    if (mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        *error_code = 7;
        return NULL;
    }

    Customer* customer = (Customer*)malloc(sizeof(Customer));
    if (!customer) {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        *error_code = 8;
        return NULL;
    }

    MYSQL_BIND result[5];
    memset(result, 0, sizeof(result));
    unsigned long lengths[5];

    result[0].buffer_type = MYSQL_TYPE_LONG;
    result[0].buffer = &customer->id;

    result[1].buffer_type = MYSQL_TYPE_STRING;
    result[1].buffer = customer->username;
    result[1].buffer_length = MAX_USERNAME_LEN;
    result[1].length = &lengths[1];

    result[2].buffer_type = MYSQL_TYPE_STRING;
    result[2].buffer = customer->firstname;
    result[2].buffer_length = MAX_NAME_LEN;
    result[2].length = &lengths[2];

    result[3].buffer_type = MYSQL_TYPE_STRING;
    result[3].buffer = customer->lastname;
    result[3].buffer_length = MAX_NAME_LEN;
    result[3].length = &lengths[3];

    result[4].buffer_type = MYSQL_TYPE_STRING;
    result[4].buffer = customer->email;
    result[4].buffer_length = MAX_EMAIL_LEN;
    result[4].length = &lengths[4];

    if (mysql_stmt_bind_result(stmt, result)) {
        free(customer);
        mysql_stmt_close(stmt);
        mysql_close(conn);
        *error_code = 9;
        return NULL;
    }

    int fetch_result = mysql_stmt_fetch(stmt);
    if (fetch_result == 1 || fetch_result == MYSQL_NO_DATA) {
        free(customer);
        customer = NULL;
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);
    
    return customer;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Please provide customer username as argument\\n");
        return 1;
    }

    int error_code;
    Customer* customer = get_customer_by_username(argv[1], &error_code);

    if (error_code != 0) {
        printf("Error occurred with code: %d\\n", error_code);
        return 1;
    }

    if (customer) {
        printf("Customer found: ID: %d, Username: %s, Name: %s %s, Email: %s\\n",
               customer->id, customer->username, customer->firstname, 
               customer->lastname, customer->email);
        free(customer);
    } else {
        printf("', type='text')