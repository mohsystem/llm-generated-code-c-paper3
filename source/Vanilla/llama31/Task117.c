#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

void extractTar(const char* tarFilePath, const char* extractDir) {
    // This is a very simplified example and does not handle all TAR file formats.
    // In real-world scenarios, use a library like libtar.
    char command[256];
    sprintf(command, "tar -xvzf %s -C %s", tarFilePath, extractDir);
    system(command);
}

int main() {
    const char* tarFilePath = "path/to/your/tarfile.tar.gz";
    const char* extractDir = "path/to/extract/directory";
    extractTar(tarFilePath, extractDir);
    return 0;
}