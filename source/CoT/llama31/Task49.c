// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void create_user(const char *name, const char *email) {
    sqlite3 *db;
    sqlite3_open("users.db", &db);
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO users (name, email) VALUES (?, ?)";
    sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    // Simulate HTTP request handling (this is very simplified)
    const char *request = "POST /user HTTP/1.1\r\nContent-Type: application/json\r\n\r\n{\"name\":\"John\",\"email\":\"john@example.com\"}";
    const char *json = strstr(request, "{\"name\":\"");
    if (json) {
        json += 8; // Skip "{\"name\":\""
        const char *nameEnd = strstr(json, "\",\"email\":\"");
        const char *email = strstr(nameEnd, "\"");
        email += 1; // Skip the first quote
        const char *emailEnd = strstr(email, "\"");
        char name[1024];
        char emailStr[1024];
        strncpy(name, json, nameEnd - json);
        name[nameEnd - json] = '\0';
        strncpy(emailStr, email, emailEnd - email);
        emailStr[emailEnd - email] = '\0';
        create_user(name, emailStr);
        printf("User created successfully\n");
    }
    return 0;
}