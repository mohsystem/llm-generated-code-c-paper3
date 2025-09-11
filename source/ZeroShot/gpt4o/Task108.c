#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 9090
#define BUFFER_SIZE 1024

pthread_mutex_t lock;
char* objects[100][2];  // Simple key-value store
int object_count = 0;

void* handle_client(void* client_socket_ptr) {
    int client_socket = *(int*)client_socket_ptr;
    free(client_socket_ptr);
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);

    char* response = "Invalid Command";
    char action[10], key[50], value[50];
    sscanf(buffer, "%s %s %s", action, key, value);

    pthread_mutex_lock(&lock);
    if (strcmp(action, "get") == 0) {
        for (int i = 0; i < object_count; i++) {
            if (strcmp(objects[i][0], key) == 0) {
                response = objects[i][1];
                break;
            }
        }
    } else if (strcmp(action, "set") == 0) {
        int found = 0;
        for (int i = 0; i < object_count; i++) {
            if (strcmp(objects[i][0], key) == 0) {
                objects[i][1] = strdup(value);
                found = 1;
                response = "OK";
                break;
            }
        }
        if (!found && object_count < 100) {
            objects[object_count][0] = strdup(key);
            objects[object_count][1] = strdup(value);
            object_count++;
            response = "OK";
        }
    } else if (strcmp(action, "delete") == 0) {
        for (int i = 0; i < object_count; i++) {
            if (strcmp(objects[i][0], key) == 0) {
                for (int j = i; j < object_count - 1; j++) {
                    objects[j][0] = objects[j + 1][0];
                    objects[j][1] = objects[j + 1][1];
                }
                object_count--;
                response = "Deleted";
                break;
            }
        }
    }
    pthread_mutex_unlock(&lock);

    send(client_socket, response, strlen(response), 0);
    close(client_socket);
    return NULL;
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    pthread_mutex_init(&lock, NULL);

    while (1) {
        int* client_socket = malloc(sizeof(int));
        *client_socket = accept(server_fd, NULL, NULL);
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, client_socket);
        pthread_detach(thread_id);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}