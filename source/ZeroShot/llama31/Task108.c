int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    send(clientSocket, "say_hello", 9, 0);
    send(clientSocket, "Client", 6, 0);
    char buffer[1024];
    read(clientSocket, buffer, 1024);
    printf("%s\n", buffer);

    send(clientSocket, "add", 3, 0);
    send(clientSocket, "5,10", 4, 0);
    read(clientSocket, buffer, 1024);
    printf("%s\n", buffer);

    close(clientSocket);
    return 0;
}