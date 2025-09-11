#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

char* getRootElement(const char* xmlString) {
    xmlDocPtr doc = xmlReadMemory(xmlString, strlen(xmlString), "noname.xml", NULL, 0);
    if (doc == NULL) {
        printf("Error parsing XML\n");
        return NULL;
    }
    xmlNodePtr root = xmlDocGetRootElement(doc);
    char* rootName = (char*)root->name;
    xmlFreeDoc(doc);
    return rootName;
}

int main() {
    printf("%s\n", getRootElement("<root><child></child></root>"));  // root
    printf("%s\n", getRootElement("<data><item></item></data>"));    // data
    printf("%s\n", getRootElement("<book><title></title></book>"));  // book
    printf("%s\n", getRootElement("<note><to></to></note>"));        // note
    printf("%s\n", getRootElement("<library><books></books></library>"));  // library
    return 0;
}