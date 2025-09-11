#include <stdio.h>
#include <stdlib.h>
#include <archive.h>
#include <archive_entry.h>

void extractArchive(const char *archivePath, const char *destDir) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_tar(a);
    archive_read_support_format_zip(a);

    if ((r = archive_read_open_filename(a, archivePath, 10240))) {
        fprintf(stderr, "Failed to open archive\n");
        return;
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *currentFile = archive_entry_pathname(entry);
        char fullOutputPath[1024];
        snprintf(fullOutputPath, sizeof(fullOutputPath), "%s/%s", destDir, currentFile);
        archive_entry_set_pathname(entry, fullOutputPath);

        const void *buff;
        size_t size;
        la_int64_t offset;
        FILE *outFile = fopen(fullOutputPath, "wb");
        while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
            fwrite(buff, 1, size, outFile);
        }
        fclose(outFile);
    }

    archive_read_close(a);
    archive_read_free(a);
}

int main() {
    // Test cases
    extractArchive("test1.zip", "output1");
    extractArchive("test2.zip", "output2");
    extractArchive("test3.tar", "output3");
    extractArchive("test4.tar", "output4");
    extractArchive("test5.zip", "output5");

    return 0;
}