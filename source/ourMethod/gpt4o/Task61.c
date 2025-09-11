#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>

const char* getRootElement(const char* xmlString) {
    xmlDocPtr doc = xmlReadMemory(xmlString, strlen(xmlString), NULL, NULL, XML_PARSE_NOENT);
    if (doc == NULL) {
        return NULL;
    }
    xmlNodePtr root = xmlDocGetRootElement(doc);
    const char* rootName = (root != NULL) ? (const char*)root->name : NULL;
    xmlFreeDoc(doc);
    return rootName;
}

int main() {
    printf("%s\n", getRootElement("<root><child /></root>")); // Test case 1
    printf("%s\n", getRootElement("<a><b></b></a>")); // Test case 2
    printf("%s\n", getRootElement("<library><book /></library>")); // Test case 3
    printf("%s\n", getRootElement("<data></data>")); // Test case 4
    printf("%s\n", getRootElement("<info><item></item></info>")); // Test case 5
    return 0;
}