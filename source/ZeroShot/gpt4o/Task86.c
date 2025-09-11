#include <stdio.h>
#include <stdlib.h>

void downloadExe(const char* url) {
    char command[512];
    snprintf(command, sizeof(command), "curl -o temp_downloaded.exe %s", url);
    if (system(command) != 0) {
        fprintf(stderr, "Download failed\n");
    }
}

void executeExe() {
    if (system("temp_downloaded.exe") != 0) {
        fprintf(stderr, "Execution failed\n");
    }
}

int main() {
    const char* testUrls[] = {
        "http://example.com/test1.exe",
        "http://example.com/test2.exe",
        "http://example.com/test3.exe",
        "http://example.com/test4.exe",
        "http://example.com/test5.exe"
    };

    for (int i = 0; i < 5; i++) {
        downloadExe(testUrls[i]);
        executeExe();
    }

    return 0;
}