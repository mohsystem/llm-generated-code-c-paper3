#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to generate a random string
void generateRandomString(char* str, int length) {
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    srand(time(NULL));
    for (int i = 0; i < length; ++i) {
        str[i] = characters[rand() % (sizeof(characters) - 1)];
    }
    str[length] = '\0';
}

// Function to create a temporary file with a Unicode string
char* createTempFileWithUnicodeString() {
    // Generate a random string
    char randomString[21];
    generateRandomString(randomString, 20);

    // Create a temporary file name
    char tempFileName[100];
    sprintf(tempFileName, "/tmp/temp_%d.txt", rand());

    // Write the string to the file
    FILE* file = fopen(tempFileName, "w");
    if (file != NULL) {
        fprintf(file, "%s", randomString);
        fclose(file);
    }

    return strdup(tempFileName);
}

int main() {
    for (int i = 0; i < 5; ++i) {
        char* filePath = createTempFileWithUnicodeString();
        printf("Temporary File Path: %s\n", filePath);
        free(filePath);
    }
    return 0;
}