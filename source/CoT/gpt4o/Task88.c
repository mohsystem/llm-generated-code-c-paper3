#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generate_random_string(char *str, size_t length) {
    char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (size_t i = 0; i < length; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        str[i] = charset[key];
    }
    str[length] = '\0';
}

char* convert_to_unicode(const char *input) {
    size_t len = strlen(input);
    char *unicode_str = (char*)malloc(6 * len + 1);
    unicode_str[0] = '\0';
    for (size_t i = 0; i < len; i++) {
        char buffer[7];
        snprintf(buffer, sizeof(buffer), "\\u%04x", input[i]);
        strcat(unicode_str, buffer);
    }
    return unicode_str;
}

char* create_temp_file_with_unicode_content() {
    char random_string[37];
    generate_random_string(random_string, 36);
    
    char *unicode_string = convert_to_unicode(random_string);
    
    char temp_file_path[] = "temp_file.txt";
    FILE *temp_file = fopen(temp_file_path, "w");
    if (temp_file != NULL) {
        fputs(unicode_string, temp_file);
        fclose(temp_file);
    }

    free(unicode_string);
    return realpath(temp_file_path, NULL);
}

int main() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 5; ++i) {
        char *path = create_temp_file_with_unicode_content();
        if (path) {
            printf("%s\n", path);
            free(path);
        }
    }
    return 0;
}