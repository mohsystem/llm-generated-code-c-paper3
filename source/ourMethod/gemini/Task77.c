#include <stdio.h>
#include <string.h>
#include <ftplib.h>

void downloadSensitiveFile(const char *hostname, const char *username, const char *password, const char *remoteFilePath, const char *localFilePath) {
    netbuf *ftp_control_socket;
    FILE *localFile;
    int result;

    ftp_control_socket = malloc(sizeof(netbuf));
    if (ftp_control_socket == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    if (FTP_Connect(hostname, ftp_control_socket) != 1) {
        fprintf(stderr, "FTP connection failed: %s\n", hostname);
        free(ftp_control_socket);
        return;
    }


    if (FTP_Login(username, password, ftp_control_socket) != 1) {
        fprintf(stderr, "FTP login failed: %s\n", username);
        FTP_Quit(ftp_control_socket);
        free(ftp_control_socket);
        return;
    }

    FTP_Binary(ftp_control_socket); 

    localFile = fopen(localFilePath, "wb");
    if (localFile == NULL) {
        fprintf(stderr, "Failed to open local file: %s\n", localFilePath);
        FTP_Quit(ftp_control_socket);
        free(ftp_control_socket);
        return;
    }

    result = FTP_RetrFile(remoteFilePath, localFile, ftp_control_socket);
    if (result != 1) {
        fprintf(stderr, "Failed to download file: %s\n", remoteFilePath);
    }
    else
    {
        printf("File downloaded successfully: %s\n", localFilePath);
    }


    fclose(localFile);
    FTP_Quit(ftp_control_socket);
    free(ftp_control_socket);
}

int main() {
    downloadSensitiveFile("test.rebex.net", "demo", "password", "/pub/example/readme.txt", "readme.txt");
    downloadSensitiveFile("test.rebex.net", "demo", "password", "/pub/example/imap-console-client.png", "imap-console-client.png");
    downloadSensitiveFile("test.rebex.net", "demo", "password", "/pub/example/WinFormClient.png", "WinFormClient.png");
    downloadSensitiveFile("test.rebex.net", "demo", "password", "/pub/example/latex-report.pdf", "latex-report.pdf");
    downloadSensitiveFile("test.rebex.net", "demo", "password", "/pub/example/mail-merge.docx", "mail-merge.docx");
    return 0;
}