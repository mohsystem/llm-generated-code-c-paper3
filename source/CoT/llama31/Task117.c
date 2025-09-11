#include <stdio.h>
#include <libzip.h>
#include <libtar.h>

void extractZip(const char* zipFile, const char* outputFolder) {
    int error = 0;
    zip* zipArchive = zip_open(zipFile, ZIP_RDONLY, &error);
    if (zipArchive == NULL) {
        fprintf(stderr, "Failed to open ZIP file.\n");
        return;
    }

    for (int i = 0; i < zip_get_num_entries(zipArchive, 0); ++i) {
        const char* name = zip_get_name(zipArchive, i, 0);
        zip_stat_t stat;
        zip_stat(zipArchive, name, 0, &stat);
        if (stat.size > 0) {
            zip_file* file = zip_fopen(zipArchive, name, 0);
            if (file == NULL) {
                fprintf(stderr, "Failed to open file in ZIP archive.\n");
                continue;
            }

            char outputPath[1024];
            sprintf(outputPath, "%s/%s", outputFolder, name);
            FILE* outputFile = fopen(outputPath, "wb");
            if (outputFile == NULL) {
                fprintf(stderr, "Failed to open output file.\n");
                zip_fclose(file);
                continue;
            }

            char buffer[1024];
            zip_int64_t len;
            while ((len = zip_fread(file, buffer, 1024)) > 0) {
                fwrite(buffer, 1, len, outputFile);
            }
            fclose(outputFile);
            zip_fclose(file);
        }
    }
    zip_close(zipArchive);
}

void extractTar(const char* tarFile, const char* outputFolder) {
    Tar* tarArchive = tar_open(tarFile, "r");
    if (tarArchive == NULL) {
        fprintf(stderr, "Failed to open TAR file.\n");
        return;
    }

    char buffer[1024];
    while (true) {
        TarHeader* header = tar_thead(tarArchive);
        if (header == NULL) break;

        char outputPath[1024];
        sprintf(outputPath, "%s/%s", outputFolder, header->name);
        FILE* outputFile = fopen(outputPath, "wb");
        if (outputFile == NULL) {
            fprintf(stderr, "Failed to open output file.\n");
            continue;
        }

        while (true) {
            int bytesRead = tar_block_read(tarArchive, buffer, 1024);
            if (bytesRead <= 0) break;
            fwrite(buffer, 1, bytesRead, outputFile);
        }
        fclose(outputFile);
    }
    tar_close(tarArchive);
}

int main() {
    // Test cases
    extractZip("path/to/your/zipfile.zip", "path/to/output/folder");
    extractTar("path/to/your/tarfile.tar", "path/to/output/folder");
    return 0;
}