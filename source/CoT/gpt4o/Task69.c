#include <stdio.h>

int deleteFile(const char* filePath) {
    if (remove(filePath) == 0) {
        return 1;
    }
    return 0;
}

int main() {
    printf("%d\n", deleteFile("test1.txt"));  // Replace with valid file paths for testing
    printf("%d\n", deleteFile("test2.txt"));
    printf("%d\n", deleteFile("test3.txt"));
    printf("%d\n", deleteFile("test4.txt"));
    printf("%d\n", deleteFile("test5.txt"));
    return 0;
}