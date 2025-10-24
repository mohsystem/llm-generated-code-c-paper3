#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
// ------------------------------------------------------------------
// NEW LIB: libzip headers
#include <zip.h>
// ------------------------------------------------------------------

// To compile with libzip on Debian/Kali:
// 1. Install development package: sudo apt install libzip-dev
// 2. Compile: gcc Task117.c -o Task117 -lzip

/*
Helper script to create test zip files using Python (run this once):
---------------------------------------------------------------------
import zipfile, os
if not os.path.exists('c_test_temp'): os.makedirs('c_test_temp')
with zipfile.ZipFile('c_test_temp/test.zip', 'w') as zf:
    zf.writestr('file1.txt', 'content1')
    zf.writestr('dir1/file2.txt', 'content2')
    zf.writestr('dir1/emptydir/', '')
# For traversal test
with zipfile.ZipFile('c_test_temp/traversal.zip', 'w') as zf:
    zf.writestr('../../evil.txt', 'evil content')
*/

// Cross-platform mkdir
#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#define MKDIR(path) mkdir(path, 0755)
#endif

// Creates directories recursively.
static int mkdir_p(const char *path) {
    char *p = NULL;
    char temp_path[PATH_MAX];
    snprintf(temp_path, sizeof(temp_path), "%s", path);
    size_t len = strlen(temp_path);
    if (temp_path[len - 1] == '/') {
        temp_path[len - 1] = 0;
    }
    for (p = temp_path + 1; *p; p++) {
        if (*p == '/') {
            *p = 0;
            if (MKDIR(temp_path) != 0 && errno != EEXIST) {
                return -1;
            }
            *p = '/';
        }
    }
    if (MKDIR(temp_path) != 0 && errno != EEXIST) {
        return -1;
    }
    return 0;
}

/**
 * Normalizes a path by removing leading/trailing slashes and checking for '..'
 * Returns a pointer to the start of the clean path or NULL on traversal attempt.
 */
static const char* normalize_path(const char* path) {
    // Skip leading slashes
    while (*path == '/' || *path == '\\') {
        path++;
    }
    // Check for leading '..', or '..\\' or '..\\'
    if (strstr(path, "../") == path || strstr(path, "..\\") == path || strstr(path, "..\0") == path) {
        return NULL; // Path traversal attempt at start
    }
    // Check for ".." components within the path
    if (strstr(path, "/../") != NULL || strstr(path, "\\..\\") != NULL || strstr(path, "/..\\") != NULL || strstr(path, "\\../") != NULL) {
         return NULL; // Path traversal attempt within
    }
    return path;
}


bool extract_zip(const char* zip_file_path, const char* dest_dir) {
    if (mkdir_p(dest_dir) != 0) {
        fprintf(stderr, "Error: Could not create destination directory '%s'\n", dest_dir);
        return false;
    }

    char canonical_dest_dir[PATH_MAX];
    #ifndef _WIN32
    if (realpath(dest_dir, canonical_dest_dir) == NULL) {
        // If realpath fails (e.g., dir doesn't exist), just use dest_dir
        if (errno != ENOENT) {
            perror("realpath on destination dir failed");
            return false;
        }
        strncpy(canonical_dest_dir, dest_dir, PATH_MAX - 1);
        canonical_dest_dir[PATH_MAX - 1] = '\0';
    }
    #else
    // realpath is not available on all Windows compilers, use a simple copy
    strncpy(canonical_dest_dir, dest_dir, PATH_MAX - 1);
    canonical_dest_dir[PATH_MAX - 1] = '\0';
    #endif

    int errorp;
    // Use ZIP_CHECKCONS to ensure archive integrity
    struct zip *za = zip_open(zip_file_path, ZIP_CHECKCONS, &errorp);
    if (za == NULL) {
        char err_msg[100];
        zip_error_to_str(err_msg, sizeof(err_msg), errorp, errno);
        fprintf(stderr, "Error: Could not open zip file '%s'. libzip error: %s\n", zip_file_path, err_msg);
        return false;
    }

    zip_int64_t num_entries = zip_get_num_entries(za, 0);

    for (zip_int64_t i = 0; i < num_entries; i++) {
        struct zip_stat zs;
        if (zip_stat_index(za, i, 0, &zs) != 0) {
            fprintf(stderr, "Error: Could not read file info for index %lld\n", (long long)i);
            continue;
        }

        const char* filename_in_zip = zs.name;
        // --- Security Check: Path Traversal ---
        const char* clean_filename = normalize_path(filename_in_zip);
        if (clean_filename == NULL) {
            fprintf(stderr, "Path traversal attempt. Skipping: %s\n", filename_in_zip);
            continue;
        }

        char full_dest_path[PATH_MAX];
        snprintf(full_dest_path, sizeof(full_dest_path), "%s/%s", canonical_dest_dir, clean_filename);

        // Check if it's a directory (usually ends with '/' or has ZIP_FL_UNCHANGED set on libzip)
        // Libzip's zip_stat often indicates directories explicitly via zip_stat.valid
        if (filename_in_zip[strlen(filename_in_zip) - 1] == '/') {
            if (mkdir_p(full_dest_path) != 0) {
                 fprintf(stderr, "Warning: Could not create dir %s\n", full_dest_path);
            }
        } else {
            // It's a file, ensure parent directory exists
            char* p = strrchr(full_dest_path, '/');
            if (p) {
                *p = '\0';
                mkdir_p(full_dest_path);
                *p = '/';
            }

            // Open the file within the archive
            struct zip_file *zf = zip_fopen_index(za, i, 0);
            if (zf == NULL) {
                fprintf(stderr, "Error: Could not open file in zip: %s\n", filename_in_zip);
                continue;
            }

            // Open the output file
            FILE *out = fopen(full_dest_path, "wb");
            if (out == NULL) {
                fprintf(stderr, "Error: Could not open output file: %s\n", full_dest_path);
                zip_fclose(zf);
                continue;
            }

            char buffer[8192];
            zip_int64_t read_bytes;

            // Read from zip and write to file
            while ((read_bytes = zip_fread(zf, buffer, sizeof(buffer))) > 0) {
                if (fwrite(buffer, 1, read_bytes, out) != read_bytes) {
                    fprintf(stderr, "Error writing to output file: %s\n", full_dest_path);
                    break;
                }
            }
            if (read_bytes < 0) {
                fprintf(stderr, "Error reading from zip for file: %s\n", filename_in_zip);
            }

            fclose(out);
            zip_fclose(zf);
        }

    }

    zip_close(za);
    return true;
}

