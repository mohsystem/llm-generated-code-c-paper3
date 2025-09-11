#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <stdio.h>

void executeXPath(const char* xpath, const char* xmlFileName) {
    xmlDocPtr doc = xmlReadFile(xmlFileName, NULL, 0);
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    xmlXPathObjectPtr result = xmlXPathEvalExpression((xmlChar*)xpath, context, NULL);
    xmlChar* xmlResult = xmlNodeListGetString(doc, result->nodesetval->nodeTab[0]->xmlChildrenNode, 1);
    printf("%s\n", xmlResult);
    xmlFree(xmlResult);
    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
    xmlCleanupParser();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <xpath> <xml_file_name>\n", argv[0]);
        return 1;
    }
    executeXPath(argv[1], argv[2]);
    return 0;
}