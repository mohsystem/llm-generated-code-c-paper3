#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void extractTar(const char* tarFilePath, const char* extractTo) {
    int fd = open(tarFilePath, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return;
    }

    char buffer[512];
    while (read(fd, buffer, 512) == 512) {
        char fileName[100];
        strncpy(fileName, buffer + 0, 100);
        fileName[100] = '\0';

        if (buffer[156] == '5') { // Directory
            char dirPath[256];
            snprintf(dirPath, sizeof(dirPath), "%s/%s", extractTo, fileName);
            mkdir(dirPath, 0755);
        } else { // File
            char filePath[256];
            snprintf(filePath, sizeof(filePath), "%s/%s", extractTo, fileName);
            int outFd = open(filePath, O_WRONLY | O_CREAT, 0644);
            if (outFd < 0) {
                perror("open");
                continue;
            }

            while (read(fd, buffer, 512) == 512) {
                write(outFd, buffer, 512);
            }
            close(outFd);
        }

        // Skip to next file
        lseek(fd, 512, SEEK_CUR);
    }
    close(fd);
}

int main() {
    // Test cases
    extractTar("path/to/sample.tar", "extract/to/directory");
    return 0;
}