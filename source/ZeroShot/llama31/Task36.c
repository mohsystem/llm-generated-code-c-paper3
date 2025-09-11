#include <stdio.h>
#include <stdlib.h>

void read_and_print_file(const char* fname) {
    FILE* fptr = fopen(fname, "r");
    if (fptr == NULL) {
        printf("File %s does not exist or cannot be opened.\n", fname);
        return;
    }
    char str;
    while ((str = fgetc(fptr)) != EOF) {
        printf("%c", str);
    }
    fclose(fptr);
}

int main() {
    for (int i = 0; i < 5; i++) {
        char fname[20];
        printf("Input the filename to be opened: ");
        scanf("%19s", fname); // Ensure buffer safety
        read_and_print_file(fname);
    }
    return 0;
}