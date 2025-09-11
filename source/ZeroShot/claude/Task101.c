
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void createExecutableScript(const char* content) {
    FILE* file = fopen("script.sh", "w");
    if (file == NULL) {
        fprintf(stderr, "Error creating file: %s\\n", strerror(errno));
        return;
    }

    // Write content
    if (fputs(content, file) == EOF) {
        fprintf(stderr, "Error writing to file: %s\\n", strerror(errno));
        fclose(file);
        return;
    }

    fclose(file);

    // Make executable
    if (chmod("script.sh", S_IRWXU) != 0) {
        fprintf(stderr, "Error making file executable: %s\\n", strerror(errno));
        return;
    }

    printf("Script file created and made executable successfully\\n");
}

int main() {
    // Test cases
    createExecutableScript("#!/bin/bash\\necho 'Hello World'");
    createExecutableScript("#!/bin/bash\\nls -la");
    createExecutableScript("#!/bin/bash\\ndate");
    createExecutableScript("#!/bin/bash\\npwd");
    createExecutableScript("#!/bin/bash\\nwhoami");

    return 0;
}
