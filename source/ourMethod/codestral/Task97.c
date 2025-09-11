#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <xpath_expression> <xml_file_name>\n", argv[0]);
        return 1;
    }

    const char *xpath_expression = argv[1];
    const char *xml_file_name = argv[2];

    xmlDocPtr doc;
    xmlXPathContextPtr context;
    xmlXPathObjectPtr result;

    doc = xmlParseFile(xml_file_name);
    if (doc == NULL) {
        fprintf(stderr, "Error: Failed to parse XML file\n");
        return 1;
    }

    context = xmlXPathNewContext(doc);
    if (context == NULL) {
        fprintf(stderr, "Error: Unable to create XPath context\n");
        xmlFreeDoc(doc);
        return 1;
    }

    result = xmlXPathEvalExpression((xmlChar *)xpath_expression, context);
    if (result == NULL) {
        fprintf(stderr, "Error: Unable to evaluate XPath expression\n");
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return 1;
    }

    if (xmlXPathNodeSetIsEmpty(result->nodesetval)) {
        printf("No result\n");
    } else {
        xmlNodeSetPtr nodeset = result->nodesetval;
        xmlNodePtr node = nodeset->nodeTab[0];
        xmlChar *content = xmlNodeGetContent(node);
        printf("Result: %s\n", content);
        xmlFree(content);
    }

    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return 0;
}