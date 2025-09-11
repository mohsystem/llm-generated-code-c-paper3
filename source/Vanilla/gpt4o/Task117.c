#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

void extractZip(const char* zipFilePath, const char* destDir) {
    struct archive* a;
    struct archive* ext;
    struct archive_entry* entry;
    int flags = ARCHIVE_EXTRACT_TIME;

    a = archive_read_new();
    archive_read_support_format_zip(a);
    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, flags);
    archive_write_disk_set_standard_lookup(ext);
    if (archive_read_open_filename(a, zipFilePath, 10240)) {
        fprintf(stderr, "Could not open archive: %s\n", zipFilePath);
        return;
    }
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char* currentFile = archive_entry_pathname(entry);
        char fullPath[1024];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", destDir, currentFile);
        archive_entry_set_pathname(entry, fullPath);
        archive_write_header(ext, entry);
        archive_copy_data(a, ext);
        archive_write_finish_entry(ext);
    }
    archive_read_close(a);
    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);
}

int main() {
    // Test cases
    extractZip("test1.zip", "output1");
    extractZip("test2.zip", "output2");
    extractZip("test3.zip", "output3");
    extractZip("test4.zip", "output4");
    extractZip("test5.zip", "output5");

    return 0;
}