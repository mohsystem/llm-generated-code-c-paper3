#include <stdio.h>
#include <stdbool.h>
#include <string.h> // For strlen and strcpy
#include <stdlib.h> // For remove

bool deleteFile(const char* filePath) {
   if (remove(filePath) == 0) {
      return true;
   } else {
      return false;
   }
}

int main(int argc, char *argv[]) {
   if (argc > 1) {
      for (int i = 1; i < argc; i++) {
         if (deleteFile(argv[i])) {
            printf("File deleted successfully: %s\n", argv[i]);
         } else {
            printf("Failed to delete file: %s\n", argv[i]);
         }
      }
   } else {
      printf("No file path provided.\n");

      // Test Cases (when no command line arguments):
      FILE *fp;

      // Create test1.txt and then delete
      fp = fopen("test1.txt", "w");
      if (fp != NULL) {
         fclose(fp);
      }
      printf("%s\n", deleteFile("test1.txt") ? "true" : "false"); // Should print true


      printf("%s\n", deleteFile("non_existent_file.txt") ? "true" : "false"); // Should print false


      // Creating and deleting a file inside a directory is OS-specific and complex in pure C.
      // The below demonstrates basic directory creation, which can be extended based on your target OS. 
      #ifdef _WIN32 // Windows-specific
         system("mkdir test_directory"); // Might need error checking
         fp = fopen("test_directory\\test2.txt", "w");
         if(fp != NULL) {
             fclose(fp);
         }
         printf("%s\n", deleteFile("test_directory\\test2.txt") ? "true" : "false");
         printf("%s\n", deleteFile("test_directory") ? "true" : "false"); // Try deleting the directory

      #else // For other OS (e.g., Linux/macOS -  using mkdir and rmdir)
          // Handle mkdir and file creation similar to Windows, but adapt path separators if needed
          // ...
      #endif
   }
   return 0;
}