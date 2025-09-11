
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#define MAX_XPATH_LEN 1024
#define MAX_RESULT_LEN 4096

char* executeXPathQuery(const char* xmlFilePath, const char* xpathValue) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    char* result = malloc(MAX_RESULT_LEN);
    char query[MAX_XPATH_LEN];
    
    if (!result) {
        return "Error: Memory allocation failed";
    }
    result[0] = '\\0';

    // Initialize libxml
    xmlInitParser();

    // Check file exists and is readable
    FILE* file = fopen(xmlFilePath, "r");
    if (!file) {
        free(result);
        return "Error: Cannot access XML file";
    }
    fclose(file);

    // Parse XML file
    doc = xmlReadFile(xmlFilePath, NULL, XML_PARSE_NONET);
    if (!doc) {
        free(result);
        return "Error: Failed to parse XML file";
    }

    // Create xpath context
    xpathCtx = xmlXPathNewContext(doc);
    if (!xpathCtx) {
        xmlFreeDoc(doc);
        free(result);
        return "Error: Failed to create XPath context";
    }

    // Sanitize xpath value
    char sanitizedValue[MAX_XPATH_LEN];
    size_t j = 0;
    for (size_t i = 0; xpathValue[i] && j < MAX_XPATH_LEN - 1; i++) {
        if (isalnum((unsigned char)xpathValue[i])) {
            sanitizedValue[j++] = xpathValue[i];
        }
    }
    sanitizedValue[j] = '\\0';

    // Create query
    snprintf(query, MAX_XPATH_LEN, "//tag[@id='%s']", sanitizedValue);

    // Execute xpath query
    xpathObj = xmlXPathEvalExpression((xmlChar*)query, xpathCtx);
    if (!xpathObj) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        free(result);
        return "Error: Failed to evaluate XPath expression";
    }

    // Process results
    if (xpathObj->nodesetval) {
        for (int i = 0; i < xpathObj->nodesetval->nodeNr; i++) {
            xmlNodePtr node = xpathObj->nodesetval->nodeTab[i];
            if (node->children && node->children->content) {
                strncat(result, (char*)node->children->content, MAX_RESULT_LEN - strlen(result) - 1);
                strncat(result, "\\n", MAX_RESULT_LEN - strlen(result) - 1);
            }
        }
    }

    // Cleanup
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <xml_file_path> <xpath_value>\\n", argv[0]);
        return 1;
    }

    char* result = executeXPathQuery(argv[1], argv[2]);
    printf("%s", result);
    free(result);

    return 0;
}
