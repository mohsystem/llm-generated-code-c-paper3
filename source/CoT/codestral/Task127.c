#include <stdio.h>
#include <stdlib.h>

void copyFile(const char *src, const char *dest) {
    FILE *source = fopen(src, "rb");
    FILE *destination = fopen(dest, "wb");

    if (source) {
        if (destination) {
            int ch;
            while ((ch = fgetc(source)) != EOF) {
                fputc(ch, destination);
            }
            fclose(source);
            fclose(destination);
            printf("File copied successfully.\n");
        } else {
            fclose(source);
            printf("Unable to open destination file for writing.\n");
        }
    } else {
        printf("No such file/directory exists.\n");
    }
}

int main() {
    copyFile("/path/to/source/file", "/path/to/destination/file");
    copyFile("/path/to/nonexistent/file", "/path/to/destination/file");
    copyFile("/path/to/source/file", "/path/to/nonexistent/directory");
    return 0;
}