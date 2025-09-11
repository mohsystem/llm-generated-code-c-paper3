#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 12345
#define MAX_CLIENTS 100

typedef struct {
    int sockfd;
    char username[100];
} Client;


Client clients[MAX_CLIENTS];
int num_clients = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast(char *message, int sender_sockfd) {

    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < num_clients; i++) {
        if (clients[i].sockfd != sender_sockfd) {

            if (send(clients[i].sockfd, message, strlen(message), 0) == -1) {

            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}


void *handle_client(void *arg) {
    Client client = *(Client *)arg;
    char buffer[1024];
    int bytes_received;


    while ((bytes_received = recv(client.sockfd, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytes_received] = '\0';
        char message[1024 + 100];


        snprintf(message, sizeof(message), "%s: %s\n", client.username, buffer);
        broadcast(message, client.sockfd);
    }



    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < num_clients; i++) {
        if (clients[i].sockfd == client.sockfd) {

            for (int j = i; j < num_clients - 1; j++) {
                clients[j] = clients[j + 1];
            }
            num_clients--;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);


    char left_message[1024];
    snprintf(left_message, sizeof(left_message), "%s has left the chat.\n", client.username);
    broadcast(left_message, client.sockfd);
    close(client.sockfd);
    free(arg);

    pthread_exit(NULL);
}

int main() {
    int server_fd, new_socket;
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
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Chat server started on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        Client *new_client = (Client *)malloc(sizeof(Client));
        new_client->sockfd = new_socket;

        int bytes_received = recv(new_socket, new_client->username, sizeof(new_client->username) -1, 0);
        if (bytes_received <= 0) {
            perror("recv failed");
            free(new_client);
            continue;
        }
        new_client->username[bytes_received] = '\0';


        char join_message[1024];
        snprintf(join_message, sizeof(join_message), "%s has joined the chat!\n", new_client->username);
        broadcast(join_message, new_socket);


        pthread_mutex_lock(&clients_mutex);
        if (num_clients < MAX_CLIENTS) {
            clients[num_clients++] = *new_client;
        }
        pthread_mutex_unlock(&clients_mutex);



        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, new_client);


    }

    return 0;
}