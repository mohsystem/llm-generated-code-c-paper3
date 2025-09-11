// Note: C does not have built-in support for Unicode. This code will write ASCII characters to the file.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* generate_random_string(int length) {
    const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    char* random_string = malloc(length + 1);
    srand(time(0));
    for (int i = 0; i < length; i++) {
        random_string[i] = chars[rand() % (sizeof(chars) - 1)];
    }
    random_string[length] = '\0';
    return random_string;
}

char* create_temp_file_with_ascii() {
    char* random_string = generate_random_string(10);

    FILE* fp = fopen("/tmp/temp.txt", "w");
    fprintf(fp, "%s", random_string);
    fclose(fp);

    free(random_string);

    return "/tmp/temp.txt";
}

int main() {
    printf("%s\n", create_temp_file_with_ascii());
    return 0;
}