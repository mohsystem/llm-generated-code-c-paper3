#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

char* executeXPath(const char* xmlFile, const char* xpathExpr) {
    xmlDocPtr doc = xmlParseFile(xmlFile);
    if (doc == NULL) {
        fprintf(stderr, "Error: unable to parse file %s\n", xmlFile);
        return NULL;
    }

    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (context == NULL) {
        xmlFreeDoc(doc);
        fprintf(stderr, "Error: unable to create new XPath context\n");
        return NULL;
    }

    xmlXPathObjectPtr result = xmlXPathEvalExpression((xmlChar *)xpathExpr, context);
    if (result == NULL) {
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        fprintf(stderr, "Error: unable to evaluate xpath expression %s\n", xpathExpr);
        return NULL;
    }

    xmlNodeSetPtr nodeset = result->nodesetval;
    char* output = NULL;
    if (!xmlXPathNodeSetIsEmpty(nodeset)) {
        xmlNodePtr node = nodeset->nodeTab[0];
        output = (char *)xmlNodeGetContent(node);
    } else {
        printf("No result\n");
    }

    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
    return output;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: ./program <xpath> <xmlFile>\n");
        return 1;
    }
    char* result = executeXPath(argv[2], argv[1]);
    if (result) {
        printf("%s\n", result);
    }
    return 0;
}