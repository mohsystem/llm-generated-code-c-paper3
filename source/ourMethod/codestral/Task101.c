#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int createAndMakeExecutable(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file != NULL) {
        fclose(file);
        printf("File already exists.\n");
        return 0;
    }

    file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error creating file.\n");
        return 1;
    }
    fclose(file);
    printf("File created: %s\n", fileName);

    if (chmod(fileName, S_IRWXU | S_IRGRP | S_IXGRP) == 0) {
        printf("File made executable: %s\n", fileName);
        return 0;
    } else {
        printf("Error making file executable.\n");
        return 1;
    }
}

int main() {
    return createAndMakeExecutable("script.sh");
}