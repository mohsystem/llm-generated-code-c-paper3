#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // For stat()


char* readFileData(const char* filename) {
    struct stat st;
    if (stat(filename, &st) != 0) {
        char *error_msg = malloc(100 * sizeof(char)); // Allocate memory for the error message
        snprintf(error_msg, 100, "Error: File does not exist or cannot be accessed.");
        return error_msg; // Return the dynamically allocated error message
    }
    if (!S_ISREG(st.st_mode)) {  // Check if it's a regular file
        char *error_msg = malloc(100 * sizeof(char)); // Allocate memory for the error message
        snprintf(error_msg, 100, "Error: Not a regular file.");
        return error_msg; // Return the dynamically allocated error message
    }
    if (!(st.st_mode & S_IRUSR)) { // Check read permissions for owner
        char *error_msg = malloc(100 * sizeof(char)); // Allocate memory for the error message
        snprintf(error_msg, 100, "Error: File cannot be read (permissions issue?).");
        return error_msg; // Return the dynamically allocated error message
    }


    FILE* file = fopen(filename, "r");
    if (file == NULL) {
         char *error_msg = malloc(100 * sizeof(char)); // Allocate memory for the error message
        snprintf(error_msg, 100, "Error: Unable to open file.");
        return error_msg; // Return the dynamically allocated error message
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* data = (char*)malloc(fsize + 1); // Allocate memory for the file content
    if(data == NULL){
        fclose(file);
        char *error_msg = malloc(100 * sizeof(char)); // Allocate memory for the error message
        snprintf(error_msg, 100, "Memory allocation failed.");
        return error_msg; // Return the dynamically allocated error message
    }


    fread(data, 1, fsize, file);
    data[fsize] = 0; // Null-terminate the string
    fclose(file);
    return data;


}

int main() {
    char* result;

    result = readFileData("test.txt");
    printf("%s\n", result);
    free(result); // Free allocated memory

    result = readFileData("nonexistent.txt");
    printf("%s\n", result);
    free(result);


    result = readFileData("./");
    printf("%s\n", result);
    free(result);


    result = readFileData("/etc/passwd");
    printf("%s\n", result);
    free(result);


    result = readFileData("test_long_filename_that_might_cause_issues.txt");
    printf("%s\n", result);
    free(result);

    return 0;
}