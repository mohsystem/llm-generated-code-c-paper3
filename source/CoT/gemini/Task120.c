#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to escape HTML characters
void escapeHtml(char* input, char* output) {
    int i = 0, j = 0;
    while (input[i] != '\0') {
        switch (input[i]) {
            case '<':
                strcpy(output + j, "&lt;");
                j += 4;
                break;
            case '>':
                strcpy(output + j, "&gt;");
                j += 4;
                break;
            case '&':
                strcpy(output + j, "&amp;");
                j += 5;
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
    char userInput[1000]; 
    char escapedInput[5000]; // Larger to accommodate escaped characters


    printf("<form method=\"post\">\n");
    printf("Enter text: <input type=\"text\" name=\"userInput\"><br>\n");
    printf("<input type=\"submit\" value=\"Submit\">\n");
    printf("</form>\n");

    printf("Enter your input: ");
    fgets(userInput, sizeof(userInput), stdin);
    userInput[strcspn(userInput, "\n")] = '\0'; // Remove trailing newline


    escapeHtml(userInput, escapedInput);
    printf("<p>You entered: %s</p>\n", escapedInput);

    return 0;
}