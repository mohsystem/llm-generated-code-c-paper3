#include <stdio.h>
#include <archive.h>
#include <archive_entry.h>

void extractZipFile(const char* filePath) {
    struct archive* a = archive_read_new();
    archive_read_support_format_zip(a);
    archive_read_open_filename(a, filePath, 10240);

    struct archive_entry* entry;
    int r;
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char* path = archive_entry_pathname(entry);
        size_t size;
        archive_entry_size(entry);

        void* buff = malloc(size);
        archive_read_data(a, buff, size);

        FILE* f = fopen(path, "w");
        fwrite(buff, 1, size, f);
        fclose(f);

        free(buff);
    }

    archive_read_close(a);
    archive_read_free(a);
}

int main() {
    extractZipFile("test.zip");
    return 0;
}