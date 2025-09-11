#include <stdio.h>
#include <sys/stat.h>

int main() {
    FILE *file = fopen("script.sh", "w");
    if (!file) {
        fprintf(stderr, "Error opening file for writing.\n");
        return 1;
    }

    fprintf(file, "#!/bin/bash\n");
    fprintf(file, "echo 'Hello World'\n");
    fclose(file);

    // Make the script executable
    if (chmod("script.sh", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) != 0) {
        fprintf(stderr, "Error setting permissions.\n");
        return 1;
    }

    return 0;
}