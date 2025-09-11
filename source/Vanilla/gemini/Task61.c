#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

// Compile with: gcc -o xml_parser xml_parser.c `xml2-config --cflags --libs`

char* getRootElement(const char* xmlString) {
    xmlDocPtr doc = xmlReadMemory(xmlString, strlen(xmlString), "input.xml", NULL, 0);
    if (doc == NULL) {
        return NULL;
    }

    xmlNodePtr root = xmlDocGetRootElement(doc);
    if (root == NULL) {
         xmlFreeDoc(doc);
        return NULL;
    }

    char* rootName = (char*)xmlStrdup(root->name);

    xmlFreeDoc(doc); 
    return rootName;
}


int main() {
    char* xml1 = "<note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don't forget me this weekend!</body></note>";
    char* xml2 = "<book><title>The Great Gatsby</title><author>F. Scott Fitzgerald</author></book>";
    char* xml3 = "<person><name>John Doe</name><age>30</age></person>";
    char* xml4 = "<empty />";
    char* xml5 = "<malformed><tag> </malformed>";

    char *result;

    result = getRootElement(xml1);
    printf("%s\n", result ? result : "NULL"); xmlFree(result); // Output: note

    result = getRootElement(xml2);
    printf("%s\n", result ? result : "NULL"); xmlFree(result); // Output: book

    result = getRootElement(xml3);
    printf("%s\n", result ? result : "NULL"); xmlFree(result); // Output: person

    result = getRootElement(xml4);
    printf("%s\n", result ? result : "NULL"); xmlFree(result); // Output: empty

    result = getRootElement(xml5);
    printf("%s\n", result ? result : "NULL"); xmlFree(result); // Output: NULL

    return 0;
}