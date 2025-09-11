#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

int extract_zip_file(const char* zip_file_path, const char* dest_directory) {
    struct archive* a = archive_read_new();
    struct archive* ext = archive_write_disk_new();
    struct archive_entry* entry;
    int r;

    archive_read_support_format_zip(a);
    archive_read_open_filename(a, zip_file_path, 10240);

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char* path = archive_entry_pathname(entry);
        char* full_path = malloc(strlen(dest_directory) + strlen(path) + 2);
        sprintf(full_path, "%s/%s", dest_directory, path);
        archive_entry_set_pathname(entry, full_path);
        free(full_path);

        r = archive_write_header(ext, entry);
        if (r < ARCHIVE_OK) {
            fprintf(stderr, "%s\n", archive_error_string(ext));
            return 1;
        } else {
            const void* buff;
            size_t size;
            int64_t offset;

            while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
                r = archive_write_data(ext, buff, size);
                if (r < ARCHIVE_OK) {
                    fprintf(stderr, "%s\n", archive_error_string(ext));
                    return 1;
                }
            }
        }
        r = archive_write_finish_entry(ext);
        if (r < ARCHIVE_OK) {
            fprintf(stderr, "%s\n", archive_error_string(ext));
            return 1;
        }
    }
    r = archive_read_close(a);
    if (r < ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        return 1;
    }
    r = archive_read_free(a);
    if (r < ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(a));
        return 1;
    }
    archive_write_close(ext);
    archive_write_free(ext);
    return 0;
}

int main() {
    return extract_zip_file("path_to_zip_file.zip", "destination_directory");
}