#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void createExecutableFile() {
    const char* file_name = "script.sh";
    FILE *file = fopen(file_name, "w");
    if (file != NULL) {
        fclose(file);
        if (chmod(file_name, S_IRWXU) == 0) {
            printf("File script.sh created and made executable.\n");
        } else {
            printf("Failed to make the file executable.\n");
        }
    } else {
        printf("Failed to create the file.\n");
    }
}

int main() {
    createExecutableFile();
    return 0;
}