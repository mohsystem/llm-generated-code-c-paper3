#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h> // For *nix systems
#include <fcntl.h>  // For open flags
#endif


char* createTempFileWithUnicodeString() {
    char tempTemplate[] = "unicode_XXXXXX.txt";
    int fd;

#ifdef _WIN32
    char tempPath[MAX_PATH];
    if (GetTempPathA(MAX_PATH, tempPath) == 0) {
        fprintf(stderr, "Error getting temporary directory path.\n");
        return NULL;
    }

     strcat(tempPath, tempTemplate);
     fd = mkstemp(tempPath);
#else
     fd = mkstemp(tempTemplate);
#endif

    if (fd == -1) {
        perror("Error creating temporary file");
        return NULL;
    }


    // Generate random string (UTF-8 encoding)
    int stringLength = 10;
    char randomString[stringLength * 4 + 1]; // Max 4 bytes per UTF-8 char + null terminator

    srand(time(NULL));
    for (int i = 0; i < stringLength; i++) {
        // Generate random Unicode code point (up to 0x10FFFF)
        int codePoint = rand() % 0x10FFFF + 1;
        
        // Encode in UTF-8 
        int bytesWritten = 0;
        if (codePoint <= 0x7F) {
            randomString[i * 4 + bytesWritten++] = (char)codePoint;
        } else if (codePoint <= 0x7FF) {
            randomString[i * 4 + bytesWritten++] = (char)(0xC0 | (codePoint >> 6));
            randomString[i * 4 + bytesWritten++] = (char)(0x80 | (codePoint & 0x3F));
        } else if (codePoint <= 0xFFFF) {
            randomString[i * 4 + bytesWritten++] = (char)(0xE0 | (codePoint >> 12));
            randomString[i * 4 + bytesWritten++] = (char)(0x80 | ((codePoint >> 6) & 0x3F));
            randomString[i * 4 + bytesWritten++] = (char)(0x80 | (codePoint & 0x3F));
        } else {  // codePoint <= 0x10FFFF
            randomString[i * 4 + bytesWritten++] = (char)(0xF0 | (codePoint >> 18));
            randomString[i * 4 + bytesWritten++] = (char)(0x80 | ((codePoint >> 12) & 0x3F));
            randomString[i * 4 + bytesWritten++] = (char)(0x80 | ((codePoint >> 6) & 0x3F));
            randomString[i * 4 + bytesWritten++] = (char)(0x80 | (codePoint & 0x3F));
        }

    }
    randomString[stringLength * 4] = '\0'; // Null terminate the string



    // Write to file
    if (write(fd, randomString, strlen(randomString)) == -1) {
        perror("Error writing to temporary file");
        close(fd);
#ifdef _WIN32
         _unlink(tempPath);
#else
        unlink(tempTemplate);
#endif
        return NULL;
    }


    close(fd); 

#ifdef _WIN32
    char* result = _strdup(tempPath); // Allocate and copy the path string
#else
    char *result = strdup(tempTemplate);
#endif
    return result;
}




int main() {
    for (int i = 0; i < 5; i++) {
        char* filePath = createTempFileWithUnicodeString();
        if (filePath != NULL) {
            printf("Test case %d: %s\n", i + 1, filePath);
            remove(filePath); // Delete temporary file
            free(filePath); // Free allocated memory
        }
    }
    return 0;
}