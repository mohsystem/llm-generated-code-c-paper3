
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>

#include "../../../../../../../usr/include/stdint.h"

#define MAX_PATH_LEN 4096
#define MAX_FILE_SIZE (10 * 1024 * 1024) // 10 MB limit
#define BUFFER_SIZE 8192
#define MAX_FILES 100

// Thread-safe file queue structure
typedef struct {
    char files[MAX_FILES][MAX_PATH_LEN];
    int count;
    int next_index;
    pthread_mutex_t mutex;
} FileQueue;

// Global file queue
static FileQueue g_file_queue;
static int g_base_dirfd = -1;

// Explicit zero function for sensitive data - compiler cannot optimize away
static void explicit_zero(void* ptr, size_t len) {
    volatile unsigned char* p = (volatile unsigned char*)ptr;
    while (len--) {
        *p++ = 0;
    }
}

// Initialize file queue with mutex
static int init_file_queue(FileQueue* queue) {
    if (!queue) return -1;
    
    memset(queue, 0, sizeof(FileQueue));
    
    // Initialize mutex with error checking
    pthread_mutexattr_t attr;
    if (pthread_mutexattr_init(&attr) != 0) {
        return -1;
    }
    
    if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK) != 0) {
        pthread_mutexattr_destroy(&attr);
        return -1;
    }
    
    if (pthread_mutex_init(&queue->mutex, &attr) != 0) {
        pthread_mutexattr_destroy(&attr);
        return -1;
    }
    
    pthread_mutexattr_destroy(&attr);
    return 0;
}

// Cleanup file queue
static void cleanup_file_queue(FileQueue* queue) {
    if (!queue) return;
    pthread_mutex_destroy(&queue->mutex);
}
// Validate and normalize path to ensure it's within base directory
static int validate_path(const char* base_dir,
                         const char* rel_path,
                         char* normalized,
                         size_t norm_size) {
    if (!base_dir || !rel_path || !normalized || norm_size == 0) {
        return -1;
    }

    // Check for empty or invalid relative path
    if (rel_path[0] == '\0' || rel_path[0] == '/' || strstr(rel_path, "..") != NULL) {
        return -1;
    }

    // Ensure path doesn't exceed maximum length
    size_t base_len = strlen(base_dir);
    size_t rel_len  = strlen(rel_path);
    if (base_len + rel_len + 2 > norm_size) {
        return -1;
    }

    // Construct normalized path
    int written = snprintf(normalized, norm_size, "%s/%s", base_dir, rel_path);
    if (written < 0 || (size_t)written >= norm_size) {
        return -1;
    }

    return 0;
}


// Add file to queue (thread-safe)
static int enqueue_file(FileQueue* queue, const char* filename) {
    if (!queue || !filename) return -1;
    
    // Validate filename length
    size_t len = strlen(filename);
    if (len == 0 || len >= MAX_PATH_LEN) {
        return -1;
    }
    
    int result = pthread_mutex_lock(&queue->mutex);
    if (result != 0) {
        return -1;
    }
    
    if (queue->count >= MAX_FILES) {
        pthread_mutex_unlock(&queue->mutex);
        return -1;
    }
    
    // Safe copy with bounds check
    strncpy(queue->files[queue->count], filename, MAX_PATH_LEN - 1);
    queue->files[queue->count][MAX_PATH_LEN - 1] = '\0';
    queue->count++;
    
    pthread_mutex_unlock(&queue->mutex);
    return 0;
}

