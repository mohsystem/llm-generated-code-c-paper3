
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void trim(char *str) {
    int start = 0, end = strlen(str) - 1;
    
    while(isspace(str[start])) start++;
    while(end > start && isspace(str[end])) end--;
    
    int i;
    for(i = 0; i <= end-start; i++)
        str[i] = str[start+i];
    str[i] = '\\0';
}

void findRootElement(const char* xml, char* result) {
    char temp[1000];
    strcpy(temp, xml);
    trim(temp);
    
    result[0] = '\\0';
    if (temp[0] != '<' || temp[strlen(temp)-1] != '>') {
        return;
    }
    
    int firstSpace = -1;
    int firstClose = -1;
    
    for(int i = 0; temp[i]; i++) {
        if(temp[i] == ' ' && firstSpace == -1) 
            firstSpace = i;
        if(temp[i] == '>' && firstClose == -1) 
            firstClose = i;
    }
    
    int end = firstSpace == -1 ? strlen(temp) : firstSpace;
    end = end < firstClose ? end : firstClose;
    
    if(end <= 1) {
        return;
    }
    
    strncpy(result, temp + 1, end - 1);
    result[end-1] = '\\0';
}

int main() {
    char* testCases[] = {
        "<root><child>Data</child></root>",
        "<note><to>John</to><from>Jane</from></note>",
        "<book category='fiction'><title>Example</title></book>",
        "<data />",
        "<invalid"
    };
    
    char result[1000];
    for(int i = 0; i < 5; i++) {
        printf("Input: %s\\n", testCases[i]);
        findRootElement(testCases[i], result);
        printf("Root element: %s\\n\\n", result);
    }
    
    return 0;
}