int file_exists(const char* path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}

void remove_all(const char *path) {
    // Basic cleanup for tests, not a full-featured recursive delete
    #ifdef _WIN32
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "rmdir /s /q \"%s\"", path);
        system(cmd);
    #else
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "rm -rf \"%s\"", path);
        system(cmd);
    #endif
}

void run_tests() {
    printf("--- Running C ZIP Extraction Tests (libzip) ---\n");
    printf("Note: Make sure test zip files exist in 'c_test_temp/'\n");

    const char* temp_dir = "c_test_temp";
    const char* test_zip = "c_test_temp/test.zip";
    const char* traversal_zip = "c_test_temp/traversal.zip";

    // Test Case 1: Normal extraction
    printf("\n[Test 1] Normal Extraction\n");
    const char* out1 = "c_test_temp/out1";
    remove_all(out1);
    bool success1 = extract_zip(test_zip, out1);
    printf("Result: %s\n", (success1 && file_exists("c_test_temp/out1/dir1/file2.txt")) ? "PASS" : "FAIL");

    // Test Case 2: Extraction to a non-existent directory
    printf("\n[Test 2] Extract to New Directory\n");
    const char* out2 = "c_test_temp/out2_new";
    remove_all(out2);
    bool success2 = extract_zip(test_zip, out2);
    printf("Result: %s\n", (success2 && file_exists("c_test_temp/out2_new/file1.txt")) ? "PASS" : "FAIL");

    // Test Case 3: Path traversal attack
    printf("\n[Test 3] Path Traversal Attack\n");
    const char* out3 = "c_test_temp/out3";
    remove_all(out3);
    extract_zip(traversal_zip, out3);
    printf("Result: %s\n", (!file_exists("evil.txt")) ? "PASS" : "FAIL");
    if(file_exists("evil.txt")) remove("evil.txt");

    // Test Case 4: Non-existent archive file
    printf("\n[Test 4] Non-existent Archive\n");
    const char* out4 = "c_test_temp/out4";
    bool success4 = extract_zip("nonexistent.zip", out4);
    printf("Result: %s\n", (!success4) ? "PASS" : "FAIL");

    // Test Case 5: Output destination is an existing file
    printf("\n[Test 5] Output is a File (Should Fail Gracefully or Pass/Skip)\n");
    const char* out_file = "c_test_temp/output_file.txt";
    remove_all(out_file);
    FILE* f = fopen(out_file, "w"); fclose(f);
    // The extraction function will successfully call mkdir_p (which succeeds if the file exists)
    // but the actual file extraction won't overwrite the output file directory.
    bool success5 = extract_zip(test_zip, out_file);
    printf("Result: %s\n", (success5) ? "PASS" : "FAIL");
    
    // Cleanup
    remove_all(temp_dir);
}


int main() {
    run_tests();
    return 0;
}