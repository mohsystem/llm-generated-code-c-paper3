#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void create_and_make_executable(const char *filename) {
    int fd = creat(filename, 0744); // Creates file with desired permissions
    if (fd == -1) {
        perror("creat");
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
    printf("Files created and made executable.\n");
    return 0;
}