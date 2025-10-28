#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Note: C doesn't have built-in XML/XPath support.
// This is a simplified implementation that searches for id attributes.
// For production use, consider libraries like libxml2.

char* executeXPath(const char* xpathValue, const char* xmlFileName) {
    FILE* file = fopen(xmlFileName, "r");
    if (file == NULL) {
        char* error = (char*)malloc(100);
        strcpy(error, "Error: Could not open file");
        return error;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* xmlContent = (char*)malloc(fileSize + 1);
    fread(xmlContent, 1, fileSize, file);
    xmlContent[fileSize] = '\0';
    fclose(file);

    char searchPattern[256];
    sprintf(searchPattern, "id=\"%s\"", xpathValue);

    char* result = (char*)malloc(1000);
    result[0] = '\0';

    char* pos = strstr(xmlContent, searchPattern);
    if (pos == NULL) {
        sprintf(searchPattern, "id='%s'", xpathValue);
        pos = strstr(xmlContent, searchPattern);
    }

    if (pos != NULL) {
        char* tagStart = pos;
        while (tagStart > xmlContent && *tagStart != '<') {
            tagStart--;
        }

        char* tagNameEnd = tagStart + 1;
        while (*tagNameEnd != ' ' && *tagNameEnd != '>' && *tagNameEnd != '\0') {
            tagNameEnd++;
        }

        int tagNameLen = (int)(tagNameEnd - tagStart - 1);
        char tagName[256];
        strncpy(tagName, tagStart + 1, (size_t)tagNameLen);
        tagName[tagNameLen] = '\0';

        char* contentStart = strchr(pos, '>');
        if (contentStart != NULL) {
            contentStart++;
            char endTag[256];
            sprintf(endTag, "</%s", tagName);
            char* contentEnd = strstr(contentStart, endTag);
            if (contentEnd != NULL) {
                int contentLen = (int)(contentEnd - contentStart);
                char content[1000];
                strncpy(content, contentStart, (size_t)contentLen);
                content[contentLen] = '\0';
                sprintf(result, "%s: %s", tagName, content);
            }
        }
    }

    free(xmlContent);
    return result;
}

int main(int argc, char* argv[]) {
    char* result;

    // Test case 1
    printf("Test Case 1:\n");
    result = executeXPath("1", "test1.xml");
    printf("%s\n\n", result);
    free(result);

    // Test case 2
    printf("Test Case 2:\n");
    result = executeXPath("2", "test2.xml");
    printf("%s\n\n", result);
    free(result);

    // Test case 3
    printf("Test Case 3:\n");
    result = executeXPath("3", "test3.xml");
    printf("%s\n\n", result);
    free(result);

    // Test case 4
    printf("Test Case 4:\n");
    result = executeXPath("item1", "test4.xml");
    printf("%s\n\n", result);
    free(result);

    // Test case 5
    printf("Test Case 5:\n");
    result = executeXPath("main", "test5.xml");
    printf("%s\n", result);
    free(result);
    
    return 0;
}
