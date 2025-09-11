#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

char *executeXPath(const char *xmlFilePath, const char *xpathValue) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    char *result = NULL;


    doc = xmlParseFile(xmlFilePath);
    if (doc == NULL) {
        fprintf(stderr, "Error: could not parse file %s\n", xmlFilePath);
        return NULL;
    }

    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        fprintf(stderr, "Error: unable to create new XPath context\n");
        xmlFreeDoc(doc);
        return NULL;
    }

    xpathObj = xmlXPathEvalExpression((xmlChar *)xpathValue, xpathCtx);
    if (xpathObj == NULL) {
        fprintf(stderr, "Error: unable to evaluate XPath expression\n");
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    if (xpathObj->nodesetval && xpathObj->nodesetval->nodeNr > 0) {
        xmlNode *node = xpathObj->nodesetval->nodeTab[0];
        if (node->type == XML_TEXT_NODE || node->type == XML_ATTRIBUTE_NODE) {
            result = (char *)xmlNodeGetContent(node);
        }
    }

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);


    return result ? strdup(result) : NULL; // Return a copy to avoid memory issues
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <xml_file> <xpath_expression>\n", argv[0]);
        return 1;
    }
    char *xmlFile = argv[1];

    // Test cases
    char *result1 = executeXPath(xmlFile, "/data/entry[@id=1]");
    if(result1) { printf("%s\n", result1); free(result1);}

    char *result2 = executeXPath(xmlFile, "/data/entry[@id=2]");
     if(result2) { printf("%s\n", result2); free(result2);}

    char *result3 = executeXPath(xmlFile, "/data/entry[@id=3]");
     if(result3) { printf("%s\n", result3); free(result3);}

    char *result4 = executeXPath(xmlFile, "/data/entry[@id=4]");
     if(result4) { printf("%s\n", result4); free(result4);}

    char *result5 = executeXPath(xmlFile, "/data/entry[@id=5]");
     if(result5) { printf("%s\n", result5); free(result5);}

    return 0;
}