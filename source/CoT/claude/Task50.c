
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>
#include <openssl/sha.h>

#define UPLOAD_DIR "uploads/"
#define MAX_FILE_SIZE 10485760  // 10MB limit
#define MAX_FILENAME_LENGTH 256
#define SHA256_STRING_LENGTH 64

// Function prototypes
static void generate_unique_filename(const char* original_name, char* unique_name);
static void sanitize_filename(const char* input, char* output);
static char* upload_file(const char* filename, const unsigned char* file_data, size_t data_size);

static void generate_unique_filename(const char* original_name, char* unique_name) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    
    time_t current_time = time(NULL);
    char time_str[32];
    sprintf(time_str, "%ld", current_time);
    
    SHA256_Update(&sha256, original_name, strlen(original_name));
    SHA256_Update(&sha256, time_str, strlen(time_str));
    SHA256_Final(hash, &sha256);
    
    char hash_str[SHA256_STRING_LENGTH + 1];
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash_str[i*2], "%02x", hash[i]);
    }
    
    sprintf(unique_name, "%s_%s", hash_str, original_name);
}

static void sanitize_filename(const char* input, char* output) {
    int j = 0;
    for(size_t i = 0; i < strlen(input) && i < MAX_FILENAME_LENGTH - 1; i++) {
        if(isalnum(input[i]) || input[i] == '.' || input[i] == '-') {
            output[j++] = input[i];
        } else {
            output[j++] = '_';
        }
    }
    output[j] = '\\0';
}

static char* upload_file(const char* filename, const unsigned char* file_data, size_t data_size) {
    char* result = malloc(512);
    if (!result) {
        return NULL;
    }

    // Check file size
    if (data_size > MAX_FILE_SIZE) {
        sprintf(result, "Error: File size exceeds limit of 10MB");
        return result;
    }

    // Create upload directory
    #ifdef _WIN32
        _mkdir(UPLOAD_DIR);
    #else
        mkdir(UPLOAD_DIR, 0755);
    #endif

    // Sanitize filename
    char sanitized_name[MAX_FILENAME_LENGTH];
    sanitize_filename(filename, sanitized_name);

    // Generate unique filename
    char unique_filename[MAX_FILENAME_LENGTH + SHA256_STRING_LENGTH + 2];
    generate_unique_filename(sanitized_name, unique_filename);

    // Create full path
    char full_path[MAX_FILENAME_LENGTH + SHA256_STRING_LENGTH + sizeof(UPLOAD_DIR)];
    snprintf(full_path, sizeof(full_path), "%s%s", UPLOAD_DIR, unique_filename);

    // Write file
    FILE* fp = fopen(full_path, "wb");
    if (!fp) {
        sprintf(result, "Error: Cannot create file");
        return result;
    }

    size_t written = fwrite(file_data, 1, data_size, fp);
    fclose(fp);

    if (written != data_size) {
        sprintf(result, "Error: Failed to write complete file");
        return result;
    }

    // Set file permissions
    #ifndef _WIN32
        chmod(full_path, 0644);
    #endif

    sprintf(result, "File uploaded successfully: %s", unique_filename);
    return result;
}

int main() {
    // Test cases
    unsigned char test_file1[] = "Test content 1";
    unsigned char test_file2[] = "Test content 2";
    unsigned char* test_file3 = malloc(MAX_FILE_SIZE + 1);
    unsigned char test_file4[] = "Test content 4";
    unsigned char test_file5[] = "Test content 5";

    memset(test_file3, 'x', MAX_FILE_SIZE + 1);

    printf("%s\\n", upload_file("test1.txt", test_file1, strlen((char*)test_file1)));
    printf("%s\\n", upload_file("test2.doc", test_file2, strlen((char*)test_file2)));
    printf("%s\\n", upload_file("test3.pdf", test_file3, MAX_FILE_SIZE + 1));
    printf("%s\\n", upload_file("test4<script>.txt", test_file4, strlen((char*)test_file4)));
    printf("%s\\n", upload_file("../test5.txt", test_file5, strlen((char*)test_file5)));

    free(test_file3);
    return 0;
}
