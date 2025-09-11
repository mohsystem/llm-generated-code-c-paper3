#include <stdio.h>
#include <string.h>
#include <ftplib.h>

void downloadFile(const char *hostname, const char *username, const char *password, const char *filename) {
    netbuf *ftp_connection = NULL;
    ftp_session *ftp_session = NULL;
    FILE *file = NULL;
    char buffer[1024];
    int bytes_read;

    if ((ftp_connection = malloc(sizeof(netbuf))) == NULL) return;
    if ((ftp_session = malloc(sizeof(ftp_session))) == NULL) goto cleanup;

    if (FTP_Connect(hostname, ftp_connection) != 1) goto cleanup;
    if (FTP_Login(username, password, ftp_connection, ftp_session) != 1) goto cleanup;

    if (FTP_Binary(1, ftp_connection, ftp_session) != 1) goto cleanup; // Set binary mode

    if ((file = fopen(filename, "wb")) == NULL) goto cleanup;

    if (FTP_RetrFile(filename, file, 1024, ftp_connection, ftp_session) != 1) goto cleanup;


    printf("File downloaded successfully.\n");

cleanup:
    if (file) fclose(file);
    if (ftp_session) {
        FTP_Quit(ftp_connection, ftp_session);
        free(ftp_session);
    }
    if (ftp_connection) {
        FTP_Disconnect(ftp_connection);
        free(ftp_connection);
    }
}



int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <hostname> <username> <password> <filename>\n", argv[0]);
        return 1;
    }
    
    downloadFile(argv[1], argv[2], argv[3], argv[4]);


    //Test Cases
    downloadFile("test.rebex.net", "demo", "password", "readme.txt");
    downloadFile("test.rebex.net", "demo", "password", "pub.key");


    return 0;
}