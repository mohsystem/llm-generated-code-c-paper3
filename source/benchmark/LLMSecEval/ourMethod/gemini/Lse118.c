#define _GNU_SOURCE // For dirname
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/types.h>

#define NUM_FLOATS 3
#define FLOAT_STR_LEN 50 // Generous buffer for a single float string
#define TOTAL_BUFFER_SIZE (NUM_FLOATS * FLOAT_STR_LEN)

/**
 * @brief Securely generates a random float.
 * Reads from /dev/urandom for entropy.
 * @return A random float between 0.0 and 1.0. Returns -1.0 on error.
 */
float get_random_float() {
    int urandom_fd = open("/dev/urandom", O_RDONLY);
    if (urandom_fd < 0) {
        perror("Failed to open /dev/urandom");
        return -1.0f;
    }

    unsigned int seed;
    ssize_t result = read(urandom_fd, &seed, sizeof(seed));
    close(urandom_fd);

    if (result != sizeof(seed)) {
        fprintf(stderr, "Failed to read from /dev/urandom\n");
        return -1.0f;
    }

    return (float)seed / (float)UINT_MAX;
}


/**
 * @brief Generates floats, concatenates them, and writes to a file securely.
 *
 * Follows the secure pattern: write to temp file, fsync, then atomic rename.
 * Also fsyncs the parent directory for durability.
 *
 * @param final_filename The final name of the file.
 * @return 0 on success, -1 on failure.
 */
int generate_and_write_to_file(const char* final_filename) {
    // 1. Generate 3 random floats and concatenate into a string buffer
    char buffer[TOTAL_BUFFER_SIZE];
    memset(buffer, 0, TOTAL_BUFFER_SIZE);
    int offset = 0;

    for (int i = 0; i < NUM_FLOATS; ++i) {
        float r = get_random_float();
        if (r < 0.0f) return -1;

        int remaining_size = TOTAL_BUFFER_SIZE - offset;
        int written = snprintf(buffer + offset, remaining_size, "%.8g%s", r, (i < NUM_FLOATS - 1) ? " " : "");
        
        if (written < 0 || written >= remaining_size) {
            fprintf(stderr, "Error: snprintf buffer overflow or encoding error.\n");
            return -1;
        }
        offset += written;
    }

    // 2. Securely write to a file
    char temp_template[PATH_MAX];
    char final_filename_copy[PATH_MAX];
    char final_filename_copy_for_dirname[PATH_MAX];

    // strncpy is safer than strcpy
    strncpy(final_filename_copy, final_filename, PATH_MAX - 1);
    final_filename_copy[PATH_MAX - 1] = '\0';
    
    strncpy(final_filename_copy_for_dirname, final_filename, PATH_MAX - 1);
    final_filename_copy_for_dirname[PATH_MAX - 1] = '\0';
    
    char* parent_dir = dirname(final_filename_copy_for_dirname);

    // Create parent directory if it doesn't exist.
    struct stat st = {0};
    if (stat(parent_dir, &st) == -1) {
        if (mkdir(parent_dir, 0700) != 0 && errno != EEXIST) {
             perror("Failed to create parent directory");
             return -1;
        }
    }

    int n = snprintf(temp_template, PATH_MAX, "%s/data-XXXXXX.tmp", parent_dir);
    if (n < 0 || n >= PATH_MAX) {
        fprintf(stderr, "Error creating temp file path.\n");
        return -1;
    }

    int fd = mkstemp(temp_template);
    if (fd < 0) {
        perror("Failed to create temporary file");
        return -1;
    }

    // Write content to temp file
    ssize_t bytes_written = write(fd, buffer, strlen(buffer));
    if (bytes_written < 0 || (size_t)bytes_written != strlen(buffer)) {
        perror("Failed to write to temporary file");
        close(fd);
        unlink(temp_template);
        return -1;
    }

    // Ensure data is written to disk
    if (fsync(fd) < 0) {
        perror("Failed to fsync temporary file");
        close(fd);
        unlink(temp_template);
        return -1;
    }

    if (close(fd) < 0) {
        perror("Failed to close temporary file");
        unlink(temp_template);
        return -1;
    }

    // Atomically rename the temp file
    if (rename(temp_template, final_filename_copy) < 0) {
        perror("Failed to rename temporary file");
        unlink(temp_template);
        return -1;
    }

    // Sync the parent directory to ensure rename is durable
    int dir_fd = open(parent_dir, O_RDONLY | O_DIRECTORY);
    if(dir_fd < 0) {
        perror("Could not open parent directory to fsync");
        return -1; // The file is created, but this is a durability error
    }
    if (fsync(dir_fd) < 0) {
        perror("Failed to fsync parent directory");
        close(dir_fd);
        return -1;
    }
    close(dir_fd);

    return 0;
}


int main() {
    printf("Running 5 test cases...\n");
    for (int i = 1; i <= 5; ++i) {
        char file_name[50];
        snprintf(file_name, sizeof(file_name), "output_c_%d.txt", i);

        printf("Test case %d: Writing to %s...", i, file_name);
        int result = generate_and_write_to_file(file_name);
        
        if (result == 0) {
            printf(" Succeeded.\n");
            FILE *f = fopen(file_name, "r");
            if (f) {
                char content[TOTAL_BUFFER_SIZE] = {0};
                if(fgets(content, sizeof(content), f)) {
                    // remove trailing newline if any
                    content[strcspn(content, "\n")] = 0;
                    printf("  -> Content: %s\n", content);
                }
                fclose(f);
            }
        } else {
            printf(" Failed.\n");
        }
    }
    return 0;
}