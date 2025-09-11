#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024

void escapeHtml(char *input, char *output) {
    int i = 0, j = 0;
    while (input[i] != '\0') {
        switch (input[i]) {
            case '&':
                strcpy(output + j, "&amp;");
                j += 5;
                break;
            case '<':
                strcpy(output + j, "&lt;");
                j += 4;
                break;
            case '>':
                strcpy(output + j, "&gt;");
                j += 4;
                break;
            case '"':
                strcpy(output + j, "&quot;");
                j += 6;
                break;
            case '\'':
                strcpy(output + j, "&#39;");
                j += 5;
                break;
            default:
                output[j] = input[i];
                j++;
        }
        i++;
    }
    output[j] = '\0';
}


int main() {
    char testCases[5][MAX_INPUT_LENGTH] = {
        "<script>alert('XSS')</script>",
        "Test input with special characters: & < > \" '",
        "Normal text",
        "",
        "12345"
    };

    for (int i = 0; i < 5; i++) {
        char escapedInput[MAX_INPUT_LENGTH * 6]; // Increased size for escaped characters
        escapeHtml(testCases[i], escapedInput);

        printf("<!DOCTYPE html>\n");
        printf("<html>\n");
        printf("<head>\n");
        printf("<title>User Input Display</title>\n");
        printf("</head>\n");
        printf("<body>\n");
        printf("<h1>User Input:</h1>\n");
        printf("<p>%s</p>\n", escapedInput);
        printf("</body>\n");
        printf("</html>\n");
        printf("--------------------\n");

    }
    return 0;
}