#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/ftp.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    const char* hostname = argv[1];
    const char* username = argv[2];
    const char* password = argv[3];
    const char* remoteFile = argv[4];
    const char* localFile = argv[5];

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Error creating socket\n");
        return 1;
    }

    struct hostent* server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr, "Error resolving hostname\n");
        return 1;
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    serv_addr.sin_port = htons(21);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        fprintf(stderr, "Error connecting to FTP server\n");
        return 1;
    }

    FILE* outputFile = fopen(localFile, "wb");
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening local file\n");
        return 1;
    }

    char buffer[1024];
    char command[256];

    snprintf(command, sizeof(command), "USER %s\r\n", username);
    write(sockfd, command, strlen(command));
    read(sockfd, buffer, sizeof(buffer));

    snprintf(command, sizeof(command), "PASS %s\r\n", password);
    write(sockfd, command, strlen(command));
    read(sockfd, buffer, sizeof(buffer));

    snprintf(command, sizeof(command), "PASV\r\n");
    write(sockfd, command, strlen(command));
    read(sockfd, buffer, sizeof(buffer));

    char* pasvResponse = strdup(buffer);
    char* ipStart = strrchr(pasvResponse, ',') + 1;
    char* ipEnd = strrchr(ipStart, ',');
    unsigned int portStart = (unsigned int)(ipEnd - pasvResponse + 1);
    unsigned int portEnd = (unsigned int)(strrchr(pasvResponse, ')') - pasvResponse);

    char ip[16];
    strncpy(ip, ipStart, ipEnd - ipStart);
    ip[ipEnd - ipStart] = '\0';
    unsigned int port = atoi(pasvResponse + portStart);

    struct sockaddr_in dataAddr;
    memset(&dataAddr, 0, sizeof(dataAddr));
    dataAddr.sin_family = AF_INET;
    dataAddr.sin_addr.s_addr = inet_addr(ip);
    dataAddr.sin_port = htons(port);

    int dataSockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (dataSockfd < 0) {
        fprintf(stderr, "Error creating data socket\n");
        return 1;
    }

    if (connect(dataSockfd, (struct sockaddr*)&dataAddr, sizeof(dataAddr)) < 0) {
        fprintf(stderr, "Error connecting to data socket\n");
        return 1;
    }

    snprintf(command, sizeof(command), "RETR %s\r\n", remoteFile);
    write(sockfd, command, strlen(command));
    read(sockfd, buffer, sizeof(buffer));

    ssize_t bytesRead;
    while ((bytesRead = read(dataSockfd, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, bytesRead, outputFile);
    }

    fclose(outputFile);

    snprintf(command, sizeof(command), "QUIT\r\n");
    write(sockfd, command, strlen(command));
    read(sockfd, buffer, sizeof(buffer));

    close(dataSockfd);
    close(sockfd);

    printf("File downloaded successfully.\n");

    return 0;
}