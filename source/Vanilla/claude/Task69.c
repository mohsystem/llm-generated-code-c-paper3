
#include <stdio.h>
#include <stdbool.h>

bool deleteFile(const char* filePath) {
    return remove(filePath) == 0;
}

int main() {
    // Test cases
    const char* testPaths[] = {
        "test1.txt",
        "folder/test2.txt",
        "nonexistent.txt",
        "test3.doc",
        "folder/subfolder/test4.pdf"
    };
    
    int numTests = 5;
    for(int i = 0; i < numTests; i++) {
        bool result = deleteFile(testPaths[i]);
        printf("Deleting %s: %s\\n", testPaths[i], result ? "Success" : "Failed");
    }
    
    return 0;
}
