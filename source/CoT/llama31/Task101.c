#include <stdio.h>
#include <stdlib.h>

int main() {
    try {
        // Create the script file
        FILE *file = fopen("script.sh", "w");
        if (file == NULL) {
            fprintf(stderr, "Unable to open file\n");
            return 1;
        }
        fprintf(file, "#!/bin/bash\n");
        fprintf(file, "echo 'Hello World'\n");
        fclose(file);

        // Make the script executable
        system("chmod +x script.sh");
    } catch (const exception& e) { // Note: C does not have try-catch, this is pseudo-code
        fprintf(stderr, "Error: %s\n", e.what());
    }

    return 0;
}