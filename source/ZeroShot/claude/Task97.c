
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATH 1024

static int isFileAccessible(const char* filePath) {
    struct stat statbuf;
    return (stat(filePath, &statbuf) == 0 && S_ISREG(statbuf.st_mode) && access(filePath, R_OK) == 0);
}

char* executeXPathQuery(const char* xmlFilePath, const char* xpathQuery) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    char* result = NULL;
    
    // Initialize libxml
    xmlInitParser();
    
    // Check file accessibility
    if (!isFileAccessible(xmlFilePath)) {
        return strdup("Error: Cannot access XML file");
    }
    
    // Parse XML file
    doc = xmlReadFile(xmlFilePath, NULL, XML_PARSE_NONET | XML_PARSE_NOENT | XML_PARSE_NOCDATA);
    if (doc == NULL) {
        return strdup("Error: Unable to parse XML file");
    }
    
    // Create xpath context
    xpathCtx = xmlXPathNewContext(doc);
    if(xpathCtx == NULL) {
        xmlFreeDoc(doc);
        return strdup("Error: Unable to create XPath context");
    }
    
    // Evaluate xpath expression
    xpathObj = xmlXPathEvalExpression((xmlChar*)xpathQuery, xpathCtx);
    if(xpathObj == NULL) {
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return strdup("Error: Unable to evaluate XPath expression");
    }
    
    // Process results
    if(xmlXPathNodeSetIsEmpty(xpathObj->nodesetval)) {
        result = strdup("No result found");
    } else {
        xmlNodePtr node = xpathObj->nodesetval->nodeTab[0];
        xmlChar* nodeContent = xmlNodeGetContent(node);
        if(nodeContent != NULL) {
            result = strdup((char*)nodeContent);
            xmlFree(nodeContent);
        } else {
            result = strdup("No content in node");
        }
    }
    
    // Cleanup
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return result;
}

int main() {
    // Test cases
    const char* testFiles[] = {
        "sample.xml",
        "test.xml",
        "data.xml",
        "invalid.xml",
        "sample.xml"
    };
    
    const char* testQueries[] = {
        "/root[@id='1']",
        "/users/user[@id='123']",
        "/books/book[@id='B001']",
        "/root[@id='1']",
        "/invalid[@id='999']"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("XML File: %s\\n", testFiles[i]);
        printf("XPath Query: %s\\n", testQueries[i]);
        char* result = executeXPathQuery(testFiles[i], testQueries[i]);
        printf("Result: %s\\n", result);
        printf("------------------------\\n");
        free(result);
    }
    
    return 0;
}
