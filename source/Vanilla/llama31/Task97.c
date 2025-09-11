#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

void execute_xpath(const char* xpath, const char* xml_file) {
    xmlDocPtr doc;
    xmlXPathContextPtr ctxt;
    xmlXPathObjectPtr result;

    doc = xmlParseFile(xml_file);
    if (doc == NULL) {
        fprintf(stderr, "Error parsing XML file\n");
        return;
    }

    ctxt = xmlXPathNewContext(doc);
    if (ctxt == NULL) {
        fprintf(stderr, "Error creating XPath context\n");
        xmlFreeDoc(doc);
        return;
    }

    result = xmlXPathEvalExpression((const xmlChar*)xpath, ctxt);
    if (result == NULL) {
        fprintf(stderr, "Error evaluating XPath expression\n");
        xmlXPathFreeContext(ctxt);
        xmlFreeDoc(doc);
        return;
    }

    if (result->nodesetval != NULL) {
        for (int i = 0; i < result->nodesetval->nodeNr; i++) {
            xmlNodePtr node = result->nodesetval->nodeTab[i];
            if (node->children != NULL && node->children->content != NULL) {
                printf("%s\n", node->children->content);
            }
        }
    }

    xmlXPathFreeObject(result);
    xmlXPathFreeContext(ctxt);
    xmlFreeDoc(doc);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: ./Task97 <xpath> <xmlfile>\n");
        return 1;
    }
    execute_xpath(argv[1], argv[2]);
    return 0;
}