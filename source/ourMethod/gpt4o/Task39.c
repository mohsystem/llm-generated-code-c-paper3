#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

char* displayFileContent(const char* filename) {
    static char result[4096];
    memset(result, 0, sizeof(result));

    struct stat file_stat;
    if (stat(filename, &file_stat) != 0 || !S_ISREG(file_stat.st_mode)) {
        snprintf(result, sizeof(result), "File not found.");
        return result;
    }

    char command[512];
    snprintf(command, sizeof(command), "cat %s 2>&1", filename);

    FILE* pipe = popen(command, "r");
    if (!pipe) {
        snprintf(result, sizeof(result), "Error displaying file.");
        return result;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        strncat(result, buffer, sizeof(result) - strlen(result) - 1);
    }
    int exitCode = pclose(pipe);
    if (exitCode != 0) {
        snprintf(result, sizeof(result), "Error displaying file.");
    }

    return result;
}

int main() {
    printf("%s", displayFileContent("test1.txt"));
    printf("%s", displayFileContent("test2.txt"));
    printf("%s", displayFileContent("test3.txt"));
    printf("%s", displayFileContent("test4.txt"));
    printf("%s", displayFileContent("test5.txt"));
    return 0;
}