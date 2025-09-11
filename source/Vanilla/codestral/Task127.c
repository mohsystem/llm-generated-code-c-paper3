#include <stdio.h>

void copyFile(const char *source, const char *destination) {
    FILE *src, *dst;
    char ch;

    src = fopen(source, "rb");
    dst = fopen(destination, "wb");

    if (src == NULL || dst == NULL) {
        perror("An error occurred while copying the file");
    } else {
        while ((ch = fgetc(src)) != EOF)
            fputc(ch, dst);
    }

    fclose(src);
    fclose(dst);
}

int main() {
    copyFile("source_file_path", "destination_file_path");
    return 0;
}