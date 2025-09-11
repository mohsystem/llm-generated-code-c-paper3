// C
#include <mysql.h>
#include <stdio.h>

void getUserInfo(char* username) {
    MYSQL* con;
    MYSQL_ROW row;
    MYSQL_RES* res;

    con = mysql_init(0);

    if (con == NULL) {
        printf("Error: %s\n", mysql_error(con));
        return;
    }

    con = mysql_real_connect(con, "localhost", "username", "password", "mydatabase", 3306, NULL, 0);

    if (con == NULL) {
        printf("Error: %s\n", mysql_error(con));
        return;
    }

    char query[100];
    sprintf(query, "SELECT * FROM users WHERE username = '%s'", username);
    int qstate = mysql_query(con, query);

    if (qstate == 0) {
        res = mysql_store_result(con);
        while ((row = mysql_fetch_row(res))) {
            printf("%s %s\n", row[0], row[1]);
        }
    } else {
        printf("Query Error: %s\n", mysql_error(con));
    }

    mysql_close(con);
}

int main() {
    getUserInfo("test_user");
    return 0;
}