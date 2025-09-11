#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

void execute_xpath(const char* xml_file, const char* xpath_query) {
    // Validate file path to prevent path traversal
    if (strstr(xml_file, "../") != NULL || strstr(xml_file, "..\\") != NULL) {
        printf("Invalid file path\n");
        return;
    }

    xmlDocPtr doc;
    xmlNodePtr root;
    xmlXPathContextPtr context;
    xmlXPathObjectPtr result;

    try {
        // Read XML file
        doc = xmlParseFile(xml_file);
        if (doc == NULL) {
            fprintf(stderr, "Failed to parse XML file\n");
            exit(EXIT_FAILURE);
        }

        root = xmlDocGetRootElement(doc);
        if (root == NULL) {
            fprintf(stderr, "Empty XML document\n");
            exit(EXIT_FAILURE);
        }

        // Execute XPath query
        context = xmlXPathNewContext(doc);
        if (context == NULL) {
            fprintf(stderr, "Failed to create XPath context\n");
            exit(EXIT_FAILURE);
        }

        char* query = strdup(xpath_query);
        char* id = strstr(query, "{id}");
        if (id != NULL) {
            strcpy(id, "1");  // Example replacement, adjust as needed
        }

        result = xmlXPathEvalExpression((const xmlChar*)query, context);
        if (result == NULL) {
            fprintf(stderr, "Failed to evaluate XPath expression\n");
            exit(EXIT_FAILURE);
        }

        free(query);

        // Print results
        if (result->nodesetval != NULL) {
            for (int i = 0; i < result->nodesetval->nodeNr; ++i) {
                xmlNodePtr node = result->nodesetval->nodeTab[i];
                if (node->type == XML_ELEMENT_NODE) {
                    printf("%s\n", xmlNodeGetContent(node));
                }
            }
        }

        // Clean up
        xmlXPathFreeObject(result);
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
    } catch (...) {
        fprintf(stderr, "An error occurred\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <xpath> <xml_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    execute_xpath(argv[2], argv[1]);
    return EXIT_SUCCESS;
}