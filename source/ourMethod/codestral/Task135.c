// C does not have built-in servlet classes, so this example uses the libev library instead
#include <ev.h>
#include <openssl/rand.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8080
#define BACKLOG 10
#define BUFFER_SIZE 4096

void generate_csrf_token(char* token) {
    unsigned char random_bytes[16];
    RAND_bytes(random_bytes, sizeof(random_bytes));
    for (size_t i = 0; i < sizeof(random_bytes); ++i) {
        sprintf(token + (i * 2), "%02x", random_bytes[i]);
    }
}

int is_csrf_token_valid(const char* request, const char* session_token) {
    const char* cookie_header = strstr(request, "Cookie: ");
    if (cookie_header != NULL) {
        const char* csrf_token_start = strstr(cookie_header, "csrf_token=");
        if (csrf_token_start != NULL) {
            char* csrf_token_end = strchr(csrf_token_start, ';');
            if (csrf_token_end == NULL) {
                csrf_token_end = strchr(csrf_token_start, '\r');
            }
            if (csrf_token_end != NULL) {
                size_t token_length = csrf_token_end - csrf_token_start - 11;
                char request_token[33];
                strncpy(request_token, csrf_token_start + 11, token_length);
                request_token[token_length] = '\0';
                if (strcmp(session_token, request_token) == 0) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void handle_request(EV_P_ ev_io* watcher, int revents) {
    int client_socket = watcher->fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received <= 0) {
        ev_io_stop(EV_A_ watcher);
        close(client_socket);
        return;
    }

    char csrf_token[33];
    if (strncmp(buffer, "GET /", 5) == 0) {
        generate_csrf_token(csrf_token);
        char response[256];
        sprintf(response, "HTTP/1.1 200 OK\r\nSet-Cookie: csrf_token=%s\r\n\r\n", csrf_token);
        send(client_socket, response, strlen(response), 0);
    } else if (strncmp(buffer, "POST /", 6) == 0) {
        if (is_csrf_token_valid(buffer, csrf_token)) {
            // Process the form submission
            const char* response = "HTTP/1.1 200 OK\r\n\r\nForm submitted successfully";
            send(client_socket, response, strlen(response), 0);
        } else {
            // Reject the form submission
            const char* response = "HTTP/1.1 403 Forbidden\r\n\r\nInvalid CSRF token";
            send(client_socket, response, strlen(response), 0);
        }
    }
}

void accept_connection(EV_P_ ev_io* watcher, int revents) {
    int server_socket = watcher->fd;
    int client_socket = accept(server_socket, NULL, NULL);
    if (client_socket < 0) {
        perror("accept");
        return;
    }

    ev_io* client_watcher = (ev_io*)malloc(sizeof(ev_io));
    ev_io_init(client_watcher, handle_request, client_socket, EV_READ);
    ev_io_start(EV_A_ client_watcher);
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        return 1;
    }

    if (listen(server_socket, BACKLOG) < 0) {
        perror("listen");
        return 1;
    }

    ev_io server_watcher;
    ev_io_init(&server_watcher, accept_connection, server_socket, EV_READ);
    ev_io_start(EV_DEFAULT, &server_watcher);

    ev_run(EV_DEFAULT, 0);

    return 0;
}