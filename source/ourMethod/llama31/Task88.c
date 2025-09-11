#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>

char* createTemporaryFile(const char* content) {
    uuid_t bin_uuid;
    uuid_generate_random(bin_uuid);
    char uuid[37];
    uuid_unparse(bin_uuid, uuid);

    char tempFileName[256];
    sprintf(tempFileName, "/tmp/temp_%s.tmp", uuid);

    FILE* tempFile = fopen(tempFileName, "wb+");
    if (!tempFile) {
        perror("Error creating temporary file");
        exit(1);
    }
    fwrite(content, 1, strlen(content), tempFile);
    fclose(tempFile);
    return strdup(tempFileName);
}

int main() {
    for (int i = 0; i < 5; i++) {
        uuid_t bin_uuid;
        uuid_generate_random(bin_uuid);
        char uuid[37];
        uuid_unparse(bin_uuid, uuid);
        char randomString[37];
        strcpy(randomString, uuid);
        char* tempFilePath = createTemporaryFile(randomString);
        printf("Temporary File Path: %s\n", tempFilePath);
        free(tempFilePath);
    }
    return 0;
}