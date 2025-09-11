
#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>

bool createExecutableScript() {
    // Create file
    FILE *script = fopen("script.sh", "w");
    if (script == NULL) {
        return false;
    }
    
    fprintf(script, "#!/bin/bash\\necho \\"Hello from script\\"");
    fclose(script);
    
    // Make executable
    return chmod("script.sh", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) == 0;
}

int main() {
    // Test case 1: Create new script file
    printf("Test 1: %d\\n", createExecutableScript());
    
    // Test case 2: Create script file again (overwrite)
    printf("Test 2: %d\\n", createExecutableScript());
    
    // Test case 3: Verify file exists
    FILE *f = fopen("script.sh", "r");
    printf("Test 3: %d\\n", f != NULL);
    if (f) fclose(f);
    
    // Test case 4: Verify file is executable
    struct stat st;
    stat("script.sh", &st);
    printf("Test 4: %d\\n", (st.st_mode & S_IXUSR) != 0);
    
    // Test case 5: Create script with no permissions
    chmod("script.sh", 0);
    printf("Test 5: %d\\n", createExecutableScript());
    
    return 0;
}
