#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void create_and_make_executable(const char *file_name) {
    FILE *file = fopen(file_name, "w");
    if (file) {
        fclose(file);
        if (chmod(file_name, S_IRWXU | S_IRGRP | S_IROTH) == 0) {
            printf("%s is created and made executable.\n", file_name);
        } else {
            perror("Failed to make the file executable");
        }
    } else {
        perror("Failed to create the file");
    }
}

int main() {
    create_and_make_executable("script1.sh");
    create_and_make_executable("script2.sh");
    create_and_make_executable("script3.sh");
    create_and_make_executable("script4.sh");
    create_and_make_executable("script5.sh");
    return 0;
}