#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void task127(const char* file_path) {
    FILE* source = fopen(file_path, "rb");
    if (source == NULL) {
        perror("Error opening source file");
        return;
    }

    char temp_path[L_tmpnam];
    tmpnam(temp_path);

    FILE* temp = fopen(temp_path, "wb");
    if (temp == NULL) {
        perror("Error opening temp file");
        fclose(source);
        return;
    }

    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        size_t bytes_written = fwrite(buffer, 1, bytes_read, temp);
        if (bytes_written != bytes_read) {
            perror("Error writing to temp file");
            fclose(source);
            fclose(temp);
            remove(temp_path);
            return;
        }
    }

    if (ferror(source)) {
        perror("Error reading source file");
        fclose(source);
        fclose(temp);
        remove(temp_path);
        return;
    }

    printf("File copied to: %s\n", temp_path);

    fclose(source);
    fclose(temp);
    remove(temp_path);
}

int main() {
    task127("input.txt");
    return 0;
}