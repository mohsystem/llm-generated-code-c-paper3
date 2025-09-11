#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

char* getRootElement(const char* xmlContent) {
    xmlDoc *document = xmlReadMemory(xmlContent, strlen(xmlContent), "noname.xml", NULL, 0);
    if (document == NULL) {
        return NULL;
    }
    xmlNode *root = xmlDocGetRootElement(document);
    char *rootName = (char *) root->name;
    xmlFreeDoc(document);
    return rootName;
}

int main() {
    printf("%s\n", getRootElement("<root><child/></root>")); // root
    printf("%s\n", getRootElement("<root></root>")); // root
    printf("%s\n", getRootElement("<a><b/></a>")); // a
    printf("%s\n", getRootElement("<parent><child1/><child2/></parent>")); // parent
    printf("%s\n", getRootElement("<data><item/></data>")); // data
    return 0;
}