#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

const char* getRootElement(const char* xmlContent) {
    xmlDoc *doc = xmlReadMemory(xmlContent, strlen(xmlContent), "noname.xml", NULL, 0);
    if (doc == NULL) {
        printf("Failed to parse document\n");
        return NULL;
    }
    xmlNode *root_element = xmlDocGetRootElement(doc);
    const char* rootName = (const char*)root_element->name;
    xmlFreeDoc(doc);
    return rootName;
}

int main() {
    const char* testCases[] = {
        "<root><child>Content</child></root>",
        "<bookstore><book><title>XML</title></book></bookstore>",
        "<note><to>User</to><from>AI</from></note>",
        "<greeting>Hello, world!</greeting>",
        "<data><item id='1'>Item1</item></data>"
    };

    for (int i = 0; i < 5; i++) {
        printf("Root element: %s\n", getRootElement(testCases[i]));
    }

    xmlCleanupParser();
    return 0;
}