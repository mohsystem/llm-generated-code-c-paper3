#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12345
#define BUFFER_SIZE 1024

typedef struct {
    int sock;
    struct sockaddr address;
    socklen_t addr_len;
} connection_t;

const char* users[][2] = {{"user1", "pass1"}, {"user2", "pass2"}};

void *handle_client(void *ptr) {
    char buffer[BUFFER_SIZE];
    connection_t *conn;
    long addr = 0;

    if (!ptr) pthread_exit(0);
    conn = (connection_t *)ptr;

    read(conn->sock, buffer, BUFFER_SIZE);
    char* username = strtok(buffer, " ");
    char* password = strtok(NULL, " ");

    int success = 0;
    for (int i = 0; i < 2; ++i) {
        if (strcmp(users[i][0], username) == 0 && strcmp(users[i][1], password) == 0) {
            success = 1;
            break;
        }
    }

    if (success) {
        write(conn->sock, "success", strlen("success"));
    } else {
        write(conn->sock, "failure", strlen("failure"));
    }

    close(conn->sock);
    free(conn);
    pthread_exit(0);
}

void start_server() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    connection_t *connection;
    pthread_t thread;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(sock, (struct sockaddr *)&address, sizeof(address));
    listen(sock, 5);

    while (1) {
        connection = (connection_t *)malloc(sizeof(connection_t));
        connection->sock = accept(sock, &connection->address, &connection->addr_len);
        pthread_create(&thread, 0, handle_client, (void *)connection);
        pthread_detach(thread);
    }
}

int login(const char* username, const char* password) {
    int sock;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect failed");
        return 0;
    }

    snprintf(buffer, BUFFER_SIZE, "%s %s", username, password);
    write(sock, buffer, strlen(buffer));

    read(sock, buffer, BUFFER_SIZE);
    close(sock);

    return strcmp(buffer, "success") == 0;
}

int main() {
    pthread_t server_thread;
    pthread_create(&server_thread, NULL, (void *)start_server, NULL);
    sleep(1); // Give server a moment to start

    // Test cases
    printf("%d\n", login("user1", "pass1")); // 1
    printf("%d\n", login("user2", "wrong")); // 0
    printf("%d\n", login("user3", "pass3")); // 0
    printf("%d\n", login("user1", "pass2")); // 0
    printf("%d\n", login("user2", "pass2")); // 1

    pthread_join(server_thread, NULL);
    return 0;
}