// C does not have built-in support for ZIP files. You would need to use a library like libzip or zlib.
// Here's a simplified example using libzip.
#include <zip.h>
#include <stdio.h>
#include <string.h>

int extractZipFile(const char *zipFilePath, const char *destDir) {
    int err = 0;
    zip *z = zip_open(zipFilePath, 0, &err);

    if (z == NULL) {
        printf("Failed to open zip file: %s\n", zip_strerror(z));
        return -1;
    }

    for (int i = 0; i < zip_get_num_entries(z, 0); i++) {
        zip_entry *e = zip_get_entry(z, i);
        const char *name = zip_entry_name(e);
        char filePath[1024];
        snprintf(filePath, sizeof(filePath), "%s/%s", destDir, name);

        if (zip_entry_open(z, e) != 0) {
            printf("Failed to open entry: %s\n", zip_strerror(z));
            zip_close(z);
            return -1;
        }

        FILE *f = fopen(filePath, "wb");
        if (f == NULL) {
            printf("Failed to open file for writing: %s\n", strerror(errno));
            zip_entry_close(e);
            zip_close(z);
            return -1;
        }

        char buf[1024];
        int len;
        while ((len = zip_entry_read(e, buf, sizeof(buf))) > 0) {
            fwrite(buf, 1, len, f);
        }

        fclose(f);
        zip_entry_close(e);
    }

    zip_close(z);
    return 0;
}

int main() {
    return extractZipFile("path_to_your_file.zip", "destination_directory");
}