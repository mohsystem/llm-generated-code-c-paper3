#include <stdio.h>
#include <stdlib.h>

int main() {
    // Create the script file
    FILE *file = fopen("script.sh", "w");
    if (file != NULL) {
        fprintf(file, "#!/bin/bash\n");
        fprintf(file, "echo 'Hello World'\n");
        fclose(file);
    }

    // Make the script executable
    system("chmod +x script.sh");

    // Test cases
    for (int i = 0; i < 5; i++) {
        system("./script.sh");
    }

    return 0;
}