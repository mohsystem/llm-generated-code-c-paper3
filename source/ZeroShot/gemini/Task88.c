#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *create_temp_file_with_unicode_string() {
    char random_string[11];
    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        int random_num = rand() % 62; // 0-61 for alphanumeric
        if (random_num < 26) {
            random_string[i] = 'A' + random_num;
        } else if (random_num < 52) {
            random_string[i] = 'a' + (random_num - 26);
        } else {
            random_string[i] = '0' + (random_num - 52);
        }
    }
    random_string[10] = '\0';

    char *unicode_string = (char*)malloc(sizeof(char) * 10 * 6 + 1); // \uXXXX format for each char
    if (!unicode_string) return NULL;
    int index = 0;

    for (int i = 0; i < 10; i++) {
        sprintf(unicode_string + index, "\\u%04x", (int)random_string[i]);
        index += 6;
    }

    char *temp_filename = tmpnam(NULL); // Generates a unique temp filename
    if (!temp_filename) {
        free(unicode_string);
        return NULL;
    }

    FILE *temp_file = fopen(temp_filename, "w");
    if (!temp_file) {
        free(unicode_string);
        return NULL;
    }


    fputs(unicode_string, temp_file);
    fclose(temp_file);
    free(unicode_string);
    return temp_filename; // returns the path, caller responsible for freeing it
}



int main() {
    for (int i = 0; i < 5; i++) {
        char *file_path = create_temp_file_with_unicode_string();
        if (file_path) {
            printf("Temporary file created: %s\n", file_path);
            remove(file_path);  // Clean up the temporary file
            free(file_path);
        } else {
            perror("Error creating temporary file");
        }
    }
    return 0;
}