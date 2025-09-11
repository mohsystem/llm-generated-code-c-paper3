
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_XML_LENGTH 1000
#define MAX_TAG_LENGTH 100

char* getRootElement(const char* xmlString) {
    if (xmlString == NULL || strlen(xmlString) == 0) {
        return strdup("");
    }
    
    static char result[MAX_TAG_LENGTH];
    size_t startIdx = 0;
    
    // Check for XML declaration
    if (strncmp(xmlString, "<?xml", 5) == 0) {
        char* declEnd = strstr(xmlString, "?>");
        if (declEnd) {
            startIdx = (declEnd - xmlString) + 2;
        }
    }
    
    // Find first < after XML declaration
    while (xmlString[startIdx] && xmlString[startIdx] != '<') {
        startIdx++;
    }
    
    if (!xmlString[startIdx]) {
        return strdup("");
    }
    
    // Find end of root tag
    size_t endIdx = startIdx;
    while (xmlString[endIdx] && xmlString[endIdx] != '>') {
        endIdx++;
    }
    
    if (!xmlString[endIdx]) {
        return strdup("");
    }
    
    // Extract root element name
    size_t tagLen = endIdx - startIdx - 1;
    if (tagLen >= MAX_TAG_LENGTH) {
        return strdup("");
    }
    
    strncpy(result, xmlString + startIdx + 1, tagLen);
    result[tagLen] = '\\0';
    
    // Remove any attributes
    char* space = strchr(result, ' ');
    if (space) {
        *space = '\\0';
    }
    
    return strdup(result);
}

void test(const char* xml) {
    printf("Input: %s\\n", xml);
    char* root = getRootElement(xml);
    printf("Root: %s\\n\\n", root);
    free(root);
}

int main() {
    // Test cases
    test("<?xml version=\\"1.0\\"?><root><child>Test</child></root>");
    test("<simple>content</simple>");
    test("<!-- comment --><root attr=\\"value\\">content</root>");
    test("<?xml version=\\"1.0\\" encoding=\\"UTF-8\\"?><root/>");
    test("<root xmlns=\\"http://example.com\\">test</root>");
    
    return 0;
}
