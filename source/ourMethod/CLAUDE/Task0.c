#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#define PATH_SEPARATOR '\\'
#else
#include <libgen.h>
#define PATH_SEPARATOR '/'
#endif

/* Security constants */
#define MAX_FILE_SIZE (100 * 1024 * 1024)  /* 100MB limit */
#define MAX_PATH_LENGTH 4096
#define BUFFER_CHUNK_SIZE 8192
#define MAX_FILES 100

/* File mutex entry for tracking per-file locks */
typedef struct FileMutexEntry {
    char path[MAX_PATH_LENGTH];
    pthread_mutex_t mutex;
    bool initialized;
} FileMutexEntry;

/* Main processor system structure */
typedef struct FileProcessorSystem {
    char base_directory[MAX_PATH_LENGTH];
    FileMutexEntry file_mutexes[MAX_FILES];
    size_t mutex_count;
    pthread_mutex_t map_mutex;  /* Protects file_mutexes array */
} FileProcessorSystem;

/* Thread argument structure */
typedef struct ThreadArg {
    FileProcessorSystem* system;
    char relative_path[MAX_PATH_LENGTH];
} ThreadArg;

/* Securely clear memory before freeing (prevents sensitive data leaks) */
static void secure_clear(void* ptr, size_t size) {
    if (ptr == NULL || size == 0) return;
#ifdef __STDC_LIB_EXT1__
    memset_s(ptr, size, 0, size);
#else
    volatile unsigned char* p = (volatile unsigned char*)ptr;
    while (size--) *p++ = 0;
#endif
}

/* Normalize and validate path to prevent directory traversal (CWE-22) */
static bool normalize_path(const char* path, char* normalized, size_t norm_size) {
    if (path == NULL || normalized == NULL || norm_size == 0) {
        return false;
    }

    size_t path_len = strnlen(path, MAX_PATH_LENGTH + 1);
    if (path_len == 0 || path_len > MAX_PATH_LENGTH) {
        return false;
    }

    char* result = realpath(path, NULL);
    if (result == NULL) {
        return false;
    }

    size_t result_len = strnlen(result, MAX_PATH_LENGTH + 1);
    if (result_len >= norm_size || result_len > MAX_PATH_LENGTH) {
        free(result);
        return false;
    }

    if (snprintf(normalized, norm_size, "%s", result) < 0) {
        free(result);
        return false;
    }

    free(result);
    return true;
}

/* Validate path is within base directory and is a regular file */
static bool validate_path(FileProcessorSystem* system, const char* relative_path,
                          char* normalized_path, size_t norm_size) {
    if (system == NULL || relative_path == NULL || normalized_path == NULL) {
        return false;
    }

    size_t rel_path_len = strnlen(relative_path, MAX_PATH_LENGTH + 1);
    if (rel_path_len == 0 || rel_path_len > MAX_PATH_LENGTH) {
        return false;
    }

    char full_path[MAX_PATH_LENGTH];
    int written = snprintf(full_path, sizeof(full_path), "%s%c%s",
                           system->base_directory, PATH_SEPARATOR, relative_path);
    if (written < 0 || written >= (int)sizeof(full_path)) {
        return false;
    }

    if (!normalize_path(full_path, normalized_path, norm_size)) {
        return false;
    }

    size_t base_len = strnlen(system->base_directory, MAX_PATH_LENGTH);
    size_t norm_len = strnlen(normalized_path, MAX_PATH_LENGTH);

    if (norm_len < base_len ||
        strncmp(normalized_path, system->base_directory, base_len) != 0) {
        return false;
    }

    struct stat st;
    if (lstat(normalized_path, &st) != 0) {
        return false;
    }

    if (!S_ISREG(st.st_mode) || S_ISLNK(st.st_mode)) {
        return false;
    }

    return true;
}

