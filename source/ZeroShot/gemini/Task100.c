#include <stdio.h>
#include <string.h>
#include <regex.h>

char* regexSearchInFile(const char* regex, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        char* error = (char*)malloc(100 * sizeof(char));
        snprintf(error,100,"Error reading file: %s", fileName);
        return error;
    }
    char* fileContent = NULL;
    size_t fileLength = 0;
    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);
    fileContent = (char*)malloc(fileLength + 1);
    fread(fileContent, 1, fileLength, file);
    fileContent[fileLength] = '\0';
    fclose(file);

    regex_t compiledRegex;
    int reti = regcomp(&compiledRegex, regex, REG_EXTENDED);
    if (reti) {
        char* error = (char*)malloc(100* sizeof(char));
        strcpy(error, "Invalid regular expression");
        free(fileContent);
        return error;
    }

    regmatch_t match;
    char* result = (char*)malloc(1024* sizeof(char)); // Adjust size if needed
    result[0] = '\0';

    char* remainingText = fileContent;
    while (regexec(&compiledRegex, remainingText, 1, &match, 0) == 0) {
         strncat(result, remainingText + match.rm_so, match.rm_eo - match.rm_so);
         strncat(result, "\n", 2);
         remainingText += match.rm_eo;
    }
    
    regfree(&compiledRegex);
    free(fileContent);
    if(strlen(result)==0) return "";

    return result;
}

int main() {
    printf("%s\n", regexSearchInFile("hello", "test.txt"));
    printf("%s\n", regexSearchInFile("\\d+", "test.txt"));
    printf("%s\n", regexSearchInFile("[a-zA-Z]+", "test.txt"));
    printf("%s\n", regexSearchInFile(".*", "test.txt"));
    printf("%s\n", regexSearchInFile("invalid(", "test.txt"));
    return 0;
}