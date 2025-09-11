#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
#include <stdio.h>

const char* getRootElement(const char* xmlString) {
    xmlDocPtr doc = xmlReadMemory(xmlString, strlen(xmlString), nullptr, nullptr, 0);
    if (doc == nullptr) {
        fprintf(stderr, "Failed to parse XML document\n");
        return nullptr;
    }
    xmlNodePtr root = xmlDocGetRootElement(doc);
    const char* rootName = root->name;
    xmlFreeDoc(doc);
    return rootName;
}

int main() {
    const char* xmlString = "<root><child>Text</child></root>";
    const char* rootElement = getRootElement(xmlString);
    if (rootElement != nullptr) {
        printf("Root element: %s\n", rootElement);
    }
    return 0;
}