#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // For mkdir

#ifdef _WIN32 // Windows specific includes
#include <direct.h> // For mkdir on Windows
#else
#include <unistd.h> // For access and mkdir on POSIX systems
#endif


void copy_file(const char *source_path, const char *dest_path) {
    FILE *source_file, *dest_file;
    char buffer[BUFSIZ]; // Use a buffer for efficient copying
    size_t bytes_read;

    if ((source_file = fopen(source_path, "rb")) == NULL) {
        perror("Error opening source file");
        return; 
    }

    // Create destination directory if it doesn't exist
    char dest_dir[256]; // Adjust size as needed
    strncpy(dest_dir, dest_path, sizeof(dest_dir));
    char* last_slash = strrchr(dest_dir, '/'); 
    if (last_slash != NULL) {
        *last_slash = '\0'; // Terminate the string at the last slash to get the directory path


        #ifdef _WIN32 //check for windows
            if (_mkdir(dest_dir) != 0 && errno != EEXIST) {
                perror("Error creating destination directory");
                fclose(source_file);
                return;
            }

        #else //linux or posix
            if (mkdir(dest_dir, 0777) != 0 && errno != EEXIST) {
                perror("Error creating destination directory");
                fclose(source_file);
                return;
            }
        #endif



    }




    if ((dest_file = fopen(dest_path, "wb")) == NULL) {
        perror("Error opening destination file");
        fclose(source_file);
        return;
    }


    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source_file)) > 0) {
        if (fwrite(buffer, 1, bytes_read, dest_file) != bytes_read) {
            perror("Error writing to destination file");
            fclose(source_file);
            fclose(dest_file);
            return;
        }
    }

    printf("File copied successfully: %s\n", source_path);


    fclose(source_file);
    fclose(dest_file);
}

int main() {
    copy_file("test1.c", "temp/test1_copy.c");
    copy_file("test2.c", "temp/test2_copy.c"); // test2.c might not exist
    copy_file("test3.c", "temp/test3_copy.c");
    copy_file("test4.c", "temp/test4_copy.c");
    copy_file("test5.c", "temp/test5_copy.c");

    return 0;
}