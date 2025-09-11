#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>

void executeXPath(const char* xpath, const char* xmlFile) {
    // Read XML file
    xmlDocPtr doc = xmlParseFile(xmlFile);
    if (doc == NULL) {
        fprintf(stderr, "Error parsing XML file\n");
        return;
    }

    // Execute XPath query
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (context == NULL) {
        fprintf(stderr, "Error creating XPath context\n");
        xmlFreeDoc(doc);
        return;
    }

    char* id = strchr(xpath, '=');
    if (id == NULL) {
        fprintf(stderr, "Invalid XPath query\n");
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return;
    }
    id++;
    char* end = strchr(id, '}');
    if (end == NULL) {
        fprintf(stderr, "Invalid XPath query\n");
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return;
    }
    *end = '\0';

    xmlXPathObjectPtr result = xmlXPathEvalExpression((const xmlChar*)xpath, context);
    if (result == NULL) {
        fprintf(stderr, "Error executing XPath query\n");
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return;
    }

    // Print results
    if (result->nodesetval != NULL) {
        for (int i = 0; i < result->nodesetval->nodeNr; ++i) {
            xmlNodePtr node = result->nodesetval->nodeTab[i];
            if (node->type == XML_ELEMENT_NODE) {
                printf("Result: %s\n", xmlNodeGetContent(node));
            }
        }
    }

    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: ./Task97 <xpath> <xml_file>\n");
        return 1;
    }
    executeXPath(argv[1], argv[2]);
    return 0;
}