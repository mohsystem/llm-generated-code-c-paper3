
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include <errno.h>

#define MAX_NAME_LENGTH 256
#define MAX_DESC_LENGTH 1024
#define MAX_INPUT_LENGTH 32

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    double price;
    char description[MAX_DESC_LENGTH];
} Product;

typedef struct {
    MYSQL* conn;
} Task137;

void init_task(Task137* task) {
    task->conn = mysql_init(NULL);
    if (!task->conn) {
        fprintf(stderr, "Failed to initialize MySQL connection\\n");
        exit(1);
    }

    if (!mysql_real_connect(task->conn, "localhost", "user", "password", 
                           "productdb", 3306, NULL, 0)) {
        fprintf(stderr, "Failed to connect to database: %s\\n", mysql_error(task->conn));
        mysql_close(task->conn);
        exit(1);
    }
}

void cleanup_task(Task137* task) {
    if (task->conn) {
        mysql_close(task->conn);
        task->conn = NULL;
    }
}

bool get_product_details(Task137* task, int product_id, Product* product) {
    if (!task || !product || product_id <= 0) {
        return false;
    }

    MYSQL_STMT* stmt = mysql_stmt_init(task->conn);
    if (!stmt) {
        fprintf(stderr, "Failed to initialize statement\\n");
        return false;
    }

    const char* query = "SELECT * FROM products WHERE product_id = ?";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "Failed to prepare statement: %s\\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return false;
    }

    MYSQL_BIND bind_param[1];
    memset(bind_param, 0, sizeof(bind_param));
    bind_param[0].buffer_type = MYSQL_TYPE_LONG;
    bind_param[0].buffer = &product_id;

    if (mysql_stmt_bind_param(stmt, bind_param)) {
        fprintf(stderr, "Failed to bind parameters: %s\\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return false;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Failed to execute statement: %s\\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return false;
    }

    MYSQL_BIND bind_result[4];
    unsigned long name_length, desc_length;
    my_bool is_null[4];
    memset(bind_result, 0, sizeof(bind_result));

    bind_result[0].buffer_type = MYSQL_TYPE_LONG;
    bind_result[0].buffer = &product->id;
    bind_result[0].is_null = &is_null[0];

    bind_result[1].buffer_type = MYSQL_TYPE_STRING;
    bind_result[1].buffer = product->name;
    bind_result[1].buffer_length = MAX_NAME_LENGTH;
    bind_result[1].length = &name_length;
    bind_result[1].is_null = &is_null[1];

    bind_result[2].buffer_type = MYSQL_TYPE_DOUBLE;
    bind_result[2].buffer = &product->price;
    bind_result[', type='text')