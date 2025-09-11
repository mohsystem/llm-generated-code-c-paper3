#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* generateRandomString(int length) {
    static const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    char* randomString = (char*)malloc((length + 1) * sizeof(char));
    srand(time(NULL));
    for (int i = 0; i < length; ++i) {
        randomString[i] = characters[rand() % strlen(characters)];
    }
    randomString[length] = '\0';
    return randomString;
}

char* createTempFile() {
    // Create a temporary file
    FILE* fp = tmpfile();
    if (fp == NULL) {
        fprintf(stderr, "Error creating temporary file\n");
        exit(1);
    }

    // Generate a random string
    char* randomString = generateRandomString(10);

    // Write the string to the file using UTF-8 encoding
    fputs(randomString, fp);
    rewind(fp);

    // Get the file path (Note: tmpfile does not provide a direct way to get the file path)
    // This example assumes the file is used immediately and then closed.
    // For getting the file path, consider using NamedTemporaryFile approaches available in other languages.

    // Close the file. The file will be deleted automatically.
    fclose(fp);

    // Since we cannot get the file path directly, we return an empty string.
    // In a real application, you would need to use a different method to get the file path.
    return "";
}

int main() {
    for (int i = 0; i < 5; ++i) {
        char* filePath = createTempFile();
        printf("Temporary File Path: %s\n", filePath);
    }
    return 0;
}