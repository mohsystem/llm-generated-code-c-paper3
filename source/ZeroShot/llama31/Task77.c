#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

// Note: This example uses a simple FTP library which is not part of standard C.
// For a complete solution, consider using a library like libcurl.

// This example is simplified and does not handle errors as robustly as it should.
void downloadFile(const char* hostname, const char* username, const char* password, const char* filename) {
    // This is a very basic example and does not cover all FTP commands and error handling.
    // In a real-world application, use a library like libcurl for FTP operations.

    // Simulating FTP connection (this is highly simplified and not recommended for real use)
    printf("Connecting to %s\n", hostname);
    printf("Logging in with %s and %s\n", username, password);
    printf("Downloading %s\n", filename);

    // Open local file for writing
    FILE* file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Failed to open local file for writing.\n");
        return;
    }

    // Simulate downloading (this is a placeholder and does not actually download the file)
    char buffer[1024];
    fwrite(buffer, 1, 1024, file); // This is just a placeholder, real implementation would read from FTP server
    fclose(file);

    printf("%s downloaded successfully.\n", filename);
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: %s <hostname> <username> <password> <filename>\n", argv[0]);
        return 1;
    }
    const char* hostname = argv[1];
    const char* username = argv[2];
    const char* password = argv[3];
    const char* filename = argv[4];

    downloadFile(hostname, username, password, filename);
    return 0;
}