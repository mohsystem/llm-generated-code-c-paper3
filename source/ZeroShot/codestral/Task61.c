/* This code uses libxml2, a C library for parsing XML documents.
 * Please install libxml2 before compiling this code.
 * Compile with: gcc -o main main.c -lxml2
 */

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdio.h>

const char* getRootElement(const char* xml) {
    xmlDocPtr doc = xmlReadMemory(xml, strlen(xml), nullptr, nullptr, XML_PARSE_NONET);
    xmlNodePtr root_element = xmlDocGetRootElement(doc);
    const char* root_name = (char*)root_element->name;
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return root_name;
}

int main() {
    const char* xmls[] = {
        "<root><child>Hello</child></root>",
        "<root><child1><child2>World</child2></child1></root>",
        "<root><child1 attr='val1'><child2 attr='val2'>!</child2></child1></root>",
        "<root attr='val'></root>",
        "<root>Text</root>"
    };
    for (int i = 0; i < 5; i++) {
        printf("%s\n", getRootElement(xmls[i]));
    }
    return 0;
}