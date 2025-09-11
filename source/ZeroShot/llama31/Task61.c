// Note: This example uses libxml2 which is not included here due to complexity.
// You would need to install and link against libxml2 to use this code.

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdio.h>
#include <string.h>

void parseXML(const char* xmlString) {
    xmlDocPtr doc = xmlParseDoc((const xmlChar*)xmlString);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse XML\n");
        return;
    }
    xmlNodePtr root = xmlDocGetRootElement(doc);
    if (root != NULL) {
        printf("Root Element: %s\n", root->name);
    }
    xmlFreeDoc(doc);
}

int main() {
    const char* testCases[] = {
        "<root><child>Text</child></root>",
        "<person><name>John</name><age>30</age></person>",
        "<catalog><book id='bk101'><author>John Smith</author></book></catalog>",
        "<note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don't forget me this weekend!</body></note>",
        "<empty/>"
    };

    for (int i = 0; i < 5; ++i) {
        parseXML(testCases[i]);
    }
    return 0;
}