#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // For mkdir on Linux/macOS
#include <unistd.h> // For access on Linux/macOS
#include <time.h> //for random number generation


// Function to sanitize the filename (replace invalid characters with underscores)
char* sanitize_filename(const char *filename) {
    char* sanitized = (char*)malloc(strlen(filename) + 1); // Allocate memory for sanitized filename
    if (sanitized == NULL) {
        perror("Memory allocation failed");
        return NULL; // Handle memory allocation error
    }
    strcpy(sanitized, filename);
    for (int i = 0; sanitized[i] != '\0'; i++) {
        if (!isalnum(sanitized[i]) && sanitized[i] != '.' && sanitized[i] != '_' && sanitized[i] != '-') {
            sanitized[i] = '_';
        }
    }
    return sanitized;
}



char* upload_file(const char *upload_directory, const char *file_data, size_t file_size, const char *file_name) {
    if (!upload_directory || !file_data || !file_name) {
        fprintf(stderr, "Invalid input parameters.\n");
        return NULL;
    }
    
    char* sanitized_file_name = sanitize_filename(file_name);
    if(sanitized_file_name == NULL){
        return NULL;
    }
    

    //Generate random number to prevent overwriting
    srand(time(NULL)); // Seed the random number generator
    int random_number = rand() % 100000; // Generate a random number between 0 and 999999
    
    // Allocate memory for the full file path
    char* file_path = malloc(strlen(upload_directory) + strlen(sanitized_file_name) + 12 +1 );  //+1 for null terminator, +12 for random numbers and underscore
    if (file_path == NULL) {
        perror("Memory allocation failed");
        free(sanitized_file_name); // Free allocated memory before returning
        return NULL;
    }

    // Create upload directory if it doesn't exist
    #ifdef _WIN32 // For Windows
    if (_mkdir(upload_directory) != 0 && errno != EEXIST) { 
        // Handle error if directory creation fails and it's not because it already exists
    #else // For Linux/macOS
        // Create all parent directories as well if they don't exist
    if (mkdir(upload_directory, 0777) != 0 && errno != EEXIST) { 
        // Handle error if directory creation fails and it's not because it already exists
    #endif
       perror("Error creating directory");
       free(sanitized_file_name);
       free(file_path);
       return NULL;
    }

    sprintf(file_path, "%s/%d_%s", upload_directory, random_number, sanitized_file_name);
    free(sanitized_file_name);
    FILE *file = fopen(file_path, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        free(file_path);
        return NULL;
    }

    size_t bytes_written = fwrite(file_data, 1, file_size, file);
    if (bytes_written != file_size) {
        perror("Error writing to file");
        fclose(file);
        free(file_path);
        return NULL;
    }

    fclose(file);

    return file_path;
}


int main() {
    const char *upload_dir = "uploads";
    const char *file_data1 = "Test file content 1";
    const char *file_data2 = "Test file content 2";
    const char *file_name1 = "test1.txt";
    const char *file_name2 = "test2.txt";
    const char *file_name3 = "../test3.txt";
    const char *file_name4 = "test4.txt";
    const char *file_name5 = "test5.txt";
    size_t file_size1 = strlen(file_data1);
    size_t file_size2 = strlen(file_data2);


    char *path1 = upload_file(upload_dir, file_data1, file_size1, file_name1);
    if(path1){
        printf("Uploaded file path: %s\n", path1);
        free(path1);
    }
    
    char *path2 = upload_file(upload_dir, file_data2, file_size2, file_name2);
    if(path2){
         printf("Uploaded file path: %s\n", path2);
         free(path2);
    }


    char *path3 = upload_file(upload_dir, file_data1, file_size1, file_name3);
    if(path3){
         printf("Uploaded file path: %s\n", path3);
         free(path3);
    }

    char *path4 = upload_file(upload_dir, file_data2, file_size2, file_name4);
    if(path4){
         printf("Uploaded file path: %s\n", path4);
         free(path4);
    }


    char *path5 = upload_file(upload_dir, file_data1, file_size1, file_name5);
    if(path5){
         printf("Uploaded file path: %s\n", path5);
         free(path5);
    }

    return 0;
}