/* Get or create mutex for specific file */
static pthread_mutex_t* get_file_mutex(FileProcessorSystem* system, const char* file_path) {
    if (system == NULL || file_path == NULL) {
        return NULL;
    }

    pthread_mutex_lock(&system->map_mutex);

    for (size_t i = 0; i < system->mutex_count; i++) {
        if (system->file_mutexes[i].initialized &&
            strncmp(system->file_mutexes[i].path, file_path, MAX_PATH_LENGTH) == 0) {
            pthread_mutex_unlock(&system->map_mutex);
            return &system->file_mutexes[i].mutex;
        }
    }

    if (system->mutex_count < MAX_FILES) {
        FileMutexEntry* entry = &system->file_mutexes[system->mutex_count];

        pthread_mutexattr_t attr;
        if (pthread_mutexattr_init(&attr) != 0) {
            pthread_mutex_unlock(&system->map_mutex);
            return NULL;
        }
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);

        if (pthread_mutex_init(&entry->mutex, &attr) != 0) {
            pthread_mutexattr_destroy(&attr);
            pthread_mutex_unlock(&system->map_mutex);
            return NULL;
        }
        pthread_mutexattr_destroy(&attr);

        if (snprintf(entry->path, sizeof(entry->path), "%s", file_path) < 0) {
            pthread_mutex_destroy(&entry->mutex);
            pthread_mutex_unlock(&system->map_mutex);
            return NULL;
        }

        entry->initialized = true;
        system->mutex_count++;

        pthread_mutex_unlock(&system->map_mutex);
        return &entry->mutex;
    }

    pthread_mutex_unlock(&system->map_mutex);
    return NULL;
}

/* Initialize file processor system */
static bool init_file_processor(FileProcessorSystem* system, const char* base_dir) {
    if (system == NULL || base_dir == NULL) {
        return false;
    }

    memset(system, 0, sizeof(FileProcessorSystem));

    if (!normalize_path(base_dir, system->base_directory, sizeof(system->base_directory))) {
        return false;
    }

    struct stat st;
    if (stat(system->base_directory, &st) != 0 || !S_ISDIR(st.st_mode)) {
        return false;
    }

    pthread_mutexattr_t attr;
    if (pthread_mutexattr_init(&attr) != 0) {
        return false;
    }
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);

    if (pthread_mutex_init(&system->map_mutex, &attr) != 0) {
        pthread_mutexattr_destroy(&attr);
        return false;
    }
    pthread_mutexattr_destroy(&attr);

    system->mutex_count = 0;
    return true;
}

/* Cleanup file processor system */
static void cleanup_file_processor(FileProcessorSystem* system) {
    if (system == NULL) return;

    for (size_t i = 0; i < system->mutex_count; i++) {
        if (system->file_mutexes[i].initialized) {
            pthread_mutex_destroy(&system->file_mutexes[i].mutex);
        }
    }

    pthread_mutex_destroy(&system->map_mutex);
    secure_clear(system, sizeof(FileProcessorSystem));
}

/* Process file with exclusive lock */
static bool process_file(FileProcessorSystem* system, const char* relative_path) {
    if (system == NULL || relative_path == NULL) {
        return false;
    }

    char normalized_path[MAX_PATH_LENGTH];
    if (!validate_path(system, relative_path, normalized_path, sizeof(normalized_path))) {
        fprintf(stderr, "Invalid file path: %s\n", relative_path);
        return false;
    }

    pthread_mutex_t* file_mutex = get_file_mutex(system, normalized_path);
    if (file_mutex == NULL) {
        fprintf(stderr, "Failed to get file mutex\n");
        return false;
    }

    if (pthread_mutex_lock(file_mutex) != 0) {
        fprintf(stderr, "Failed to lock file mutex\n");
        return false;
    }

    bool success = false;
    FILE* file = NULL;
    char* buffer = NULL;
    size_t buffer_capacity = 0;
    size_t total_read = 0;

    struct stat st;
    if (stat(normalized_path, &st) != 0) {
        fprintf(stderr, "Failed to stat file: %s\n", normalized_path);
        goto cleanup;
    }

    if ((uintmax_t)st.st_size > MAX_FILE_SIZE) {
        fprintf(stderr, "File too large: %s\n", normalized_path);
        goto cleanup;
    }

    file = fopen(normalized_path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", normalized_path);
        goto cleanup;
    }

    buffer_capacity = BUFFER_CHUNK_SIZE;
    buffer = (char*)calloc(buffer_capacity, 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        goto cleanup;
    }

    while (total_read < MAX_FILE_SIZE) {
        if (total_read >= buffer_capacity) {
            size_t new_capacity = buffer_capacity + BUFFER_CHUNK_SIZE;
            if (new_capacity > MAX_FILE_SIZE) new_capacity = MAX_FILE_SIZE;
            if (new_capacity <= buffer_capacity) break;

            char* new_buffer = (char*)realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                goto cleanup;
            }

            memset(new_buffer + buffer_capacity, 0, new_capacity - buffer_capacity);
            buffer = new_buffer;
            buffer_capacity = new_capacity;
        }

        size_t to_read = BUFFER_CHUNK_SIZE;
        if (total_read + to_read > MAX_FILE_SIZE) to_read = MAX_FILE_SIZE - total_read;
        if (total_read + to_read > buffer_capacity) to_read = buffer_capacity - total_read;

        size_t actually_read = fread(buffer + total_read, 1, to_read, file);
        if (ferror(file)) {
            fprintf(stderr, "Read error on file: %s\n", normalized_path);
            goto cleanup;
        }

        total_read += actually_read;
        if (feof(file)) break;
    }

    printf("Thread %lu processed file: %s (%zu bytes)\n",
           (unsigned long)pthread_self(), relative_path, total_read);

    success = true;

