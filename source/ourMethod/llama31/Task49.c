#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_request(int client_socket, sqlite3* db) {
    char buffer[BUFFER_SIZE];
    recv(client_socket, buffer, BUFFER_SIZE, 0);

    // Simplified JSON parsing
    char* name = strstr(buffer, "name");
    char* email = strstr(buffer, "email");
    if (name == NULL || email == NULL) {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\n\r\nMissing required fields", strlen("HTTP/1.1 400 Bad Request\r\n\r\nMissing required fields"), 0);
        return;
    }

    name += 6; // Skip "name\":\""
    email += 7; // Skip "email\":\""

    char* name_end = strchr(name, '\"');
    char* email_end = strchr(email, '\"');

    if (name_end == NULL || email_end == NULL) {
        send(client_socket, "HTTP/1.1 400 Bad Request\r\n\r\nInvalid JSON", strlen("HTTP/1.1 400 Bad Request\r\n\r\nInvalid JSON"), 0);
        return;
    }

    *name_end = '\0';
    *email_end = '\0';

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, "INSERT INTO users (name, email) VALUES (?, ?)", -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    send(client_socket, "HTTP/1.1 201 Created\r\n\r\nUser created successfully", strlen("HTTP/1.1 201 Created\r\n\r\nUser created successfully"), 0);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, 3);

    sqlite3* db;
    sqlite3_open("users.db", &db);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        handle_request(client_socket, db);
        close(client_socket);
    }

    sqlite3_close(db);
    return 0;
}