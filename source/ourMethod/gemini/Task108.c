#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 12345
#define MAX_OBJECTS 100
#define MAX_NAME_LENGTH 50
#define MAX_VALUE_LENGTH 100


typedef struct {
    char name[MAX_NAME_LENGTH];
    char value[MAX_VALUE_LENGTH];
} Object;

Object objects[MAX_OBJECTS];
int num_objects = 0;

void* handle_client(void* arg) {
    int client_fd = *(int*)arg;
    free(arg);

    char buffer[1024];
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0) {
            break;
        }
        
        char command[MAX_NAME_LENGTH], name[MAX_NAME_LENGTH], value[MAX_VALUE_LENGTH];
        sscanf(buffer, "%s %s", command, name);


        if (strcmp(command, "create") == 0 || strcmp(command, "set") == 0) {
           
            char *val_start = strchr(buffer, ' ') + 1;
            val_start = strchr(val_start, ' ') + 1;
            strcpy(value, val_start);

            int object_index = -1;
            for (int i = 0; i < num_objects; i++) {
                if (strcmp(objects[i].name, name) == 0) {
                    object_index = i;
                    break;
                }
            }

            if (object_index == -1) {
                if (num_objects < MAX_OBJECTS) {
                    strcpy(objects[num_objects].name, name);
                    strcpy(objects[num_objects].value, value);
                    num_objects++;
                }
            } else {
                strcpy(objects[object_index].value, value);
            }
            write(client_fd, "OK\n", 3);
        } else if (strcmp(command, "get") == 0) {
            int object_index = -1;
            for (int i = 0; i < num_objects; i++) {
                if (strcmp(objects[i].name, name) == 0) {
                    object_index = i;
                    break;
                }
            }
            if (object_index != -1) {
                write(client_fd, objects[object_index].value, strlen(objects[object_index].value));
                write(client_fd, "\n", 1);
            } else {
                write(client_fd, "Not Found\n", 10);
            }
        } else if (strcmp(command, "delete") == 0) {
            for (int i = 0; i < num_objects; i++) {
                if (strcmp(objects[i].name, name) == 0) {
                    
                    for (int j = i; j < num_objects - 1; j++) {
                        objects[j] = objects[j + 1];
                    }
                    num_objects--;
                    break;
                }
            }
            write(client_fd, "OK\n", 3);
        } else {
            write(client_fd, "Invalid Command\n", 16);
        }

    }
    close(client_fd);
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

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server started on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        int *client_fd_ptr = (int*)malloc(sizeof(int));
        *client_fd_ptr = new_socket;
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, (void*)client_fd_ptr);


    }
    return 0;
}