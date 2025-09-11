
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    const char* message;
    int code;
} Error;

Error copy_file(const char* source_path, const char* dest_path) {
    Error error = {NULL, 0};
    FILE *src = NULL, *dst = NULL;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    src = fopen(source_path, "rb");
    if (src == NULL) {
        error.message = "Unable to open source file";
        error.code = 1;
        return error;
    }

    dst = fopen(dest_path, "wb");
    if (dst == NULL) {
        fclose(src);
        error.message = "Unable to open destination file";
        error.code = 2;
        return error;
    }

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        if (fwrite(buffer, 1, bytes_read, dst) != bytes_read) {
            fclose(src);
            fclose(dst);
            error.message = "Error writing to destination file";
            error.code = 3;
            return error;
        }
    }

    if (ferror(src)) {
        fclose(src);
        fclose(dst);
        error.message = "Error reading from source file";
        error.code = 4;
        return error;
    }

    fclose(src);
    fclose(dst);
    return error;
}

int main() {
    // Test cases
    struct {
        const char* source;
        const char* dest;
    } test_cases[] = {
        {"./source1.txt", "./dest1.txt"},
        {"./nonexistent.txt", "./dest2.txt"},
        {"./source3.txt", "./dest3.txt"},
        {"./source4.txt", "./dest4.txt"},
        {"./source5.txt", "./dest5.txt"}
    };

    for (int i = 0; i < 5; i++) {
        printf("Test case %d:\\n", i + 1);
        Error result = copy_file(test_cases[i].source, test_cases[i].dest);
        
        if (result.code != 0) {
            printf("Error: %s (code: %d)\\n", result.message, result.code);
        } else {
            printf("File copied successfully!\\n");
        }
        printf("\\n");
    }

    return 0;
}
