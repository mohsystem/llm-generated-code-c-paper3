#include <stdio.h>
#include <stdlib.h>

void uploadFile(const char* source, const char* destination) {
    FILE* in = fopen(source, "rb");
    FILE* out = fopen(destination, "wb");

    if (!in || !out) {
        fprintf(stderr, "Error opening files.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, 1024, in)) > 0) {
        fwrite(buffer, 1, bytesRead, out);
    }

    fclose(in);
    fclose(out);

    printf("File uploaded from %s to %s\n", source, destination);
}

int main() {
    // Test cases
    const char* sourceFiles[] = {"test1.txt", "test2.txt", "test3.txt"};
    const char* destinationFiles[] = {"uploaded_test1.txt", "uploaded_test2.txt", "uploaded_test3.txt"};

    for (int i = 0; i < 3; i++) {
        uploadFile(sourceFiles[i], destinationFiles[i]);
    }

    return 0;
}