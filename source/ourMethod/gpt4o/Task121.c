#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int upload_file(const char *file_content, const char *file_name) {
    // Define the directory where files will be uploaded
    const char *upload_directory = "uploads";

    // Create the directory if it doesn't exist
    struct stat st = {0};
    if (stat(upload_directory, &st) == -1) {
        mkdir(upload_directory, 0700);
    }

    // Ensure file_name is sanitized and doesn't contain any path traversal
    const char *sanitized_file_name = strrchr(file_name, '/');
    sanitized_file_name = sanitized_file_name ? sanitized_file_name + 1 : file_name;

    // Define the full path where the file will be saved
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%s/%s", upload_directory, sanitized_file_name);

    // Ensure not to overwrite existing files
    if (stat(file_path, &st) == 0) {
        printf("File already exists: %s\n", sanitized_file_name);
        return 0;
    }

    // Write the file to the specified path
    FILE *file = fopen(file_path, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return 0;
    }
    fwrite(file_content, sizeof(char), strlen(file_content), file);
    fclose(file);
    return 1;
}

int main() {
    // Example test cases
    const char *file_content = "Sample content";
    printf("%s\n", upload_file(file_content, "example1.txt") ? "File uploaded successfully" : "Error uploading file");
    printf("%s\n", upload_file(file_content, "example2.txt") ? "File uploaded successfully" : "Error uploading file");
    printf("%s\n", upload_file(file_content, "example3.txt") ? "File uploaded successfully" : "Error uploading file");
    printf("%s\n", upload_file(file_content, "example4.txt") ? "File uploaded successfully" : "Error uploading file");
    printf("%s\n", upload_file(file_content, "example5.txt") ? "File uploaded successfully" : "Error uploading file");
    return 0;
}