// Get next file from queue (thread-safe)
static int dequeue_file(FileQueue* queue, char* filename, size_t size) {
    if (!queue || !filename || size == 0) return -1;
    
    int result = pthread_mutex_lock(&queue->mutex);
    if (result != 0) {
        return -1;
    }
    
    if (queue->next_index >= queue->count) {
        pthread_mutex_unlock(&queue->mutex);
        return -1; // No more files
    }
    
    // Safe copy with bounds check
    strncpy(filename, queue->files[queue->next_index], size - 1);
    filename[size - 1] = '\0';
    queue->next_index++;
    
    pthread_mutex_unlock(&queue->mutex);
    return 0;
}
// Process a single file safely - open first, validate, then operate
static int process_file_safe(const char* rel_path) {
    if (!rel_path || g_base_dirfd < 0) {
        fprintf(stderr, "Invalid parameters\n");
        return -1;
    }

    // Open file using openat to prevent TOCTOU, with O_NOFOLLOW to reject symlinks
    int fd = openat(g_base_dirfd, rel_path, O_RDONLY | O_CLOEXEC | O_NOFOLLOW);
    if (fd < 0) {
        if (errno == ELOOP) {
            fprintf(stderr, "Symlink rejected: %s\n", rel_path);
        } else {
            fprintf(stderr, "Failed to open file: %s\n", rel_path);
        }
        return -1;
    }

    // Validate the opened file descriptor with fstat (no TOCTOU)
    struct stat st;
    if (fstat(fd, &st) != 0) {
        fprintf(stderr, "Failed to stat opened file\n");
        close(fd);
        return -1;
    }

    // Ensure it's a regular file
    if (!S_ISREG(st.st_mode)) {
        fprintf(stderr, "Not a regular file: %s\n", rel_path);
        close(fd);
        return -1;
    }

    // Check file size limit
    if (st.st_size > MAX_FILE_SIZE || st.st_size < 0) {
        fprintf(stderr, "File size invalid or exceeds limit: %s\n", rel_path);
        close(fd);
        return -1;
    }

    // Use fdopen to get FILE* from the validated fd (no reopening by path)
    FILE* file = fdopen(fd, "rb");
    if (!file) {
        fprintf(stderr, "Failed to fdopen\n");
        close(fd);
        return -1;
    }

    // Process file with bounded buffer
    unsigned char* buffer = (unsigned char*)malloc(BUFFER_SIZE);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file); // This also closes fd
        return -1;
    }

    size_t total_bytes = 0;
    size_t bytes_read;

    // Read and process file in chunks with bounds checking
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        // Check for integer overflow
        if (total_bytes > SIZE_MAX - bytes_read) {
            fprintf(stderr, "Integer overflow detected\n");
            explicit_zero(buffer, BUFFER_SIZE);
            free(buffer);
            fclose(file);
            return -1;
        }

        total_bytes += bytes_read;

        // Simulate processing (e.g., checksum, transformation)
        // In real use, process buffer data here
    }

    // Check for read errors
    if (ferror(file)) {
        fprintf(stderr, "Error reading file: %s\n", rel_path);
        explicit_zero(buffer, BUFFER_SIZE);
        free(buffer);
        fclose(file);
        return -1;
    }

    printf("Successfully processed %s: %zu bytes\n", rel_path, total_bytes);

    // Clear sensitive buffer before freeing
    explicit_zero(buffer, BUFFER_SIZE);
    free(buffer);
    fclose(file); // Closes underlying fd

    return 0;
}

// Worker thread function
static void* worker_thread(void* arg) {
    (void)arg; // Unused parameter

    char filename[MAX_PATH_LEN];

    while (1) {
        // Get next file from queue
        if (dequeue_file(&g_file_queue, filename, sizeof(filename)) != 0) {
            break; // No more files
        }

        // Process the file safely
        process_file_safe(filename);
    }

    return NULL;
}

