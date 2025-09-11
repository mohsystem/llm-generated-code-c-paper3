#include <mysql.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    MYSQL *con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    if (mysql_real_connect(con, "localhost", "username", "password", "mydb", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    char query[256];
    sprintf(query, "SELECT * FROM customer WHERE customerusername = '%s'", argv[1]);
    if (mysql_query(con, query)) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    if (mysql_num_rows(result) == 0) {
        printf("No customer found with username: %s\n", argv[1]);
    } else {
        // fetch relevant information and create structured data or object
    }
    mysql_free_result(result);
    mysql_close(con);
    return 0;
}