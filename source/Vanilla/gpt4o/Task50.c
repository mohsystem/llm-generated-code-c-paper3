#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char* upload_file(const char* file_name, const char* file_content) {
    struct stat st = {0};
    if (stat("uploads", &st) == -1) {
        mkdir("uploads", 0700);
    }
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "uploads/%s", file_name);
    FILE *file = fopen(file_path, "wb");
    if (file) {
        fwrite(file_content, sizeof(char), strlen(file_content), file);
        fclose(file);
        char *success_msg = malloc(256);
        snprintf(success_msg, 256, "File uploaded successfully: %s", file_name);
        return success_msg;
    } else {
        char *error_msg = malloc(256);
        snprintf(error_msg, 256, "Failed to upload file: %s", file_name);
        return error_msg;
    }
}

int main() {
    printf("%s\n", upload_file("test1.txt", "Hello World!"));
    printf("%s\n", upload_file("test2.txt", "C Programming"));
    printf("%s\n", upload_file("test3.txt", "File Upload Test"));
    printf("%s\n", upload_file("test4.txt", "Sample Data"));
    printf("%s\n", upload_file("test5.txt", "Another Test"));
    return 0;
}