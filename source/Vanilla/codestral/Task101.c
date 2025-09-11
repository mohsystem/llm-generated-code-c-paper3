#include <stdio.h>
#include <sys/stat.h>

void createExecutableFile() {
    FILE *fp = fopen("script.sh", "w");
    if (fp != NULL) {
        printf("File is created!\n");
        fclose(fp);
        if (chmod("script.sh", S_IRWXU) == 0) {
            printf("File is now executable!\n");
        } else {
            printf("Unable to set file as executable!\n");
        }
    } else {
        printf("File already exists or an error occurred.\n");
    }
}

int main() {
    createExecutableFile();
    return 0;
}