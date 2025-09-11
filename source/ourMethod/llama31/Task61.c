#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

xmlNodePtr parseXml(const char* xmlString) {
    xmlDocPtr doc = xmlParseDoc((const xmlChar*)xmlString);
    if (doc == NULL) {
        return NULL;
    }
    return xmlDocGetRootElement(doc);
}

int main() {
    const char* xmlString = "<root><child>text</child></root>";
    xmlNodePtr root = parseXml(xmlString);
    if (root != NULL) {
        printf("Root Element: %s\n", root->name);
    }
    return 0;
}