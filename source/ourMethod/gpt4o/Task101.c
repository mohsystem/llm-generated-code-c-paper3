#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int create_and_make_executable(const char *file_name) {
    int fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (fd != -1) {
        close(fd);
        return chmod(file_name, S_IRWXU | S_IRGRP | S_IROTH) == 0;
    }
    return 0;
}

int main() {
    printf("%d\n", create_and_make_executable("script.sh"));
    printf("%d\n", create_and_make_executable("script2.sh"));
    printf("%d\n", create_and_make_executable("script3.sh"));
    printf("%d\n", create_and_make_executable("script4.sh"));
    printf("%d\n", create_and_make_executable("script5.sh"));
    return 0;
}