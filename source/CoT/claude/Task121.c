
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <openssl/sha.h>
#include <errno.h>

#define UPLOAD_DIR "uploads/"
#define MAX_FILE_SIZE (10 * 1024 * 1024) // 10MB limit
#define PATH_MAX 4096
#define SHA256_STRING_LENGTH (SHA256_DIGEST_LENGTH * 2 + 1)

// Function prototypes
static void generate_unique_filename(const char* filepath, char* output);
static int create_directory(const char* path);
static long get_file_size(const char* filename);
static int copy_file(const char* source, const char* destination);

char* upload_file(const char* source_file_path) {
    static char result[PATH_MAX];
    char unique_filename[SHA256_STRING_LENGTH];
    char destination_path[PATH_MAX];
    const char* file_extension;
    
    // Input validation
    if (source_file_path == NULL || strlen(source_file_path) == 0) {
        return "Error: Invalid file path";
    }

    // Check if file exists
    FILE* source_file = fopen(source_file_path, "rb");
    if (source_file == NULL) {
        return "Error: File does not exist";
    }
    fclose(source_file);

    // Check file size
    long file_size = get_file_size(source_file_path);
    if (file_size == -1 || file_size > MAX_FILE_SIZE) {
        return "Error: File size exceeds limit or cannot be determined";
    }

    // Create upload directory if it doesn't exist\n    if (create_directory(UPLOAD_DIR) != 0) {\n        return "Error: Cannot create upload directory";\n    }\n\n    // Generate unique filename\n    generate_unique_filename(source_file_path, unique_filename);\n    \n    // Get file extension\n    file_extension = strrchr(source_file_path, '.');\n    if (file_extension == NULL) {\n        file_extension = "";\n    }\n\n    // Create destination path\n    snprintf(destination_path, PATH_MAX, "%s%s%s", UPLOAD_DIR, unique_filename, file_extension);\n\n    // Copy file\n    if (copy_file(source_file_path, destination_path) != 0) {\n        return "Error: Failed to copy file";\n    }\n\n    snprintf(result, PATH_MAX, "File uploaded successfully: %s%s", unique_filename, file_extension);\n    return result;\n}\n\nstatic void generate_unique_filename(const char* filepath, char* output) {\n    unsigned char hash[SHA256_DIGEST_LENGTH];\n    char unique_data[PATH_MAX + 20];\n    time_t current_time;\n    SHA256_CTX sha256;\n    int i;\n\n    time(&current_time);\n    snprintf(unique_data, sizeof(unique_data), "%s%ld", filepath, current_time);\n\n    SHA256_Init(&sha256);\n    SHA256_Update(&sha256, unique_data, strlen(unique_data));\n    SHA256_Final(hash, &sha256);\n\n    for(i = 0; i < SHA256_DIGEST_LENGTH; i++) {\n        sprintf(output + (i * 2), "%02x", hash[i]);\n    }\n    output[SHA256_DIGEST_LENGTH * 2] = '\\0';
}

static int create_directory(const char* path) {
    #ifdef _WIN32
        return mkdir(path);
    #else
        return mkdir(path, 0777);
    #endif
}

static long get_file_size(const char* filename) {
    struct stat st;
    if (stat(filename, &st) == 0) {
        return st.st_size;
    }
    return -1;
}

static int copy_file(const char* source, const char* destination) {
    FILE *src, *dst;
    char buffer[4096];
    size_t bytes;

    src = fopen(source, "rb");
    if (src == NULL) return -1;

    dst = fopen(destination, "wb");
    if (dst == NULL) {
        fclose(src);
        return -1;
    }

    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        if (fwrite(buffer, 1, bytes, dst) != bytes) {
            fclose(src);
            fclose(dst);
            return -1;
        }
    }

    fclose(src);
    fclose(dst);
    return 0;
}

int main() {
    // Test cases
    const char* test_files[] = {
        "test1.txt",
        "test2.jpg",
        "test3.pdf",
        "test4.doc",
        "test5.zip"
    };
    int num_tests = 5;

    for (int i = 0; i < num_tests; i++) {
        printf("Testing file: %s\\n", test_files[i]);
        char* result = upload_file(test_files[i]);
        printf("%s\\n", result);
        printf("------------------------\\n");
    }

    return 0;
}
