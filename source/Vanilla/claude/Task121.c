
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int uploadFile(const char* sourcePath, const char* destinationPath) {
    FILE *source, *destination;
    char buffer[4096];
    size_t bytes;
    
    source = fopen(sourcePath, "rb");
    if (source == NULL) {
        return 0;
    }
    
    destination = fopen(destinationPath, "wb");
    if (destination == NULL) {
        fclose(source);
        return 0;
    }
    
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes, destination);
    }
    
    fclose(source);
    fclose(destination);
    return 1;
}

int main() {
    // Test cases
    printf("Test 1: %d\\n", uploadFile("test1.txt", "upload/test1.txt"));
    printf("Test 2: %d\\n", uploadFile("image.jpg", "upload/image.jpg"));
    printf("Test 3: %d\\n", uploadFile("doc.pdf", "upload/doc.pdf"));
    printf("Test 4: %d\\n", uploadFile("nonexistent.txt", "upload/test.txt"));
    printf("Test 5: %d\\n", uploadFile("data.csv", "upload/data.csv"));
    
    return 0;
}
