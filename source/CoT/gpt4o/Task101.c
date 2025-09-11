#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void createAndMakeExecutable(const char* fileName) {
    FILE* file = fopen(fileName, "w");
    if (file) {
        fclose(file);
        if (chmod(fileName, S_IRWXU | S_IRGRP | S_IROTH) == 0) {
            printf("%s is created and made executable.\n", fileName);
        } else {
            printf("Failed to make %s executable.\n", fileName);
        }
    } else {
        printf("Failed to create %s.\n", fileName);
    }
}

int main() {
    // Test cases
    createAndMakeExecutable("script.sh");
    createAndMakeExecutable("example.sh");
    createAndMakeExecutable("testScript.sh");
    createAndMakeExecutable("myScript.sh");
    createAndMakeExecutable("demo.sh");

    return 0;
}