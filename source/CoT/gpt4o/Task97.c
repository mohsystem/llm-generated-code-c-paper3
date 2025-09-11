#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

char* executeXPathQuery(const char* xmlFilePath, const char* xpathValue) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx; 
    xmlXPathObjectPtr xpathObj; 

    doc = xmlParseFile(xmlFilePath);
    if (doc == NULL) {
        return "Error: Unable to parse XML file.";
    }

    xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return "Error: Unable to create new XPath context.";
    }

    xpathObj = xmlXPathEvalExpression((xmlChar*)xpathValue, xpathCtx);
    if (xpathObj == NULL) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return "Error: Unable to evaluate XPath expression.";
    }

    xmlNodeSetPtr nodes = xpathObj->nodesetval;
    xmlBufferPtr buffer = xmlBufferCreate();
    for (int i = 0; i < nodes->nodeNr; i++) {
        xmlNodePtr node = nodes->nodeTab[i];    
        xmlNodeDump(buffer, doc, node, 0, 1);
    }

    char* result = (char*)malloc(buffer->use + 1);
    strcpy(result, (const char*)buffer->content);

    xmlBufferFree(buffer);
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return result;
}

int main() {
    const char* xmlFilePath = "example.xml"; // Replace with actual XML file path
    const char* xpathValue = "/tag[@id='1']"; // Replace with actual XPath

    // Test cases
    printf("%s\n", executeXPathQuery(xmlFilePath, xpathValue));
    printf("%s\n", executeXPathQuery("another_example.xml", "/tag[@id='2']"));
    printf("%s\n", executeXPathQuery("example.xml", "/tag[@id='3']"));
    printf("%s\n", executeXPathQuery("wrongfile.xml", "/tag[@id='1']"));
    printf("%s\n", executeXPathQuery("example.xml", "/wrongtag[@id='1']"));

    return 0;
}