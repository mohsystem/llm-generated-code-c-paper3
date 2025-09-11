#include <stdio.h>
#include <stdlib.h>

int copyFile(const char *sourcePath, const char *destinationPath) {
    FILE *source = fopen(sourcePath, "rb");
    FILE *dest = fopen(destinationPath, "wb");

    if (!source || !dest) {
        perror("An error occurred");
        if (source) fclose(source);
        if (dest) fclose(dest);
        return 0;
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    fclose(source);
    fclose(dest);
    return 1;
}

int main() {
    printf("%d\n", copyFile("test1.txt", "temp1.txt"));
    printf("%d\n", copyFile("test2.txt", "temp2.txt"));
    printf("%d\n", copyFile("test3.txt", "temp3.txt"));
    printf("%d\n", copyFile("test4.txt", "temp4.txt"));
    printf("%d\n", copyFile("test5.txt", "temp5.txt"));

    return 0;
}