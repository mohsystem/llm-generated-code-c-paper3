
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int deleteFile(const char* filePath) {
    if (filePath == NULL || strlen(filePath) == 0) {
        return 0;
    }
    
    // Check if file exists and can be accessed
    if (access(filePath, F_OK | W_OK) == -1) {
        return 0;
    }
    
    // Try to remove the file
    if (remove(filePath) == 0) {
        return 1;
    }
    
    return 0;
}

int main() {
    // Test cases
    const char* testPaths[] = {
        "test1.txt",
        "folder/test2.txt",
        "", // empty path
        NULL, // null path
        "nonexistent.txt"
    };
    
    for (int i = 0; i < 5; i++) {
        int result = deleteFile(testPaths[i]);
        printf("Deleting file: %s - Result: %d\\n", 
               testPaths[i] ? testPaths[i] : "NULL", 
               result);
    }
    
    return 0;
}
