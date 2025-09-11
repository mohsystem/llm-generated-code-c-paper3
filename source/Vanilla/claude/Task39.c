
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char* display_file_contents(const char* filename) {
    static char result[BUFFER_SIZE];
    char command[BUFFER_SIZE];
    FILE* pipe;
    
    #ifdef _WIN32
        sprintf(command, "type %s", filename);
    #else
        sprintf(command, "cat %s", filename);
    #endif
    
    pipe = popen(command, "r");
    if (!pipe) {
        return "Error executing command";
    }
    
    result[0] = '\\0';
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        strcat(result, buffer);
    }
    
    pclose(pipe);
    return result;
}

int main() {
    // Test cases
    const char* test_files[] = {
        "test1.txt",
        "sample.txt",
        "nonexistent.txt",
        "data.txt",
        "empty.txt"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Reading file: %s\\n", test_files[i]);
        printf("%s\\n", display_file_contents(test_files[i]));
        printf("------------------------\\n");
    }
    
    return 0;
}
