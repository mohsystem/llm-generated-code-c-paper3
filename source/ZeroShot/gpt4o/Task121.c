#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool uploadFile(const char *sourceFile, const char *destinationDir) {
    FILE *src = fopen(sourceFile, "rb");
    if (src == NULL) {
        return false;
    }
    char destinationFile[256];
    snprintf(destinationFile, sizeof(destinationFile), "%s/%s", destinationDir, strrchr(sourceFile, '/') + 1);
    FILE *dest = fopen(destinationFile, "wb");
    if (dest == NULL) {
        fclose(src);
        return false;
    }
    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }
    fclose(src);
    fclose(dest);
    return true;
}

int main() {
    // Test cases
    printf("%d\n", uploadFile("test1.txt", "/path/to/destination"));
    printf("%d\n", uploadFile("test2.txt", "/path/to/destination"));
    printf("%d\n", uploadFile("test3.txt", "/path/to/destination"));
    printf("%d\n", uploadFile("test4.txt", "/path/to/destination"));
    printf("%d\n", uploadFile("test5.txt", "/path/to/destination"));
    return 0;
}