#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

char *executeXPath(const char *xmlFilePath, const char *xpathQuery) {
    xmlDocPtr doc = xmlParseFile(xmlFilePath);
    if (doc == NULL) {
        fprintf(stderr, "Error: Could not parse XML file.\n");
        return NULL;
    }

    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);
    if (xpathCtx == NULL) {
        fprintf(stderr, "Error: Unable to create XPath context.\n");
        xmlFreeDoc(doc);
        return NULL;
    }

    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *)xpathQuery, xpathCtx);
    if (xpathObj == NULL) {
        fprintf(stderr, "Error: Invalid XPath expression.\n");
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    xmlNodeSetPtr nodes = xpathObj->nodesetval;
    if (nodes == NULL || nodes->nodeNr == 0) {
        // No nodes found or error occurred
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return strdup(""); // Return empty string if no results
    }

    char *result = NULL;
    int resultSize = 0;


    for (int i = 0; i < nodes->nodeNr; i++) {
        xmlNodePtr cur = nodes->nodeTab[i];
        if (cur->type == XML_TEXT_NODE) {
            char *content = (char *)xmlNodeGetContent(cur);
            int contentLen = strlen(content);

            char *newResult = (char *)realloc(result, resultSize + contentLen + 2); // +2 for 
 and \0
            if (newResult == NULL) {
                fprintf(stderr, "Memory allocation error.\n");
                free(result);
                xmlXPathFreeObject(xpathObj);
                xmlXPathFreeContext(xpathCtx);
                xmlFreeDoc(doc);
                return NULL;
            }
            result = newResult;

            strcpy(result + resultSize, content);
            strcpy(result + resultSize + contentLen, "\n"); 
            resultSize += contentLen + 1;


            xmlFree(content);

        }
    }


    if (result != NULL && resultSize > 0 && result[resultSize - 1] == '\n') {
        result[resultSize - 1] = '\0'; // Replace last newline with null terminator
    }

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return result;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <xml_file> <xpath_query>\n", argv[0]);
        return 1;
    }
    char *xmlFile = argv[1];

    printf("Test case 1:\n%s\n", executeXPath(xmlFile, "/data/entry[@id='1']"));
    printf("\nTest case 2:\n%s\n", executeXPath(xmlFile, "/data/entry[@id='2']"));
    printf("\nTest case 3:\n%s\n", executeXPath(xmlFile, "/data/entry[@id='3']"));
    printf("\nTest case 4:\n%s\n", executeXPath(xmlFile, "/data/entry[@id='4']"));
    printf("\nTest case 5:\n%s\n", executeXPath(xmlFile, "/data/entry[@id='5']"));
    return 0;
}