cleanup:
    if (file != NULL) fclose(file);
    if (buffer != NULL) {
        secure_clear(buffer, buffer_capacity);
        free(buffer);
    }
    pthread_mutex_unlock(file_mutex);
    return success;
}

/* Thread function wrapper */
static void* thread_process_file(void* arg) {
    if (arg == NULL) return NULL;

    ThreadArg* thread_arg = (ThreadArg*)arg;
    process_file(thread_arg->system, thread_arg->relative_path);

    secure_clear(thread_arg, sizeof(ThreadArg));
    free(thread_arg);
    return NULL;
}

int main(void) {
    FileProcessorSystem system;
    const char* test_dir = "./test_concurrent_files_c";

#ifdef _WIN32
    _mkdir(test_dir);
#else
    mkdir(test_dir, 0755);
#endif

    const char* test_files[] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"};
    size_t num_files = sizeof(test_files) / sizeof(test_files[0]);

    for (size_t i = 0; i < num_files; i++) {
        char path[MAX_PATH_LENGTH];
        if (snprintf(path, sizeof(path), "%s%c%s", test_dir, PATH_SEPARATOR, test_files[i]) >= (int)sizeof(path)) {
            continue;
        }

        FILE* f = fopen(path, "w");
        if (f != NULL) {
            fprintf(f, "Test content for %s", test_files[i]);
            for (int j = 0; j < 1000; j++) fputc('X', f);
            fclose(f);
        }
    }

    if (!init_file_processor(&system, test_dir)) {
        fprintf(stderr, "Failed to initialize file processor\n");
        return 1;
    }

    printf("\n=== Test Case 1: Single file processing ===\n");
    process_file(&system, "file1.txt");

    printf("\n=== Test Case 2: Concurrent file processing ===\n");
    pthread_t threads[5];
    for (size_t i = 0; i < num_files; i++) {
        ThreadArg* arg = (ThreadArg*)calloc(1, sizeof(ThreadArg));
        if (arg != NULL) {
            arg->system = &system;
            snprintf(arg->relative_path, sizeof(arg->relative_path), "%s", test_files[i]);
            pthread_create(&threads[i], NULL, thread_process_file, arg);
        }
    }
    for (size_t i = 0; i < num_files; i++) pthread_join(threads[i], NULL);

    printf("\n=== Test Case 3: Multiple threads, same file ===\n");
    pthread_t same_file_threads[3];
    for (int i = 0; i < 3; i++) {
        ThreadArg* arg = (ThreadArg*)calloc(1, sizeof(ThreadArg));
        if (arg != NULL) {
            arg->system = &system;
            snprintf(arg->relative_path, sizeof(arg->relative_path), "file3.txt");
            pthread_create(&same_file_threads[i], NULL, thread_process_file, arg);
        }
    }
    for (int i = 0; i < 3; i++) pthread_join(same_file_threads[i], NULL);

    printf("\n=== Test Case 4: Directory traversal prevention ===\n");
    process_file(&system, "../etc/passwd");
    process_file(&system, "../../secret.txt");

    printf("\n=== Test Case 5: Non-existent file ===\n");
    process_file(&system, "nonexistent.txt");

    cleanup_file_processor(&system);

    for (size_t i = 0; i < num_files; i++) {
        char path[MAX_PATH_LENGTH];
        if (snprintf(path, sizeof(path), "%s%c%s", test_dir, PATH_SEPARATOR, test_files[i]) < (int)sizeof(path)) {
            remove(path);
        }
    }
    rmdir(test_dir);

    return 0;
}
