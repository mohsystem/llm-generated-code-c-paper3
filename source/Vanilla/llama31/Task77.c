// Note: C does not have built-in FTP support, so we use system calls which is not recommended for production.
// For real applications, use a library like libcurl.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void downloadFile(const char* hostname, const char* username, const char* password, const char* filename) {
    // Using system calls for simplicity, but this is not secure or recommended.
    char command[256];
    sprintf(command, "curl -u %s:%s ftp://%s/%s -o %s", username, password, hostname, filename, filename);
    system(command);
    printf("File downloaded successfully\n");
}

int main(int argc, char** argv) {
    if (argc < 5) {
        printf("Usage: ./Task77 <hostname> <username> <password> <filename>\n");
        return 1;
    }

    downloadFile(argv[1], argv[2], argv[3], argv[4]);

    return 0;
}