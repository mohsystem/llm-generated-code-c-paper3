
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void createExecutableScript(const char* filename) {
    // Check if file exists
    struct stat buffer;
    if(stat(filename, &buffer) == 0) {
        fprintf(stderr, "Error: File already exists\\n");
        return;
    }

    // Create and write to file
    FILE* file = fopen(filename, "w");
    if(file == NULL) {
        fprintf(stderr, "Error creating file: %s\\n", strerror(errno));
        return;
    }

    fprintf(file, "#!/bin/bash\\n");
    fprintf(file, "echo \\"Hello World\\"\\n");
    fclose(file);

    // Set executable permissions
    if(chmod(filename, S_IRUSR | S_IWUSR | S_IXUSR) != 0) {
        fprintf(stderr, "Error setting permissions: %s\\n", strerror(errno));
        return;
    }
}

int main() {
    // Test cases
    createExecutableScript("script.sh");
    createExecutableScript("test1.sh");
    createExecutableScript("test2.sh");
    createExecutableScript("test3.sh");
    createExecutableScript("test4.sh");

    return 0;
}
