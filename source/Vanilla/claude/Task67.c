
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

struct Customer {
    int id;
    char username[50];
    char name[100];
    char email[100];
    char phone[20];
};

struct Customer* getCustomerInfo(const char* customerUsername) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    struct Customer* customer = NULL;
    
    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("MySQL initialization failed\\n");
        return NULL;
    }
    
    if (!mysql_real_connect(conn, "localhost", "root", "password", 
                           "customerdb", 0, NULL, 0)) {
        printf("Connection Error: %s\\n", mysql_error(conn));
        return NULL;
    }
    
    char query[200];
    snprintf(query, sizeof(query), "SELECT * FROM customer WHERE username = '%s'", 
             customerUsername);
    
    if (mysql_query(conn, query)) {
        printf("Query Error: %s\\n", mysql_error(conn));
        return NULL;
    }
    
    res = mysql_use_result(conn);
    if ((row = mysql_fetch_row(res)) != NULL) {
        customer = (struct Customer*)malloc(sizeof(struct Customer));
        customer->id = atoi(row[0]);
        strncpy(customer->username, row[1], sizeof(customer->username) - 1);
        strncpy(customer->name, row[2], sizeof(customer->name) - 1);
        strncpy(customer->email, row[3], sizeof(customer->email) - 1);
        strncpy(customer->phone, row[4], sizeof(customer->phone) - 1);
    }
    
    mysql_free_result(res);
    mysql_close(conn);
    
    return customer;
}

int main() {
    const char* testUsernames[] = {
        "john123",
        "mary456",
        "peter789",
        "sarah321",
        "mike654"
    };
    
    for(int i = 0; i < 5; i++) {
        struct Customer* customer = getCustomerInfo(testUsernames[i]);
        if(customer != NULL) {
            printf("Customer found:\\n");
            printf("ID: %d\\n", customer->id);
            printf("Username: %s\\n", customer->username);
            printf("Name: %s\\n", customer->name);
            printf("Email: %s\\n", customer->email);
            printf("Phone: %s\\n", customer->phone);
            free(customer);
        } else {
            printf("No customer found with username: %s\\n", testUsernames[i]);
        }
        printf("------------------------\\n");
    }
    
    return 0;
}
