// C
#include <stdio.h>
#include <string.h>

char* uploadFile(char* fileData, int size) {
    // Here you would handle the file uploading to the server
    // For simplicity, we're just returning a confirmation message
    static char msg[30] = "File uploaded successfully.";
    return msg;
}

int main() {
    // Test cases
    char fileData[1024]; // Replace this with actual file data
    printf("%s", uploadFile(fileData, sizeof(fileData)));
    return 0;
}