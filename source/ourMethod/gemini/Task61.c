#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

xmlNodePtr getRootElement(const char *xmlString) {
    if (!xmlString || strlen(xmlString) == 0) {
        return NULL;
    }

    xmlDocPtr doc = xmlReadMemory(xmlString, strlen(xmlString), "input.xml", NULL, 0);
    if (doc == NULL) {
        return NULL;
    }

    xmlNodePtr root = xmlDocGetRootElement(doc);
    
    return root;
}

int main() {
    char *testCases[] = {
        "<root><element1>value1</element1><element2>value2</element2></root>",
        "<note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don't forget me this weekend!</body></note>",
        "<bookstore><book><title lang=\"en\">Harry Potter</title><price>29.99</price></book></bookstore>",
        "<!-- This is a comment --><root/>",
        ""
    };
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        xmlNodePtr root = getRootElement(testCases[i]);
        if (root != NULL) {
            printf("Root element: %s\n", root->name);
        } else {
            printf("Root element not found.\n");
        }
    }


    return 0;
}