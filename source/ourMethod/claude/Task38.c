
// Task38.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 100

void printHeader() {
    printf("Content-type: text/html\\n\\n");
    printf("<!DOCTYPE html>\\n");
    printf("<html><head><title>Input Form</title></head>\\n");
    printf("<body>\\n");
}

void printFooter() {
    printf("</body></html>\\n");
}

void escapeHtml(const char* input, char* output, size_t outSize) {
    size_t i = 0, j = 0;
    while(input[i] && j < outSize - 1) {
        switch(input[i]) {
            case '&':
                if(j + 5 >= outSize) break;
                strcpy(&output[j], "&amp;");
                j += 5;
                break;
            case '"':
                if(j + 6 >= outSize) break;
                strcpy(&output[j], "&quot;");
                j += 6;
                break;
            case '\\'':
                if(j + 6 >= outSize) break;
                strcpy(&output[j], "&apos;");
                j += 6;
                break;
            case '<':
                if(j + 4 >= outSize) break;
                strcpy(&output[j], "&lt;");
                j += 4;
                break;
            case '>':
                if(j + 4 >= outSize) break;
                strcpy(&output[j], "&gt;");
                j += 4;
                break;
            default:
                if(isprint(input[i])) {
                    output[j++] = input[i];
                }
                break;
        }
        i++;
    }
    output[j] = '\\0';
}

void printForm() {
    printf("<form method='post'>\\n");
    printf("Enter text: <input type='text' name='userInput' maxlength='%d' required>\\n", MAX_INPUT);
    printf("<input type='submit' value='Submit'>\\n");
    printf("</form>\\n");
}

int main() {
    char *method = getenv("REQUEST_METHOD");
    char *length = getenv("CONTENT_LENGTH");
    char input[MAX_INPUT + 1] = {0};
    char escaped[MAX_INPUT * 6 + 1] = {0}; // Worst case each char needs 6 chars to escape

    printHeader();

    if(method && strcmp(method, "POST") == 0 && length) {
        int len = atoi(length);
        if(len > 0 && len <= MAX_INPUT) {
            fgets(input, sizeof(input), stdin);
            char *start = strstr(input, "userInput=");
            if(start) {
                start += 10; // Skip "userInput="
                char *end = strchr(start, '&');
                if(end) *end = '\\0';
                
                // URL decode and sanitize
                escapeHtml(start, escaped, sizeof(escaped));
                printf("<h2>You entered:</h2>\\n");
                printf("<p>%s</p>\\n", escaped);
            }
        }
    }

    printForm();
    printFooter();
    return 0;
}
