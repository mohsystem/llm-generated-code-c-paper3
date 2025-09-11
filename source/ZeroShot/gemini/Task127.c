#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void copy_file_to_temp(const char *source_file_path) {
    FILE *source_file, *temp_file;
    char temp_file_name[L_tmpnam]; // Sufficiently large buffer for temp file name
    char ch;


    source_file = fopen(source_file_path, "r");
    if (source_file == NULL) {
        fprintf(stderr, "Error: Source file not found: %s\n", source_file_path);
        return;
    }

    tmpnam(temp_file_name);  // Generates a unique temporary file name


    temp_file = fopen(temp_file_name, "w");
    if (temp_file == NULL) {
        fclose(source_file); // Close source file if temp file creation fails
        fprintf(stderr, "Error creating temporary file.\n");
        return;
    }

    while ((ch = fgetc(source_file)) != EOF) {
        fputc(ch, temp_file);
    }

    printf("File copied successfully to: %s\n", temp_file_name);

    fclose(source_file);
    fclose(temp_file);


}

int main() {
    // Create dummy files for testing
    fclose(fopen("test1.txt", "w"));
    fclose(fopen("test2.txt", "w"));
    fclose(fopen("test3.txt", "w"));

    copy_file_to_temp("test1.txt");
    copy_file_to_temp("nonexistent_file.txt");
    copy_file_to_temp("test2.txt");
    copy_file_to_temp(""); // Test with empty string
    copy_file_to_temp("test3.txt");


    return 0;
}