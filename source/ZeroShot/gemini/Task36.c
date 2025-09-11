#include <stdio.h>

void print_file_contents(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file) {
        char line[256]; // Adjust buffer size as needed
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        fprintf(stderr, "File not found: %s\n", file_path);
    }
}

int main() {
    print_file_contents("test1.txt");
    print_file_contents("test2.txt");
    print_file_contents("test3.txt");
    print_file_contents("test4.txt");
    print_file_contents("test5.txt");
    return 0;
}