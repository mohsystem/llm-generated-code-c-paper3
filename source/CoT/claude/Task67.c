
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_STRING_LENGTH 100

struct Customer {
    int id;
    char username[MAX_STRING_LENGTH];
    char firstName[MAX_STRING_LENGTH];
    char lastName[MAX_STRING_LENGTH];
    char email[MAX_STRING_LENGTH];
};

const char* DB_HOST = "localhost";
const char* DB_USER = "dbuser";
const char* DB_PASS = "dbpassword";
const char* DB_NAME = "customerdb";

void print_customer(const struct Customer* customer) {
    printf("Customer{id=%d, username='%s', firstName='%s', lastName='%s', email='%s'}\\n",
           customer->id, customer->username, customer->firstName, 
           customer->lastName, customer->email);
}

struct Customer* get_customer_info(const char* username, char* error_msg) {
    if (!username || strlen(username) == 0) {
        strcpy(error_msg, "Username cannot be empty");
        return NULL;
    }

    MYSQL* conn = mysql_init(NULL);
    if (!conn) {
        strcpy(error_msg, "Failed to initialize MySQL connection");
        return NULL;
    }

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        snprintf(error_msg, MAX_STRING_LENGTH, "Failed to connect to database: %s", 
                 mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if (!stmt) {
        strcpy(error_msg, "Failed to initialize statement");
        mysql_close(conn);
        return NULL;
    }

    const char* sql = "SELECT id, customerusername, firstname, lastname, email "
                     "FROM customer WHERE customerusername = ?";
                     
    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        snprintf(error_msg, MAX_STRING_LENGTH, "Failed to prepare statement: %s",
                 mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return NULL;
    }

    MYSQL_BIND bind_param[1];
    memset(bind_param, 0, sizeof(bind_param));
    
    unsigned long username_length = strlen(username);
    bind_param[0].buffer_type = MYSQL_TYPE_STRING;
    bind_param[0].buffer = (void*)username;
    bind_param[0].buffer_length = username_length;

    if (mysql_stmt_bind_param(stmt, bind_param)) {
        snprintf(error_msg, MAX_STRING_LENGTH, "Failed to bind parameters: %s",
                 mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return NULL;
    }

    if (mysql_stmt_execute(stmt)) {
        snprintf(error_msg, MAX_STRING_LENGTH, "Failed to execute statement: %s",
                 mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return NULL;
    }

    struct Customer* customer = malloc(sizeof(struct Customer));
    if (!customer) {
        strcpy(error_msg, "Memory allocation failed");
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return NULL;
    }

    MYSQL_BIND bind_result[5];
    unsigned long length[5];
    //  //todo    //incomplete code
    // memset(bind_result, 0, sizeof(bind_', type='text')
}