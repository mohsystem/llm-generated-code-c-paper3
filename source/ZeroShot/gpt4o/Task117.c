#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void extract_zip(const char *zip_file_path, const char *dest_dir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_zip(a);
    r = archive_read_open_filename(a, zip_file_path, 10240);
    if (r != ARCHIVE_OK) {
        fprintf(stderr, "Error opening archive: %s\n", archive_error_string(a));
        return;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *currentFile = archive_entry_pathname(entry);
        char fullOutputPath[1024];
        snprintf(fullOutputPath, sizeof(fullOutputPath), "%s/%s", dest_dir, currentFile);

        char *last_slash = strrchr(fullOutputPath, '/');
        if (last_slash) {
            *last_slash = '\0';
            mkdir(fullOutputPath, 0755);
            *last_slash = '/';
        }

        FILE *outFile = fopen(fullOutputPath, "wb");
        const void *buff;
        size_t size;
        la_int64_t offset;

        while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
            fwrite(buff, 1, size, outFile);
        }
        fclose(outFile);
        archive_entry_clear(entry);
    }
    archive_read_close(a);
    archive_read_free(a);
}

int main() {
    extract_zip("example.zip", "output_dir");
    return 0;
}