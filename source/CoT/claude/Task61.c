
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* findXMLRoot(const char* xml, char* result) {
    if (!xml || !result) {
        return NULL;
    }
    
    result[0] = '\\0';
    
    // Skip leading whitespace
    while (*xml && isspace(*xml)) xml++;
    
    // Skip comments
    while (strncmp(xml, "<!--", 4) == 0) {
        xml = strstr(xml, "-->");
        if (!xml) return result;
        xml += 3;
        while (*xml && isspace(*xml)) xml++;
    }
    
    // Find first tag
    const char* start = strchr(xml, '<');
    if (!start) return result;
    start++;
    
    const char* end = strchr(start, '>');
    if (!end) return result;
    
    // Copy tag name
    int i = 0;
    while (start < end && !isspace(*start) && *start != '/' && i < 99) {
        result[i++] = *start++;
    }
    result[i] = '\\0';
    
    return result;
}

int main() {
    char result[100];
    const char* test_cases[] = {
        "<root><child>value</child></root>",
        "<document><header>Title</header><body>Content</body></document>",
        "<book id='1'><title>XML Basics</title></book>",
        "<!-- comment --><data><item>1</item></data>",
        "<root attr='val'/>"
    };
    
    for (int i = 0; i < 5; i++) {
        findXMLRoot(test_cases[i], result);
        printf("Root %d: %s\\n", i+1, result);
    }
    
    return 0;
}
