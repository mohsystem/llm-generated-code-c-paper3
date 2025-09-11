#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <openssl/sha.h>

#define PORT 5000
#define MAX_CONN 5

typedef struct {
    char *username;
    char *password_hash;
} User;

User userDatabase[MAX_CONN];

void initializeUserDatabase() {
    for (int i = 0; i < MAX_CONN; i++) {
        userDatabase[i].username = (char *)malloc(6);
        sprintf(userDatabase[i].username, "user%d", i + 1);

        char password[10];
        sprintf(password, "password%d", i + 1);

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char *)password, strlen(password), hash);
        userDatabase[i].password_hash = (char *)malloc(SHA256_DIGEST_LENGTH);
        memcpy(userDatabase[i].password_hash, hash, SHA256_DIGEST_LENGTH);
    }
}

void hashPassword(const char *password, unsigned char *outputBuffer) {
    SHA256((unsigned char *)password, strlen(password), outputBuffer);
}

void *clientHandler(void *socket_desc) {
    int sock = *(int *)socket_desc;
    free(socket_desc);

    char client_message[2000];
    int read_size;
    if ((read_size = recv(sock, client_message, 2000, 0)) > 0) {
        client_message[read_size] = '\0';

        char *username = strtok(client_message, ":");
        char *password_hash = strtok(NULL, ":");

        int found = 0;
        for (int i = 0; i < MAX_CONN; i++) {
            if (strcmp(userDatabase[i].username, username) == 0) {
                if (memcmp(userDatabase[i].password_hash, password_hash, SHA256_DIGEST_LENGTH) == 0) {
                    write(sock, "Login successful\n", 17);
                    found = 1;
                    break;
                }
            }
        }
        if (!found) {
            write(sock, "Login failed\n", 13);
        }
    } else {
        write(sock, "Invalid message format\n", 23);
    }

    close(sock);
    return 0;
}

void *server(void *arg) {
    int server_fd, new_socket, *new_sock;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = new_socket;
        if (pthread_create(&sniffer_thread, NULL, clientHandler, (void*)new_sock) < 0) {
            perror("could not create thread");
            return NULL;
        }
        pthread_detach(sniffer_thread);
    }

    if (new_socket < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    return NULL;
}

void client(const char *username, const char *password) {
    int sock;
    struct sockaddr_in server;
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    char message[100];

    hashPassword(password, hashed_password);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect failed");
        return;
    }

    sprintf(message, "%s:%s", username, hashed_password);
    if (send(sock, message, strlen(message), 0) < 0) {
        puts("Send failed");
        return;
    }

    char server_reply[2000];
    if (recv(sock, server_reply, 2000, 0) > 0) {
        puts(server_reply);
    }

    close(sock);
}

int main() {
    initializeUserDatabase();
    
    pthread_t server_thread;
    pthread_create(&server_thread, NULL, server, NULL);

    sleep(1);

    // Sample test cases
    client("user1", "password1");
    client("user2", "password2");
    client("user3", "password3");
    client("user4", "password4");
    client("user5", "password5");

    pthread_join(server_thread, NULL);
    return 0;
}