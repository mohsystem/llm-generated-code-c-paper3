#include <stdio.h>
#include <zip.h>

void extractZip(const char* zipFileName) {
    zip* archive = zip_open(zipFileName, 0, NULL);
    if (!archive) {
        fprintf(stderr, "Failed to open the zip file.\n");
        return;
    }

    int numFiles = zip_get_num_files(archive, 0);
    for (int i = 0; i < numFiles; ++i) {
        struct zip_stat fileInfo;
        zip_stat_init(&fileInfo);
        if (zip_stat_index(archive, i, 0, &fileInfo) == 0) {
            // Ensure file path is safe to avoid path traversal
            char* safeFile = strdup(fileInfo.name);
            char* pos = strstr(safeFile, "../");
            while (pos != NULL) {
                memmove(pos, pos + 3, strlen(pos + 3) + 1);
                pos = strstr(safeFile, "../");
            }

            zip_file* file = zip_fopen_index(archive, i, 0);
            if (file) {
                char buffer[1024];
                FILE* outputFile = fopen(safeFile, "wb");
                if (outputFile) {
                    while (zip_fread(file, buffer, sizeof(buffer)) > 0) {
                        fwrite(buffer, sizeof(buffer), 1, outputFile);
                    }
                    fclose(outputFile);
                }
                zip_fclose(file);
            }
            free(safeFile);
        }
    }
    zip_close(archive);
}

int main() {
    // Test cases
    const char* zipFiles[] = {"test1.zip", "test2.zip"};
    for (const char* zipFile : zipFiles) {
        extractZip(zipFile);
    }
    return 0;
}