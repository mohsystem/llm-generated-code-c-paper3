
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "user"
#define PASS "password"
#define DB "products_db"
#define PORT 3306

char* getProductDetails(int productId) {
    MYSQL* conn = mysql_init(NULL);
    char* result = malloc(256); // Allocate memory for result
    
    if (!mysql_real_connect(conn, HOST, USER, PASS, DB, PORT, NULL, 0)) {
        snprintf(result, 256, "Database connection error: %s", mysql_error(conn));
        mysql_close(conn);
        return result;
    }

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if (!stmt) {
        strcpy(result, "Statement initialization failed");
        mysql_close(conn);
        return result;
    }

    const char* query = "SELECT * FROM products WHERE product_id = ?";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        snprintf(result, 256, "Statement preparation failed: %s", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return result;
    }

    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));
    
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &productId;
    
    if (mysql_stmt_bind_param(stmt, bind)) {
        strcpy(result, "Parameter binding failed");
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return result;
    }

    if (mysql_stmt_execute(stmt)) {
        strcpy(result, "Statement execution failed");
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return result;
    }

    MYSQL_RES* prepare_meta_result = mysql_stmt_result_metadata(stmt);
    if (!prepare_meta_result) {
        strcpy(result, "No results found");
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return result;
    }

    int id;
    char name[50];
    double price;
    MYSQL_BIND result_bind[3];
    memset(result_bind, 0, sizeof(result_bind));

    result_bind[0].buffer_type = MYSQL_TYPE_LONG;
    result_bind[0].buffer = &id;
    
    result_bind[1].buffer_type = MYSQL_TYPE_STRING;
    result_bind[1].buffer = name;
    result_bind[1].buffer_length = sizeof(name);
    
    result_bind[2].buffer_type = MYSQL_TYPE_DOUBLE;
    result_bind[2].buffer = &price;

    if (mysql_stmt_bind_result(stmt, result_bind)) {
        strcpy(result, "Result binding failed");
        mysql_free_result(prepare_meta_result);
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return result;
    }

    if (mysql_stmt_fetch(stmt)) {
        strcpy(result, "Product not found");
        mysql_free_result(prepare_meta_result);
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return result;
    }

    snprintf(result, 256, "Product ID: %d, Name: %s, Price: %.2f", id, name, price);

    mysql_free_result(prepare_meta_result);
    mysql_stmt_close(stmt);
    mysql_close(conn);
    
    return result;
}

int main() {
    // Test cases
    printf("%s\\n", getProductDetails(1));  // Assuming product exists
    printf("%s\\n", getProductDetails(2));  // Assuming product exists
    printf("%s\\n", getProductDetails(3));  // Assuming product exists
    printf("%s\\n", getProductDetails(-1)); // Invalid product id
    printf("%s\\n", getProductDetails(999)); // Non-existent product
    
    return 0;
}
