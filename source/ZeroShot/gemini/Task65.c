#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32 // For Windows
#include <io.h>
#define access _access
#else // For Linux/macOS
#include <unistd.h>
#endif


char* readFile(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
      char *error_message = malloc(100 * sizeof(char)); // Allocate memory
      if (error_message != NULL) {
        snprintf(error_message, 100, "Error: Could not open file or file not found: %s", filename); 
      }
        return error_message; // Return the allocated string
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, file);
    fclose(file);

    string[fsize] = 0;

    return string;
}

int main() {
    FILE *fp;
    fp = fopen("test1.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "test 1 content");
        fclose(fp);
    }


#ifdef _WIN32
    _mkdir("test");
#else
    mkdir("test", 0777); // Create the directory if it doesn't exist
#endif
    fp = fopen("test/test3.txt", "w");

    if (fp != NULL) {
        fprintf(fp, "test 3 content");
        fclose(fp);
    }


    char *result1 = readFile("test1.txt");
    printf("%s\n", result1);
    free(result1); // Free allocated memory

    char *result2 = readFile("test2.txt");
    printf("%s\n", result2);
    free(result2);

    char* result3 = readFile("invalid.txt");
    printf("%s\n", result3);
    free(result3);


    char *result4 = readFile("test/test3.txt");
    printf("%s\n", result4);
    free(result4);

    char *result5 = readFile("");
    printf("%s\n", result5);
    free(result5);



    return 0;
}