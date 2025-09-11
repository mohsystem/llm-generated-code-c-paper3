#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

char* executeXPathQuery(const char *xmlFilePath, const char *xpathValue) {
    xmlDocPtr doc = xmlReadFile(xmlFilePath, NULL, 0);
    if (doc == NULL) {
        return "Error loading the XML file";
    }

    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return "Error creating XPath context";
    }

    char xpathExpr[256];
    snprintf(xpathExpr, sizeof(xpathExpr), "/tag[@id='%s']", xpathValue);
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar*)xpathExpr, xpathCtx);
    if (xpathObj == NULL) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return "Error evaluating XPath expression";
    }

    xmlNodeSetPtr nodes = xpathObj->nodesetval;
    char *result;
    if (nodes->nodeNr > 0) {
        result = (char*)xmlNodeGetContent(nodes->nodeTab[0]);
    } else {
        result = "No result found";
    }

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return result;
}

int main() {
    printf("Result 1: %s\n", executeXPathQuery("example1.xml", "value1"));
    printf("Result 2: %s\n", executeXPathQuery("example2.xml", "value2"));
    printf("Result 3: %s\n", executeXPathQuery("example3.xml", "value3"));
    printf("Result 4: %s\n", executeXPathQuery("example4.xml", "value4"));
    printf("Result 5: %s\n", executeXPathQuery("example5.xml", "value5"));
    return 0;
}