#include <stdio.h>
#include <sys/stat.h>

void create_executable_script(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fclose(file);
        chmod(filename, S_IRWXU);
    } else {
        perror("Unable to create file");
    }
}

int main() {
    create_executable_script("script.sh");
    create_executable_script("script1.sh");
    create_executable_script("script2.sh");
    create_executable_script("script3.sh");
    create_executable_script("script4.sh");
    return 0;
}