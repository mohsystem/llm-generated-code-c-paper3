#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void createExecutableScript(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "%s", content);
        fclose(file);
        chmod(filename, S_IRWXU | S_IROG | S_IROTH); 
    } else {
        perror("Unable to create file");
    }
}

int main() {
    createExecutableScript("script.sh", "#/bin/bash\necho \"Hello, World\"\n");
    createExecutableScript("script1.sh", "#/bin/bash\necho \"Test 1\"\n");
    createExecutableScript("script2.sh", "#/bin/bash\necho \"Test 2\"\n");
    createExecutableScript("script3.sh", "#/bin/bash\necho \"Test 3\"\n");
    createExecutableScript("script4.sh", "#/bin/bash\necho \"Test 4\"\n");
    return 0;
}