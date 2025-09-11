#include <stdio.h>
#include <stdlib.h>

void displayFileContents(const char* filename) {
    char command[256];
    snprintf(command, sizeof(command), "cat %s", filename);
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        fprintf(stderr, "Error reading file.\n");
        return;
    }
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer);
    }
    pclose(pipe);
}

int main() {
    displayFileContents("test.txt");
    displayFileContents("nonexistent.txt");
    displayFileContents("/etc/passwd");
    displayFileContents("C:\\Windows\\System32\\drivers\\etc\\hosts");
    displayFileContents("../../../../../etc/passwd");
    return 0;
}