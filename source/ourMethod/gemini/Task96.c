#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    char buffer[1024];
    int bytes_received;

    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        send(client_socket, buffer, bytes_received, 0);
    }

    close(client_socket);
    free(arg); // Free the dynamically allocated memory
    pthread_exit(NULL); // Terminate the thread
}

void echo_server(int port) {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Error creating socket");
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Error binding");
        return;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Error listening");
        return;
    }

    printf("Server started on port %d\n", port);

    while (true) {
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Error accepting");
            continue;
        }
        printf("Client connected: %s\n", inet_ntoa(address.sin_addr));

        pthread_t client_thread;
        int *client_socket_ptr = (int *)malloc(sizeof(int)); // Allocate memory for client_socket
        if (client_socket_ptr == NULL) {
            perror("malloc failed");
            close(client_socket);
            continue;
        }
        *client_socket_ptr = client_socket;

        if (pthread_create(&client_thread, NULL, handle_client, client_socket_ptr) != 0) {
            perror("Error creating thread");
            close(client_socket);
            free(client_socket_ptr);
            continue;
        }
        pthread_detach(client_thread);
    }
    close(server_fd);
}

int main() {
    echo_server(8083);
    return 0;
}