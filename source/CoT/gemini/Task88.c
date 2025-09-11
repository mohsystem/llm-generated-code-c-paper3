#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// For tmpnam, mkstemp (POSIX)
#include <unistd.h>


char* create_temp_file_with_unicode_string() {
    char template_name[] = "/tmp/tempfileXXXXXX"; // Template for mkstemp
    int fd = mkstemp(template_name);

    if (fd == -1) {
        perror("mkstemp");
        return NULL;
    }

    FILE* temp_file = fdopen(fd, "w+");
    if (!temp_file) {
        perror("fdopen");
        close(fd);
        unlink(template_name); // Remove the file if opening failed
        return NULL;
    }

    // Generate random string (basic ASCII for simplicity in C)
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    char random_string[11]; // 10 chars + null terminator
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < 10; i++) {
        random_string[i] = characters[rand() % (sizeof(characters) - 1)];
    }
    random_string[10] = '\0';


    // Write to file (UTF-8 encoding needs explicit handling if non-ASCII chars are used)
    if (fputs(random_string, temp_file) == EOF) {
        perror("fputs");
        fclose(temp_file);
        unlink(template_name);
        return NULL;
    }

    fclose(temp_file); // Close the file (flushes and saves)

    char* file_path = strdup(template_name); // Duplicate the string so it persists
    if (!file_path) {
        perror("strdup");
        unlink(template_name);
        return NULL;
    }
    return file_path;
}


int main() {
    for (int i = 0; i < 5; i++) {
        char* file_path = create_temp_file_with_unicode_string();
        if (file_path) {
            printf("Temporary file path: %s\n", file_path);
            remove(file_path); // Clean up
            free(file_path);    // Free allocated memory

        }
    }
    return 0;
}