#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* generate_random_string(int length) {
    char* random_string = malloc(length + 1);
    const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length; i++) {
        int key = rand() % (int) (sizeof charset - 1);
        random_string[i] = charset[key];
    }
    random_string[length] = '\0';
    return random_string;
}

char* convert_string_to_unicode(const char* input) {
    int length = strlen(input);
    char* unicode_string = malloc(length * 6 + 1);
    char buffer[7];
    int index = 0;
    for (int i = 0; i < length; i++) {
        sprintf(buffer, "\\u%04x", (unsigned char) input[i]);
        strcpy(unicode_string + index, buffer);
        index += 6;
    }
    unicode_string[index] = '\0';
    return unicode_string;
}

char* create_temp_file_with_random_unicode_string() {
    char* random_string = generate_random_string(10);
    char* unicode_string = convert_string_to_unicode(random_string);

    char* temp_file_path = malloc(20);
    sprintf(temp_file_path, "temp_%ld.txt", time(NULL));

    FILE* fp = fopen(temp_file_path, "w");
    fprintf(fp, "%s", unicode_string);
    fclose(fp);

    free(random_string);
    free(unicode_string);

    return temp_file_path;
}

int main() {
    char* temp_file_path = create_temp_file_with_random_unicode_string();
    printf("Temporary file path: %s\n", temp_file_path);
    free(temp_file_path);
    return 0;
}