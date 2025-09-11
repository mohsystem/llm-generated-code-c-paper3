#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

typedef struct {
    char username[50];
    char password[50];
} User;

User userDatabase[] = {
    {"user1", "password1"},
    {"user2", "password2"}
};

void *handle_client(void *arg) {
    int clientSocket = *(int *)arg;
    char buffer[1024] = {0};
    read(clientSocket, buffer, 1024);

    char *token = strtok(buffer, ":");
    if (token && strcmp(token, "LOGIN") == 0) {
        char *username = strtok(NULL, ":");
        char *password = strtok(NULL, ":");
        int valid = 0;
        for (int i = 0; i < sizeof(userDatabase) / sizeof(User); i++) {
            if (username && password &&
                strcmp(userDatabase[i].username, username) == 0 &&
                strcmp(userDatabase[i].password, password) == 0) {
                valid = 1;
                break;
            }
        }
        if (valid) {
            send(clientSocket, "Login Successful", strlen("Login Successful"), 0);
        } else {
            send(clientSocket, "Invalid Credentials", strlen("Invalid Credentials"), 0);
        }
    } else {
        send(clientSocket, "Invalid Request", strlen("Invalid Request"), 0);
    }
    close(clientSocket);
    free(arg);
    return NULL;
}

void *start_server(void *arg) {
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(12345);

    bind(serverFd, (struct sockaddr *)&address, sizeof(address));
    listen(serverFd, 3);

    while (1) {
        int *clientSocket = malloc(sizeof(int));
        *clientSocket = accept(serverFd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        pthread_t threadId;
        pthread_create(&threadId, NULL, handle_client, clientSocket);
        pthread_detach(threadId);
    }
    return NULL;
}

void *client_run(void *arg) {
    char *credentials = (char *)arg;
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return NULL;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return NULL;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return NULL;
    }

    send(sock, credentials, strlen(credentials), 0);
    read(sock, buffer, 1024);
    printf("Server response: %s\n", buffer);
    close(sock);
    return NULL;
}

int main() {
    pthread_t serverThread;
    pthread_create(&serverThread, NULL, start_server, NULL);
    sleep(1); // Give server time to start

    char *test_cases[] = {
        "LOGIN:user1:password1",
        "LOGIN:user2:password2",
        "LOGIN:user1:wrongpassword",
        "LOGIN:user3:password3",
        "LOGIN:user2:password2"
    };

    pthread_t clientThreads[5];
    for (int i = 0; i < 5; i++) {
        pthread_create(&clientThreads[i], NULL, client_run, test_cases[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(clientThreads[i], NULL);
    }

    pthread_cancel(serverThread);
    return 0;
}