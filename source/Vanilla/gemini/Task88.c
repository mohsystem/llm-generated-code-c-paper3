#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // For mkstemp

char* create_temp_file_with_unicode(int string_length) {
    char temp_file_path[] = "/tmp/unicode_XXXXXX.txt";
    int fd = mkstemp(temp_file_path);

    if (fd == -1) {
        perror("Failed to create temporary file");
        return NULL;
    }

    FILE* temp_file = fdopen(fd, "w");
    if (temp_file == NULL) {
        perror("Failed to open temporary file");
        close(fd);
        unlink(temp_file_path); // Remove the file if opening fails
        return NULL;
    }


    // Ensure enough space for UTF-8 characters (max 4 bytes per char) and null terminator
    char* random_string = (char*)malloc(string_length * 4 + 1); 

    if (random_string == NULL) {
        fclose(temp_file);
        unlink(temp_file_path);
        return NULL;
    }

    srand(time(NULL)); // Seed random number generator

    for (int i = 0; i < string_length; i++) {
        // Generate code points within the valid Unicode range (0 to 0x10FFFF)
        int code_point = rand() % 0x110000; 
        // You'll need a proper UTF-8 encoding function here if you want to support 
        // characters beyond the basic multilingual plane.  This example simply casts 
        // the code point to a character, which is incorrect for many characters.
        random_string[i] = (char)code_point;
    }
    random_string[string_length] = '\0';  // Null-terminate the string

    if (fputs(random_string, temp_file) == EOF) {
        perror("Failed to write to temporary file");
        fclose(temp_file);
        unlink(temp_file_path); // Clean up
        free(random_string);
        return NULL;
    }
    

    fclose(temp_file);
    free(random_string);
    
    char *return_path = strdup(temp_file_path); // Duplicate the path to return
    if (return_path == NULL) {
        unlink(temp_file_path);
        return NULL;
    }

    return return_path;
}

int main() {
    char* path1 = create_temp_file_with_unicode(10);
    if (path1) { printf("%s\n", path1); free(path1); }
    char* path2 = create_temp_file_with_unicode(20);
    if (path2) { printf("%s\n", path2); free(path2); }
    char* path3 = create_temp_file_with_unicode(30);
    if (path3) { printf("%s\n", path3); free(path3); }
    char* path4 = create_temp_file_with_unicode(15);
    if (path4) { printf("%s\n", path4); free(path4); }
    char* path5 = create_temp_file_with_unicode(25);
    if (path5) { printf("%s\n", path5); free(path5); }


    return 0;
}