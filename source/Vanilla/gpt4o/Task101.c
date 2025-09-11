#include <stdio.h>
#include <sys/stat.h>

void create_and_make_executable(const char* file_name) {
    FILE* file = fopen(file_name, "w");
    if (file) {
        fclose(file);
        chmod(file_name, 0755);
    }
}

int main() {
    create_and_make_executable("script.sh");
    printf("File script.sh created and made executable.\n");
    return 0;
}