#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

typedef struct {
    int socket;
    char *username;
    char *password;
} client_args;

void *handle_client(void *arg) {
    client_args *args = (client_args *)arg;
    int client_socket = args->socket;
    char *username = args->username;
    char *password = args->password;
    free(arg);

    char buffer[1024];
    char *users[] = {"user1:pass1", "user2:pass2", "user3:pass3"};
    int user_count = 3;

    recv(client_socket, buffer, sizeof(buffer), 0);
    strtok(buffer, "\n");  // Remove newline character
    char *received_username = strdup(buffer);

    recv(client_socket, buffer, sizeof(buffer), 0);
    strtok(buffer, "\n");  // Remove newline character
    char *received_password = strdup(buffer);

    char response[50] = "Login failed\n";
    for (int i = 0; i < user_count; i++) {
        char *stored_username = strtok(users[i], ":");
        char *stored_password = strtok(NULL, ":");

        if (strcmp(received_username, stored_username) == 0 && strcmp(received_password, stored_password) == 0) {
            strcpy(response, "Login successful\n");
            break;
        }
    }

    send(client_socket, response, strlen(response), 0);
    close(client_socket);
    free(received_username);
    free(received_password);

    return NULL;
}

void server() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);
    printf("Server listening on port 12345\n");

    while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        pthread_t thread;
        client_args *args = malloc(sizeof(client_args));
        args->socket = client_socket;
        pthread_create(&thread, NULL, handle_client, args);
        pthread_detach(thread);
    }
}

void client(const char *username, const char *password) {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s\n", username);
    send(client_socket, buffer, strlen(buffer), 0);
    snprintf(buffer, sizeof(buffer), "%s\n", password);
    send(client_socket, buffer, strlen(buffer), 0);

    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("Client: %s", buffer);
    close(client_socket);
}

int main() {
    pthread_t server_thread;
    pthread_create(&server_thread, NULL, (void *(*)(void *))server, NULL);
    sleep(1); // Let the server start

    client("user1", "pass1");
    client("user2", "wrongpass");
    client("user1", "pass1");
    client("user3", "pass3");
    client("user4", "pass4");

    pthread_join(server_thread, NULL);
    return 0;
}