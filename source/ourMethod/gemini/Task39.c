#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum filename length (adjust as needed)
#define MAX_FILENAME_LENGTH 256

char* displayFileContents(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        // Handle file opening error securely
        char* error_message = (char*)malloc(MAX_FILENAME_LENGTH + 50); // Allocate sufficient memory
        if (error_message != NULL) { // Check if allocation was successful to prevent dereferencing NULL pointer
            snprintf(error_message, MAX_FILENAME_LENGTH + 50, "Error: Could not open file %s", filename);
        }
        return error_message; // Return error message or NULL if allocation failed

    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);  //same as rewind(f);

    char* string = malloc(fsize + 1);
    if (string == NULL) {
        fclose(file); // Close the file before returning in case of error
        return NULL; // Return NULL to indicate memory allocation failure
    }

    fread(string, fsize, 1, file);
    fclose(file);

    string[fsize] = 0;

    return string;
}


int main() {

    char* filenames[] = {"test1.txt", "test2.txt", "nonexistent_file.txt", "test4.txt", "test5.txt"};
    int num_files = sizeof(filenames) / sizeof(filenames[0]);


    for (int i = 0; i < num_files; i++) {
        char* result = displayFileContents(filenames[i]);
        if (result != NULL) {
             if(strncmp(result, "Error:", 6) == 0){ // Check if result is an error message before printing.
                fprintf(stderr, "%s\n", result); // Print error messages to stderr.
             } else {
                printf("%s", result);
             }

            free(result);
        } else {
            fprintf(stderr, "Memory allocation failed.\n"); // Print error messages to stderr
        }
    }
    return 0;
}