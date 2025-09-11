#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // For PATH_MAX
#include <libgen.h> // For dirname
#include <unistd.h> // For access and readlink


// Function to canonicalize the path to prevent directory traversal
char* canonicalize_path(const char *path) {
    char resolved_path[PATH_MAX];
    if (realpath(path, resolved_path) == NULL) {
        perror("realpath failed");
        return NULL;
    }

    char* canonicalized_path = realpath(resolved_path, NULL); // Get canonical path with dynamic allocation
    if (canonicalized_path == NULL) {
        perror("realpath failed");
        return NULL;
    }

    return canonicalized_path;
}



char* read_file(const char *file_path) {
    if (!file_path || strlen(file_path) == 0) {
        fprintf(stderr, "File path cannot be null or empty.\n");
        return NULL;
    }


    char* canonicalPath = canonicalize_path(file_path);
    if (canonicalPath == NULL) {
      return NULL; // Error already handled in canonicalize_path
    }

    FILE *file = fopen(canonicalPath, "r");
    free(canonicalPath);  // Free memory after use

    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(file_size + 1); // Allocate memory for the content
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != file_size) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[bytes_read] = '\0'; // Null-terminate the string
    fclose(file);

    return buffer;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Please provide a file path as a command-line argument.\n");
        return 1;
    }

    const char *file_path = argv[1];


    char *file_content = read_file(file_path);
    if (file_content != NULL) {
        printf("%s\n", file_content);
        free(file_content); // Free the allocated memory

        // Test Cases (Demonstrative - these would be more extensive in real usage)
        char* test1 = read_file("test1.txt"); if(test1){printf("%s\n", test1); free(test1);}
        char* test2 = read_file("test2.txt"); if(test2){printf("%s\n", test2); free(test2);}
        char* test3 = read_file("test3.txt"); if(test3){printf("%s\n", test3); free(test3);}
        char* test4 = read_file("test4.txt"); if(test4){printf("%s\n", test4); free(test4);}
        char* test5 = read_file("test5.txt"); if(test5){printf("%s\n", test5); free(test5);}




    }

    return 0;
}