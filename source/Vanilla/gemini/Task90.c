#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <process.h>


#pragma comment(lib, "Ws2_32.lib")

#define PORT 8080
#define MAX_CLIENTS 100

SOCKET client_sockets[MAX_CLIENTS];
int num_clients = 0;

unsigned int __stdcall handle_client(void* arg) {
    SOCKET client_socket = (SOCKET)arg;
    char buffer[1024];
    int bytes_received;

    while (true) {
        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            break;
        }

        for (int i = 0; i < num_clients; i++) {
            if (client_sockets[i] != client_socket && client_sockets[i] != INVALID_SOCKET) {
                 send(client_sockets[i], buffer, bytes_received, 0);
            }
        }
    }


    closesocket(client_socket);

    for (int i = 0; i < num_clients; i++) {
        if (client_sockets[i] == client_socket) {
            client_sockets[i] = INVALID_SOCKET; // Mark as disconnected
            break;
        }
    }
    printf("Client disconnected.\n");
    return 0;
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        return 1;
    }

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        fprintf(stderr, "Socket creation failed.\n");
        WSACleanup();
        return 1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = IN_ADDR_ANY;

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        fprintf(stderr, "Binding failed.\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
        fprintf(stderr, "Listening failed.\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port %d\n", PORT);

    while (true) {
        SOCKET client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == INVALID_SOCKET) {
            fprintf(stderr, "Accept failed.\n");
            closesocket(server_socket);
            WSACleanup();
            return 1;
        }

        if (num_clients < MAX_CLIENTS) {
             client_sockets[num_clients++] = client_socket;
            printf("Client connected.\n");

            _beginthreadex(NULL, 0, handle_client, (void*)client_socket, 0, NULL);
           
        } else {
            printf("Maximum client limit reached.\n");
            closesocket(client_socket);
        }
    }

    closesocket(server_socket);
    WSACleanup();

    return 0;
}