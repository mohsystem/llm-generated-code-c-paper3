#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

void* startCServer(void* arg) {
    int port = *(int*)arg;
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        pthread_exit(NULL);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        pthread_exit(NULL);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        pthread_exit(NULL);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        pthread_exit(NULL);
    }

    printf("C server listening on port %d\n", port);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            pthread_exit(NULL);
        }

        char buffer[1024] = {0};
        int valread = read(new_socket, buffer, 1024);
        if (valread > 0) {
            printf("Received: %s\n", buffer);
            send(new_socket, buffer, strlen(buffer), 0);
        }
        close(new_socket);
    }
}

int main() {
    pthread_t thread_id;
    int port = 5004;
    pthread_create(&thread_id, NULL, startCServer, (void*)&port);
    pthread_detach(thread_id);
    return 0;
}