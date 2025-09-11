#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* create_temp_file() {
    char temp_file_path[] = "/tmp/temp_file.XXXXXX";
    int fd = mkstemp(temp_file_path);

    if (fd == -1) {
        perror("Error creating temp file");
        return NULL;
    }

    srand(time(0));
    char random_string[256];
    for (int i = 0; i < 256; i++) {
        random_string[i] = (char)(rand() % 256);
    }

    write(fd, random_string, 256);
    close(fd);

    return temp_file_path;
}

int main() {
    char* path = create_temp_file();
    if (path != NULL) {
        printf("%s\n", path);
    }
    return 0;
}