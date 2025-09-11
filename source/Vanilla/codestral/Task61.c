#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdio.h>

char* parseXml(const char* xml) {
    xmlDocPtr doc = xmlReadMemory(xml, strlen(xml), NULL, NULL, 0);
    if (doc == NULL) {
        fprintf(stderr, "Error parsing XML\n");
        return NULL;
    }
    xmlNodePtr root = xmlDocGetRootElement(doc);
    char* rootName = (char*)root->name;
    xmlFreeDoc(doc);
    return rootName;
}

int main() {
    const char* testCases[] = {
        "<root><element1>data</element1></root>",
        "<main><sub1>data1</sub1><sub2>data2</sub2></main>",
        "<parent><child1>child1 data</child1><child2>child2 data</child2></parent>",
        "<top><middle><bottom>bottom data</bottom></middle></top>",
        "<first><second><third><fourth>fourth data</fourth></third></second></first>"
    };

    for (int i = 0; i < 5; i++) {
        char* rootName = parseXml(testCases[i]);
        if (rootName != NULL) {
            printf("Root element of XML document is: %s\n", rootName);
        }
    }

    return 0;
}