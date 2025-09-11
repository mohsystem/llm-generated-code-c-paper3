#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

char *executeXPathQuery(const char *xmlFileName, const char *xpathExpression) {
    xmlDocPtr doc = xmlParseFile(xmlFileName);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse %s\n", xmlFileName);
        return NULL;
    }

    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (context == NULL) {
        xmlFreeDoc(doc);
        fprintf(stderr, "Failed to create XPath context\n");
        return NULL;
    }

    xmlXPathObjectPtr result = xmlXPathEvalExpression((const xmlChar *)xpathExpression, context);
    xmlXPathFreeContext(context);

    if (result == NULL) {
        xmlFreeDoc(doc);
        fprintf(stderr, "Failed to evaluate XPath\n");
        return NULL;
    }

    char *resultStr = NULL;
    if (xmlNodeSetIsEmpty(result->nodesetval) == 0) {
        xmlNodePtr node = result->nodesetval->nodeTab[0];
        if (node && node->children && node->children->content) {
            resultStr = (char *)xmlStrdup(node->children->content);
        }
    }

    xmlXPathFreeObject(result);
    xmlFreeDoc(doc);
    return resultStr;
}

int main() {
    // Test cases
    char *result;

    result = executeXPathQuery("test1.xml", "/tag[@id='1']");
    if (result) {
        printf("%s\n", result);
        xmlFree(result);
    }

    result = executeXPathQuery("test2.xml", "/tag[@id='2']");
    if (result) {
        printf("%s\n", result);
        xmlFree(result);
    }

    result = executeXPathQuery("test3.xml", "/tag[@id='3']");
    if (result) {
        printf("%s\n", result);
        xmlFree(result);
    }

    result = executeXPathQuery("test4.xml", "/tag[@id='4']");
    if (result) {
        printf("%s\n", result);
        xmlFree(result);
    }

    result = executeXPathQuery("test5.xml", "/tag[@id='5']");
    if (result) {
        printf("%s\n", result);
        xmlFree(result);
    }

    return 0;
}