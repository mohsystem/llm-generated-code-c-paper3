#include <stdio.h>
#include <string.h>

#define MAX_INPUT 100

int main() {
    char input[MAX_INPUT];
    char *inputs[MAX_INPUT];
    int count = 0;
    
    printf("Enter input to display on web page (type 'end' to finish): \n");
    while (1) {
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character
        if (strcmp(input, "end") == 0) {
            break;
        }
        inputs[count] = strdup(input);
        count++;
    }
    
    for (int i = 0; i < count; i++) {
        printf("<p>%s</p>\n", inputs[i]);
        free(inputs[i]);
    }
    
    return 0;
}