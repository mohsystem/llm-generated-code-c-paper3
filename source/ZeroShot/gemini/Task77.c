#include <stdio.h>
#include <string.h>
#include <libftp/ftp.h>

// Note: This C example requires libftp. You'll need to install it
// (e.g., on Debian/Ubuntu: sudo apt-get install libftp-dev) and link 
// against it during compilation (e.g., gcc -o ftp_download ftp_download.c -lftp).



int downloadFile(const char *hostname, const char *username, const char *password, const char *remoteFilePath, const char *localFilePath) {
    ftp_t *ftp = ftp_new();
    if (ftp == NULL) {
        perror("ftp_new");
        return 1;
    }

    if (ftp_connect(ftp, hostname, 21) != 0) {
        fprintf(stderr, "Error connecting to FTP server: %s\n", ftp_strerror(ftp));
        ftp_free(ftp);
        return 1;
    }


    if (ftp_login(ftp, username, password) != 0) {
        fprintf(stderr, "FTP login failed: %s\n", ftp_strerror(ftp));
        ftp_free(ftp);
        return 1;
    }

    FILE *localFile = fopen(localFilePath, "wb");
    if (localFile == NULL) {
        perror("fopen");
        ftp_free(ftp);
        return 1;
    }
    
    if (ftp_retr(ftp, remoteFilePath, localFile) != 0) {
        fprintf(stderr, "Failed to download file: %s\n", ftp_strerror(ftp));
        fclose(localFile); // Close the file if download fails
        ftp_free(ftp);
        return 1;
    }
    

    fclose(localFile);
    ftp_quit(ftp);
    ftp_free(ftp);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <hostname> <username> <password> <remoteFile>\n", argv[0]);
        return 1;
    }

    const char *hostname = argv[1];
    const char *username = argv[2];
    const char *password = argv[3];
    const char *remoteFile = argv[4];
    
    char localFile[256]; // Adjust size as needed
    snprintf(localFile, sizeof(localFile), "downloaded_%s", remoteFile);


    if (downloadFile(hostname, username, password, remoteFile, localFile) == 0) {
        printf("File downloaded successfully to: %s\n", localFile);
    }


    return 0;
}