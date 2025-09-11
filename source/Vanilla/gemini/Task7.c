#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_USERS 100
#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 50

typedef struct {
    char username[USERNAME_MAX_LEN + 1];
    char password[PASSWORD_MAX_LEN + 1];
} User;


User users[MAX_USERS];
int num_users = 0;
pthread_mutex_t users_mutex = PTHREAD_MUTEX_INITIALIZER;

void* client_thread(void* arg);
void* server_thread(void* arg);


int main() {
    pthread_t server_tid;
    pthread_create(&server_tid, NULL, server_thread, NULL);
    pthread_detach(server_tid);


    strcpy(users[0].username, "user1");
    strcpy(users[0].password, "pass1");
    strcpy(users[1].username, "user2");
    strcpy(users[1].password, "pass2");
    num_users=2;


    // Test client connections (replace with your actual client implementation)
    char username[USERNAME_MAX_LEN + 1];
    char password[PASSWORD_MAX_LEN + 1];

    strcpy(username, "user1");
    strcpy(password, "pass1");
    client_thread((void*)username);

    strcpy(username, "user2");
    strcpy(password, "wrongpass");
    client_thread((void*)username);

    strcpy(username, "invaliduser");
    strcpy(password, "pass");
    client_thread((void*)username);
    
    strcpy(username, "user2");
    strcpy(password, "pass2");
    client_thread((void*)username);

    strcpy(username, "user1");
    strcpy(password, "wrongpass");
    client_thread((void*)username);




    // Keep main thread running (you might want to handle this differently in a real application)
    while (1) {
        sleep(1);
    }

    return 0;
}


void* client_thread(void* arg) {
    char username[USERNAME_MAX_LEN + 1];
    strcpy(username, (char *)arg);
    char password[PASSWORD_MAX_LEN+1]; // Assuming password is passed somehow
    // ... (Get password)


    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket creation failed");
        return NULL;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);  // Server port

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {  // Server IP
        perror("Invalid address/ Address not supported");
        return NULL;
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return NULL;
    }

    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "LOGIN %s %s\n", username, password);
    send(sock, buffer, strlen(buffer), 0);

    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Client received: %s", buffer);

    close(sock);

    return NULL;
}




void* server_thread(void* arg) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};


    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( 5000 );

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        pthread_t client_tid;
        pthread_create(&client_tid, NULL, client_thread, (void*)&new_socket);
        pthread_detach(client_tid); 
    }

    return NULL;
}


void* handle_client(void* arg) {

    int new_socket = *(int*)arg;
    char buffer[1024] = {0};
    read(new_socket , buffer, 1024);
    printf("Server received: %s\n",buffer);

    char command[10], username[50], password[50];
    sscanf(buffer, "%s %s %s", command, username, password);

    if (strcmp(command, "LOGIN") == 0) {
        int authenticated = 0;

        pthread_mutex_lock(&users_mutex);  // Protect access to the users array
        for(int i=0; i< num_users; ++i){
            if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
                authenticated = 1;
                break;
            }
        }
        pthread_mutex_unlock(&users_mutex);

        if (authenticated) {
            send(new_socket , "Login successful.\n" , strlen("Login successful.\n") , 0 );
        } else {
            send(new_socket , "Login failed.\n" , strlen("Login failed.\n") , 0 );
        }
    }


    close(new_socket);
    return NULL;
}