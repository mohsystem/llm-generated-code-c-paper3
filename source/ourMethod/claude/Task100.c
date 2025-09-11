
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_FILE_SIZE (100 * 1024 * 1024) // 100MB limit
#define MAX_LINE_LENGTH 10000
#define ERROR_BUFFER_SIZE 256

void search_file(const char* regex_pattern, const char* file_name) {
    if (!regex_pattern || !file_name || !*regex_pattern || !*file_name) {
        fprintf(stderr, "Pattern and filename must not be null or empty\\n");
        exit(1);
    }

    // Compile pattern
    regex_t regex;
    char error_buffer[ERROR_BUFFER_SIZE];
    int ret = regcomp(&regex, regex_pattern, REG_EXTENDED);
    if (ret) {
        regerror(ret, &regex, error_buffer, ERROR_BUFFER_SIZE);
        fprintf(stderr, "Invalid regex pattern: %s\\n", error_buffer);
        exit(1);
    }

    // Check file size
    struct stat st;
    if (stat(file_name, &st) != 0) {
        regfree(&regex);
        fprintf(stderr, "Cannot access file: %s\\n", strerror(errno));
        exit(1);
    }

    if (st.st_size > MAX_FILE_SIZE) {
        regfree(&regex);
        fprintf(stderr, "File too large: maximum size is %d bytes\\n", MAX_FILE_SIZE);
        exit(1);
    }

    // Open file
    FILE* file = fopen(file_name, "r");
    if (!file) {
        regfree(&regex);
        fprintf(stderr, "Cannot open file: %s\\n", strerror(errno));
        exit(1);
    }

    // Read and search file
    char line[MAX_LINE_LENGTH + 1];
    size_t line_num = 0;

    while (fgets(line, sizeof(line), file)) {
        line_num++;
        size_t len = strlen(line);
        
        // Remove newline if present
        if (len > 0 && line[len-1] == '\\n') {
            line[len-1] = '\\0';
            len--;
        }

        if (len == MAX_LINE_LENGTH) {
            fprintf(stderr, "Warning: Line %zu exceeds maximum length and may be truncated\\n", 
                    line_num);
        }

        if (regexec(&regex, line, 0, NULL, 0) == 0) {
            printf("Line %zu: %s\\n", line_num, line);
        }
    }

    // Cleanup
    fclose(file);
    regfree(&regex);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <regex_pattern> <filename>\\n", argv[0]);
        return 1;
    }

    search_file(argv[1], argv[2]);
    return 0;
}
