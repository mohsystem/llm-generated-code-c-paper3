#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdio.h>
#include <stdlib.h>

void parseXML(const char* xmlString) {
    xmlDocPtr doc;
    xmlNodePtr root;

    doc = xmlParseDoc((const xmlChar*)xmlString);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse XML\n");
        return;
    }

    root = xmlDocGetRootElement(doc);
    if (root == NULL) {
        fprintf(stderr, "Empty document\n");
        xmlFreeDoc(doc);
        return;
    }

    printf("Root Element: %s\n", root->name);

    xmlFreeDoc(doc);
}

int main() {
    const char* testCases[] = {
        "<root><child>Text</child></root>",
        "<person><name>John</name><age>30</age></person>",
        "<catalog><book id='bk101'><author>John Smith</author><title>XML for Dummies</title></book></catalog>",
        "<note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don't forget me this weekend!</body></note>",
        "<student><name>Alice</name><age>25</age></student>"
    };

    for (int i = 0; i < 5; ++i) {
        parseXML(testCases[i]);
    }

    return 0;
}