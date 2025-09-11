#include <stdio.h>

void copyFile(const char *source, const char *destination) {
    FILE *src = fopen(source, "rb");
    FILE *dst = fopen(destination, "wb");
    char buf[1024];
    size_t nread;

    if (src && dst) {
        while ((nread = fread(buf, 1, sizeof buf, src)) > 0) {
            fwrite(buf, 1, nread, dst);
        }
    } else {
        fprintf(stderr, "Unable to copy file.\n");
    }

    if (src) {
        fclose(src);
    }
    if (dst) {
        fclose(dst);
    }
}

int main() {
    copyFile("source_file.txt", "temp_file.txt");
    copyFile("non_existent_file.txt", "temp_file.txt");
    copyFile("source_file.txt", "/non_writable_directory/temp_file.txt");
    copyFile("source_file.txt", "temp_file.txt");
    copyFile("source_file.txt", "another_temp_file.txt");

    return 0;
}