// Scan directory and add files to queue
static int scan_directory(const char* dir_path) {
    if (!dir_path) return -1;

    // Open directory using validated path
    DIR* dir = opendir(dir_path);
    if (!dir) {
        fprintf(stderr, "Failed to open directory: %s\n", dir_path);
        return -1;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Validate filename doesn't contain path traversal
        if (strstr(entry->d_name, "..") != NULL || strchr(entry->d_name, '/') != NULL) {
            continue;
        }

        // Add to queue
        if (enqueue_file(&g_file_queue, entry->d_name) != 0) {
            fprintf(stderr, "Failed to enqueue file: %s\n", entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}

// Main processing function
int process_files_concurrent(const char* directory, int num_threads) {
    if (!directory || num_threads <= 0 || num_threads > 64) {
        fprintf(stderr, "Invalid parameters\\n");
        return -1;
    }
    
    // Validate directory path length
    size_t dir_len = strlen(directory);
    if (dir_len == 0 || dir_len >= MAX_PATH_LEN) {
        fprintf(stderr, "Invalid directory path length\\n");
        return -1;
    }
    
    // Open base directory and keep fd for openat operations
    g_base_dirfd = open(directory, O_RDONLY | O_DIRECTORY | O_CLOEXEC);
    if (g_base_dirfd < 0) {
        fprintf(stderr, "Failed to open base directory: %s\\n", directory);
        return -1;
    }
    
    // Initialize file queue
    if (init_file_queue(&g_file_queue) != 0) {
        fprintf(stderr, "Failed to initialize file queue\\n");
        close(g_base_dirfd);
        g_base_dirfd = -1;
        return -1;
    }
    
    // Scan directory and populate queue
    if (scan_directory(directory) != 0) {
        cleanup_file_queue(&g_file_queue);
        close(g_base_dirfd);
        g_base_dirfd = -1;
        return -1;
    }
    
    printf("Found %d files to process\\n", g_file_queue.count);
    
    if (g_file_queue.count == 0) {
        cleanup_file_queue(&g_file_queue);
        close(g_base_dirfd);
        g_base_dirfd = -1;
        return 0;
    }
    
    // Create worker threads
    pthread_t* threads = (pthread_t*)calloc((size_t)num_threads, sizeof(pthread_t));
    if (!threads) {
        fprintf(stderr, "Failed to allocate thread array\\n");
        cleanup_file_queue(&g_file_queue);
        close(g_base_dirfd);
        g_base_dirfd = -1;
        return -1;
    }
    
    // Start threads
    for (int i = 0; i < num_threads; i++) {
        if (pthread_create(&threads[i], NULL, worker_thread, NULL) != 0) {
            fprintf(stderr, "Failed to create thread %d\\n", i);
            // Wait for already created threads
            for (int j = 0; j < i; j++) {
                pthread_join(threads[j], NULL);
            }
            free(threads);
            cleanup_file_queue(&g_file_queue);
            close(g_base_dirfd);
            g_base_dirfd = -1;
            return -1;
        }
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    free(threads);
    cleanup_file_queue(&g_file_queue);
    close(g_base_dirfd);
    g_base_dirfd = -1;
    
    return 0;
}

// Test helper: create test files
static int create_test_file(const char* dir, const char* filename, const char* content) {
    char path[MAX_PATH_LEN];
    if (validate_path(dir, filename, path, sizeof(path)) != 0) {
        return -1;
    }
    
    FILE* f = fopen(path, "wb");
    if (!f) return -1;
    
    if (content) {
        size_t len = strlen(content);
        if (fwrite(content, 1, len, f) != len) {
            fclose(f);
            return -1;
        }
    }
    
    if (fflush(f) != 0 || fclose(f) != 0) {
        return -1;
    }
    
    return 0;
}

int main(void) {
    printf("=== Concurrent File Processing System Test ===\\n\\n");
    
    // Test case 1: Process multiple files with 4 threads
    printf("Test 1: Processing files with 4 threads\\n");
    system("mkdir -p test_dir1 && rm -f test_dir1/*");
    create_test_file("test_dir1", "file1.txt", "Content of file 1");
    create_test_file("test_dir1", "file2.txt", "Content of file 2");
    create_test_file("test_dir1", "file3.txt", "Content of file 3");
    create_test_file("test_dir1", "file4.txt", "Content of file 4");
    create_test_file("test_dir1", "file5.txt", "Content of file 5");
    
    if (process_files_concurrent("test_dir1", 4) == 0) {
        printf("Test 1: PASSED\\n\\n");
    } else {
        printf("Test 1: FAILED\\n\\n");
    }
    
    // Test case 2: Single thread processing
    printf("Test 2: Processing files with 1 thread\\n");
    system("mkdir -p test_dir2 && rm -f test_dir2/*");
    create_test_file("test_dir2", "data1.txt", "Test data 1");
    create_test_file("test_dir2", "data2.txt", "Test data 2");
    
    if (process_files_concurrent("test_dir2", 1) == 0) {
        printf("Test 2: PASSED\\n\\n");
    } else {
        printf("Test 2: FAILED\\n\\n");
    }
    
    // Test case 3: Empty directory
    printf("Test 3: Processing empty directory\\n");
    system("mkdir -p test_dir3 && rm -f test_dir3/*");
    
    if (process_files_concurrent("test_dir3", 2) == 0) {
        printf("Test 3: PASSED\\n\\n");
    } else {
        printf("Test 3: FAILED\\n\\n");
    }
    
    // Test case 4: Many small files
    printf("Test 4: Processing many small files\\n");
    system("mkdir -p test_dir4 && rm -f test_dir4/*");
    for (int i = 0; i < 20; i++) {
        char fname[32];
        snprintf(fname, sizeof(fname), "file%d.txt", i);
        create_test_file("test_dir4", fname, "Small file content");
    }
    
    if (process_files_concurrent("test_dir4", 8) == 0) {
        printf("Test 4: PASSED\\n\\n");
    } else {
        printf("Test 4: FAILED\\n\\n");
    }
    
    // Test case 5: Invalid directory
    printf("Test 5: Invalid directory handling\\n");
    if (process_files_concurrent("nonexistent_dir", 2) != 0) {
        printf("Test 5: PASSED (correctly rejected invalid directory)\\n\\n");
    } else {
        printf("Test 5: FAILED\\n\\n");
    }
    
    // Cleanup
    system("rm -rf test_dir1 test_dir2 test_dir3 test_dir4");
    
    printf("=== All tests completed ===\\n");
    return 0;
}
