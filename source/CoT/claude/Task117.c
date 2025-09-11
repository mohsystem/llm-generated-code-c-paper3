
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <minizip/unzip.h>

#define MAX_FILENAME 256
#define BUFFER_SIZE 8192

// Function to check if a path is safe (prevent zip slip)
int is_path_safe(const char* base_path, const char* file_path) {
    char resolved_base[PATH_MAX];
    char resolved_file[PATH_MAX];
    
    if (!realpath(base_path, resolved_base)) {
        return 0;
    }
    
    if (!realpath(file_path, resolved_file)) {
        // If file doesn't exist yet, check its parent directory\n        char parent_dir[PATH_MAX];\n        strcpy(parent_dir, file_path);\n        char* last_slash = strrchr(parent_dir, '/');\n        if (last_slash) {\n            *last_slash = '\\0';\n            if (!realpath(parent_dir, resolved_file)) {\n                return 0;\n            }\n        }\n    }\n    \n    return strncmp(resolved_base, resolved_file, strlen(resolved_base)) == 0;\n}\n\n// Function to create directory recursively\nvoid create_directories(const char* path) {\n    char tmp[256];\n    char* p = NULL;\n    size_t len;\n    \n    snprintf(tmp, sizeof(tmp), "%s", path);\n    len = strlen(tmp);\n    if (tmp[len - 1] == '/')\n        tmp[len - 1] = 0;\n    \n    for (p = tmp + 1; *p; p++) {\n        if (*p == '/') {\n            *p = 0;\n            mkdir(tmp, 0755);\n            *p = '/';\n        }\n    }\n    mkdir(tmp, 0755);\n}\n\nint extract_zip_file(const char* zip_path, const char* dest_dir) {\n    if (!zip_path || !dest_dir) {\n        return 0;\n    }\n    \n    unzFile zip_file = unzOpen(zip_path);\n    if (!zip_file) {\n        return 0;\n    }\n    \n    // Create destination directory\n    create_directories(dest_dir);\n    \n    unz_global_info global_info;\n    if (unzGetGlobalInfo(zip_file, &global_info) != UNZ_OK) {\n        unzClose(zip_file);\n        return 0;\n    }\n    \n    char read_buffer[BUFFER_SIZE];\n    \n    // Loop through each file in the archive\n    for (unsigned long i = 0; i < global_info.number_entry; i++) {\n        char filename[MAX_FILENAME];\n        unz_file_info file_info;\n        \n        if (unzGetCurrentFileInfo(zip_file, &file_info, filename, MAX_FILENAME,\n                                NULL, 0, NULL, 0) != UNZ_OK) {\n            unzClose(zip_file);\n            return 0;\n        }\n        \n        char full_path[PATH_MAX];\n        snprintf(full_path, PATH_MAX, "%s/%s", dest_dir, filename);\n        \n        // Check for zip slip\n        if (!is_path_safe(dest_dir, full_path)) {\n            unzClose(zip_file);\n            return 0;\n        }\n        \n        // Check if this is a directory\n        if (filename[strlen(filename) - 1] == '/') {\n            create_directories(full_path);\n        } else {\n            // Create parent directories\n            char parent_dir[PATH_MAX];\n            strcpy(parent_dir, full_path);\n            char* last_slash = strrchr(parent_dir, '/');\n            if (last_slash) {\n                *last_slash = '\\0';
                create_directories(parent_dir);
            }
            
            // Extract file
            if (unzOpenCurrentFile(zip_file) != UNZ_OK) {
                unzClose(zip_file);
                return 0;
            }
            
            FILE* out_file = fopen(full_path, "wb");
            if (!out_file) {
                unzCloseCurrentFile(zip_file);
                unzClose(zip_file);
                return 0;
            }
            
            int error = UNZ_OK;
            do {
                error = unzReadCurrentFile(zip_file, read_buffer, BUFFER_SIZE);
                if (error < 0) {
                    unzCloseCurrentFile(zip_file);
                    unzClose(zip_file);
                    fclose(out_file);
                    return 0;
                }
                
                if (error > 0) {
                    if (fwrite(read_buffer, error, 1, out_file) != 1) {
                        unzCloseCurrentFile(zip_file);
                        unzClose(zip_file);
                        fclose(out_file);
                        return 0;
                    }
                }
            } while (error > 0);
            
            fclose(out_file);
            unzCloseCurrentFile(zip_file);
        }
        
        if ((i + 1) < global_info.number_entry) {
            if (unzGoToNextFile(zip_file) != UNZ_OK) {
                unzClose(zip_file);
                return 0;
            }
        }
    }
    
    unzClose(zip_file);
    return 1;
}

int main() {
    // Test cases
    const char* test_files[] = {
        "test1.zip",
        "test2.zip",
        "test3.zip",
        "test4.zip",
        "test5.zip"
    };
    
    const char* dest_dir = "extracted_files";
    
    for (int i = 0; i < 5; i++) {
        int result = extract_zip_file(test_files[i], dest_dir);
        printf("Extracting %s: %s\\n", test_files[i], result ? "Success" : "Failed");
    }
    
    return 0;
}
