#include <stdio.h>
#include <string.h>
#include <libxml/parser.h> // Requires libxml2 library
#include <libxml/tree.h>

char* getRootElement(const char* xmlString) {
    if (xmlString == NULL || strlen(xmlString) == 0) {
        return NULL;
    }

    xmlDocPtr doc = xmlReadMemory(xmlString, strlen(xmlString), "input.xml", NULL, 0);
    if (doc == NULL) {
        return NULL;
    }

    xmlNodePtr root = xmlDocGetRootElement(doc);
    if (root != NULL) {
        char* rootName = (char*)xmlStrdup(root->name);
        xmlFreeDoc(doc);
        return rootName;
    }

    xmlFreeDoc(doc);
    return NULL;
}

int main() {
    char* xml1 = "<note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don't forget me this weekend!</body></note>";
    char* root1 = getRootElement(xml1);
    if (root1 != NULL) {
        printf("%s\n", root1); // Output: note
        xmlFree(root1);
    }


    char* xml2 = "<bookstore><book><title lang=\"en\">Harry Potter</title><price>29.99</price></book></bookstore>";
    char* root2 = getRootElement(xml2);
    if (root2 != NULL) {
        printf("%s\n", root2); // Output: bookstore
        xmlFree(root2);
    }


    char* xml3 = "<root><element1 /><element2></element2></root>";
    char* root3 = getRootElement(xml3);
    if (root3 != NULL) {
        printf("%s\n", root3); // Output: root
        xmlFree(root3);
    }

    char* xml4 = "";
    char* root4 = getRootElement(xml4);
    if (root4 != NULL) {
        printf("%s\n", root4); // Output: (nothing)
        xmlFree(root4);
    }


    char* xml5 = NULL;
    char* root5 = getRootElement(xml5);
     if (root5 != NULL) {
        printf("%s\n", root5); // Output: (nothing)
        xmlFree(root5);
    }

    return 0;
}