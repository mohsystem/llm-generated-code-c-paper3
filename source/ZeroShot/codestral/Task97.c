#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <stdio.h>
#include <string.h>

char* xPathQuery(const char* xmlFileName, const char* xpath) {
    xmlDocPtr doc = xmlReadFile(xmlFileName, NULL, 0);
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    xmlXPathObjectPtr result = xmlXPathEvalExpression((xmlChar*)xpath, context);
    xmlChar* keyword = xmlNodeListGetString(doc, result->nodesetval->nodeTab[0]->xmlChildrenNode, 1);
    char* resultStr = strdup((char*)keyword);
    xmlFree(keyword);
    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return resultStr;
}

int main(int argc, char* argv[]) {
    char* result = xPathQuery(argv[1], argv[2]);
    printf("%s\n", result);
    free(result);
    return 0;
}