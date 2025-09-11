
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int create_executable_script(const char* content) {
    FILE* file;
    
    // Create and write to file
    file = fopen("script.sh", "w");
    if (file == NULL) {
        printf("Unable to create file\\n");
        return 0;
    }
    
    fprintf(file, "%s", content);
    fclose(file);
    
    // Make executable
    if (chmod("script.sh", S_IRWXU) != 0) {
        printf("Unable to make file executable\\n");
        return 0;
    }
    
    return 1;
}

int main() {
    // Test cases
    const char* test_contents[] = {
        "#!/bin/bash\\necho 'Hello World'",
        "#!/bin/bash\\nls -la",
        "#!/bin/bash\\ndate",
        "#!/bin/bash\\npwd",
        "#!/bin/bash\\nwhoami"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Test case %d:\\n", i + 1);
        int result = create_executable_script(test_contents[i]);
        printf("Result: %s\\n\\n", result ? "true" : "false");
    }
    
    return 0;
}
