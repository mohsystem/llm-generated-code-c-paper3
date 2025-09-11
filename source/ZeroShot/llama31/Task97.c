#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>

int main(int argc, char** argv) {
    if (argc < 4) {
        printf("Usage: task97 <xpath> <xmlfile> <id>\n");
        return 1;
    }

    char* xpath = argv[1];
    char* xmlFile = argv[2];
    char* id = argv[3];

    xmlDocPtr doc;
    xmlNodePtr root;
    xmlXPathContextPtr context;
    xmlXPathObjectPtr result;

    doc = xmlParseFile(xmlFile);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse XML file\n");
        return 1;
    }

    root = xmlDocGetRootElement(doc);
    if (root == NULL) {
        fprintf(stderr, "Empty XML document\n");
        xmlFreeDoc(doc);
        return 1;
    }

    context = xmlXPathNewContext(doc);
    if (context == NULL) {
        fprintf(stderr, "Failed to create XPath context\n");
        xmlFreeDoc(doc);
        return 1;
    }

    char* xpathQuery = malloc(strlen(xpath) + strlen(id) + 1);
    sprintf(xpathQuery, "%s", xpath);
    char* pos = strstr(xpathQuery, "{id}");
    if (pos != NULL) {
        strcpy(pos, id);
        pos += strlen(id);
        *pos = '\0';
    }

    result = xmlXPathEvalExpression((const xmlChar*)xpathQuery, context);
    if (result == NULL) {
        fprintf(stderr, "Failed to evaluate XPath expression\n");
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        free(xpathQuery);
        return 1;
    }

    if (result->nodesetval != NULL) {
        for (int i = 0; i < result->nodesetval->nodeNr; i++) {
            xmlNodePtr node = result->nodesetval->nodeTab[i];
            if (node->type == XML_ELEMENT_NODE) {
                printf("Result: %s\n", xmlNodeGetContent(node));
            }
        }
    }

    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
    free(xpathQuery);

    return 0;
}