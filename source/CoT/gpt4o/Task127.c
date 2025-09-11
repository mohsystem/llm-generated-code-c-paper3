#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void copyFile(const char* sourcePath, const char* destPath) {
    FILE *source, *dest;
    char ch;

    source = fopen(sourcePath, "rb");
    if (source == NULL) {
        fprintf(stderr, "File not found: %s\n", strerror(errno));
        return;
    }

    dest = fopen(destPath, "wb");
    if (dest == NULL) {
        fprintf(stderr, "Error opening destination file: %s\n", strerror(errno));
        fclose(source);
        return;
    }

    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, dest);
    }

    fclose(source);
    fclose(dest);
}

int main() {
    copyFile("path/to/source/file1.txt", "path/to/destination/file1.txt");
    copyFile("path/to/source/file2.txt", "path/to/destination/file2.txt");
    copyFile("path/to/source/file3.txt", "path/to/destination/file3.txt");
    copyFile("path/to/source/file4.txt", "path/to/destination/file4.txt");
    copyFile("path/to/source/file5.txt", "path/to/destination/file5.txt");
    return 0;
}