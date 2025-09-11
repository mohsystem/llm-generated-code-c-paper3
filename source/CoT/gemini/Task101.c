#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void create_and_make_executable(const char *filename) {
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0744); // Create with rwxr--r-- permissions
    if (fd == -1) {
        perror("Error creating file");
        return;
    }
    close(fd);
}

int main() {
    create_and_make_executable("script1.sh");
    create_and_make_executable("script2.sh");
    create_and_make_executable("script3.sh");
    create_and_make_executable("script4.sh");
    create_and_make_executable("script5.sh");
    return 0;
}