#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdio.h>

const char* getRootElement(const char* xmlString) {
    xmlDocPtr doc = xmlParseDoc(xmlString);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse XML document\n");
        return NULL;
    }
    xmlNodePtr rootNode = xmlDocGetRootElement(doc);
    const char* rootElement = rootNode->name;
    xmlFreeDoc(doc);
    return rootElement;
}

int main() {
    const char* rootElement = getRootElement("<root><child>Content</child></root>");
    if (rootElement != NULL) {
        printf("%s\n", rootElement);
    }
    return 0;
}