
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <sys/stat.h>

#define CHUNK 16384

void create_directory(const char* path) {
    #ifdef _WIN32
        _mkdir(path);
    #else
        mkdir(path, 0777);
    #endif
}

int extract_gzip(const char* src_file, const char* dest_path) {
    char buffer[CHUNK];
    char out_path[1024];
    FILE* out_file;
    gzFile in_file;
    int num_read = 0;
    
    create_directory(dest_path);
    
    in_file = gzopen(src_file, "rb");
    if (!in_file) {
        printf("Failed to open input file\\n");
        return -1;
    }
    
    snprintf(out_path, sizeof(out_path), "%s/extracted_file", dest_path);
    out_file = fopen(out_path, "wb");
    if (!out_file) {
        gzclose(in_file);
        printf("Failed to create output file\\n");
        return -1;
    }
    
    while ((num_read = gzread(in_file, buffer, CHUNK)) > 0) {
        fwrite(buffer, 1, num_read, out_file);
    }
    
    fclose(out_file);
    gzclose(in_file);
    
    return 0;
}

int main() {
    // Test cases
    printf("Running test cases...\\n");
    
    // Test case 1: Extract simple gzip file
    extract_gzip("test1.gz", "output1");
    
    // Test case 2: Extract large gzip file
    extract_gzip("test2.gz", "output2");
    
    // Test case 3: Extract empty gzip file
    extract_gzip("test3.gz", "output3");
    
    // Test case 4: Invalid input file
    extract_gzip("test4.gz", "output4");
    
    // Test case 5: Extract with long path
    extract_gzip("test5.gz", "output5/nested/directory/structure");
    
    return 0;
}
