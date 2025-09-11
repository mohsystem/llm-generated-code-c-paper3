#include <stdio.h>
#include <stdlib.h>

void read_and_print_file_content(const char* file_path) {
    FILE* file_ptr = fopen(file_path, "r");
    if (file_ptr == NULL) {
        printf("An error occurred: File not found.\n");
        return;
    }
    char line[100];
    while (fgets(line, sizeof(line), file_ptr)) {
        printf("%s", line);
    }
    fclose(file_ptr);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please provide the file path as a command line argument.\n");
        return 1;
    }
    const char* file_path = argv[1];
    read_and_print_file_content(file_path);

    // Test cases
    const char* test_cases[] = {"test1.txt", "test2.txt", "test3.txt", "test4.txt", "test5.txt"};
    for (int i = 0; i < 5; ++i) {
        printf("Reading file: %s\n", test_cases[i]);
        read_and_print_file_content(test_cases[i]);
        printf("\n");
    }
    return 0;
}