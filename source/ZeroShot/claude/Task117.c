
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <minizip/unzip.h>

#define BUFFER_SIZE 4096
#define MAX_FILENAME 256

typedef struct {
    const char* zip_path;
    const char* dest_path;
} ExtractArgs;

static int create_directory(const char* path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
#ifdef _WIN32
        return _mkdir(path);
#else
        return mkdir(path, 0755);
#endif
    }
    return 0;
}

static int is_path_safe(const char* base_path, const char* target_path) {
    char real_base[PATH_MAX];
    char real_target[PATH_MAX];
    
    if (!realpath(base_path, real_base) || !realpath(target_path, real_target)) {
        return 0;
    }
    
    return strncmp(real_base, real_target, strlen(real_base)) == 0;
}

static int extract_zip_file(const char* zip_path, const char* dest_path) {
    unzFile zip_file = unzOpen(zip_path);
    if (!zip_file) {
        fprintf(stderr, "Failed to open zip file: %s\\n", zip_path);
        return -1;
    }

    if (create_directory(dest_path) != 0) {
        fprintf(stderr, "Failed to create destination directory\\n");
        unzClose(zip_file);
        return -1;
    }

    unz_global_info global_info;
    if (unzGetGlobalInfo(zip_file, &global_info) != UNZ_OK) {
        fprintf(stderr, "Failed to get zip file info\\n");
        unzClose(zip_file);
        return -1;
    }

    char read_buffer[BUFFER_SIZE];
    
    for (unsigned long i = 0; i < global_info.number_entry; ++i) {
        char filename[MAX_FILENAME];
        unz_file_info file_info;
        
        if (unzGetCurrentFileInfo(zip_file, &file_info, filename, MAX_FILENAME, 
                                 NULL, 0, NULL, 0) != UNZ_OK) {
            fprintf(stderr, "Failed to get file info\\n");
            unzClose(zip_file);
            return -1;
        }

        char full_path[PATH_MAX];
        snprintf(full_path, PATH_MAX, "%s/%s", dest_path, filename);

        // Check for path traversal
        if (!is_path_safe(dest_path, full_path)) {
            fprintf(stderr, "Path traversal attempt detected\\n");
            unzClose(zip_file);
            return -1;
        }

        // Create directory for files in subdirectories
        char* last_slash = strrchr(full_path, '/');
        if (last_slash != NULL) {
            *last_slash = '\\0';
            create_directory(full_path);
            *last_slash = '/';
        }

        if (filename[strlen(filename) - 1] != '/') {
            if (unzOpenCurrentFile(zip_file) != UNZ_OK) {
                fprintf(stderr, "Failed to open file in zip\\n");
                unzClose(zip_file);
                return -1;
            }

            FILE* out_file = fopen(full_path, "wb");
            if (!out_file) {
                fprintf(stderr, "Failed to create output file\\n");
                unzCloseCurrentFile(zip_file);
                unzClose(zip_file);
                return -1;
            }

            int bytes_read;
            do {
                bytes_read = unzReadCurrentFile(zip_file, read_buffer, BUFFER_SIZE);
                if (bytes_read < 0) {
                    fprintf(stderr, "Error reading zip file\\n");
                    fclose(out_file);
                    unzCloseCurrentFile(zip_file);
                    unzClose(zip_file);
                    return -1;
                }

                if (bytes_read > 0) {
                    if (fwrite(read_buffer, bytes_read, 1, out_file) != 1) {
                        fprintf(stderr, "Failed to write to output file\\n");
                        fclose(out_file);
                        unzCloseCurrentFile(zip_file);
                        unzClose(zip_file);
                        return -1;
                    }
                }
            } while (bytes_read > 0);

            fclose(out_file);
            unzCloseCurrentFile(zip_file);
        }

        if ((i + 1) < global_info.number_entry) {
            if (unzGoToNextFile(zip_file) != UNZ_OK) {
                fprintf(stderr, "Failed to read next file\\n");
                unzClose(zip_file);
                return -1;
            }
        }
    }

    unzClose(zip_file);
    return 0;
}

int main() {
    const char* dest_dir = "extracted_files";

    // Test case 1: Extract simple zip file
    extract_zip_file("test1.zip", dest_dir);

    // Test case 2: Extract zip with nested directories
    extract_zip_file("test2.zip", dest_dir);

    // Test case 3: Extract large zip file
    extract_zip_file("test3.zip", dest_dir);

    // Test case 4: Extract zip with special characters
    extract_zip_file("test4.zip", dest_dir);

    // Test case 5: Extract zip with potential path traversal
    extract_zip_file("test5.zip", dest_dir);

    return 0;
}
