#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>

char* hashPassword(const char* password) {
    // In a real application, use a secure hashing algorithm like bcrypt or PBKDF2
    return strdup(password); // Replace with actual hashing logic
}

int main() {
    char name[100], email[100], password[100];
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline character

    printf("Enter your email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0; // Remove newline character

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    MYSQL* conn;
    conn = mysql_init(0);
    if (!mysql_real_connect(conn, "localhost", "root", "", "user-registration", 0, NULL, 0)) {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(conn));
        return 1;
    }

    char* hashedPassword = hashPassword(password);
    char query[300];
    sprintf(query, "INSERT INTO users (name, email, password) VALUES ('%s', '%s', '%s')", name, email, hashedPassword);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error registering user: %s\n", mysql_error(conn));
    } else {
        printf("User registered successfully\n");
    }

    mysql_close(conn);
    free(hashedPassword);
    return 0;
}