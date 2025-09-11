#include <stdio.h>
#include <stdlib.h>

int main() {
    // Create the script file
    FILE *file = fopen("script.sh", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(file, "#!/bin/bash\n");
    fprintf(file, "echo \"Hello World\"\n");
    fclose(file);

    // Make the script executable using a shell command
    system("chmod +x script.sh");

    return 0;
}