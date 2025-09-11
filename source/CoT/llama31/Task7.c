#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int serverSocket, clientSocket;
struct sockaddr_in serverAddress, clientAddress;
socklen_t clientAddressLength = sizeof(clientAddress);

void runServer() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Error creating socket");
        return;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(2000);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Error binding socket");
        return;
    }

    listen(serverSocket, 1);
    printf("Server started. Waiting for a client...\n");

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
    if (clientSocket < 0) {
        perror("Error accepting client");
        return;
    }

    printf("Client accepted.\n");

    char username[BUFFER_SIZE], password[BUFFER_SIZE];
    recv(clientSocket, username, BUFFER_SIZE, 0);
    recv(clientSocket, password, BUFFER_SIZE, 0);

    if (authenticate(username, password)) {
        send(clientSocket, "Login successful", 15, 0);
        chatServer();
    } else {
        send(clientSocket, "Login failed", 13, 0);
        close(clientSocket);
    }

    close(serverSocket);
}

void runClient() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Error creating socket");
        return;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(2000);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Error connecting to server");
        return;
    }

    printf("Connected to the server.\n");

    char username[BUFFER_SIZE], password[BUFFER_SIZE];
    printf("Enter username: ");
    fgets(username, BUFFER_SIZE, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline

    printf("Enter password: ");
    fgets(password, BUFFER_SIZE, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline

    send(clientSocket, username, strlen(username), 0);
    send(clientSocket, password, strlen(password), 0);

    char response[BUFFER_SIZE];
    recv(clientSocket, response, BUFFER_SIZE, 0);
    if (strcmp(response, "Login successful") == 0) {
        chatClient();
    } else {
        printf("Login failed\n");
    }

    close(clientSocket);
}

int authenticate(const char* username, const char* password) {
    // Simulate reading from a file
    // In real scenarios, use secure methods to store and compare passwords
    return strcmp(username, "user") == 0 && strcmp(password, "pass") == 0;
}

void chatServer() {
    char message[BUFFER_SIZE];
    while (true) {
        recv(clientSocket, message, BUFFER_SIZE, 0);
        if (strcmp(message, "END") == 0) {
            send(clientSocket, "BYE", 3, 0);
            break;
        }
        printf("Client: %s\n", message);
        printf("Server: ");
        fgets(message, BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = 0; // Remove newline
        send(clientSocket, message, strlen(message), 0);
    }

    close(clientSocket);
}

void chatClient() {
    char message[BUFFER_SIZE];
    while (true) {
        printf("Client: ");
        fgets(message, BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = 0; // Remove newline
        send(clientSocket, message, strlen(message), 0);

        recv(clientSocket, message, BUFFER_SIZE, 0);
        if (strcmp(message, "BYE") == 0) {
            break;
        }
        printf("Server: %s\n", message);
    }

    close(clientSocket);
}

int main(int argc, char** argv) {
    if (argc > 1 && strcmp(argv[1], "server") == 0) {
        runServer();
    } else {
        runClient();
    }
    return 0;
}