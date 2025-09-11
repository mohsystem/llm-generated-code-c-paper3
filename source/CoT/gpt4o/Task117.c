#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

void extractArchive(const char *archivePath, const char *destDirectory) {
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    int flags = ARCHIVE_EXTRACT_TIME;
    int r;

    a = archive_read_new();
    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, flags);
    archive_read_support_format_zip(a);
    archive_read_support_format_tar(a);
    if ((r = archive_read_open_filename(a, archivePath, 10240))) {
        fprintf(stderr, "Failed to open archive\n");
        return;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *currentFile = archive_entry_pathname(entry);
        char fullOutputPath[1024];
        snprintf(fullOutputPath, sizeof(fullOutputPath), "%s/%s", destDirectory, currentFile);
        archive_entry_set_pathname(entry, fullOutputPath);
        archive_write_header(ext, entry);
        const void *buff;
        size_t size;
        la_int64_t offset;
        while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
            archive_write_data_block(ext, buff, size, offset);
        }
        archive_write_finish_entry(ext);
    }

    archive_read_close(a);
    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);
}

int main() {
    extractArchive("example.zip", "outputDir");
    extractArchive("example.tar", "outputDir");
    return 0;
}