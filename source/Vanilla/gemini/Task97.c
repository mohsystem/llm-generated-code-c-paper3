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
        fprintf(stderr, "Error: unable to parse file \"%s\"\n", xmlFilePath);
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
        fprintf(stderr, "Error: unable to evaluate XPath expression \"%s\"\n", xpathValue);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return NULL;
    }

    if (xpathObj->nodesetval && xpathObj->nodesetval->nodeNr > 0) {
        int i;
        for (i = 0; i < xpathObj->nodesetval->nodeNr; ++i) {
             if(xpathObj->nodesetval->nodeTab[i]->type == XML_ELEMENT_NODE) {
                xmlChar *content = xmlNodeGetContent(xpathObj->nodesetval->nodeTab[i]);
                if (result == NULL) {
                    result = strdup((char *)content);
                } else {
                    char *temp = result;
                    result = (char *)malloc(strlen(result) + strlen((char *)content) + 1);
                    strcpy(result, temp);
                    strcat(result, (char *)content);
                    free(temp);
                }
                xmlFree(content);
             }
        }
    }



    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return result;
}

int main() {
    FILE *fp = fopen("temp.xml", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(fp, "<root><tag id=\"1\">Value1</tag><tag id=\"2\">Value2</tag></root>\n");
    fclose(fp);


    char *result;

    result = executeXPath("temp.xml", "/root/tag[@id='1']");
    printf("%s\n", result ? result : ""); free(result);

    result = executeXPath("temp.xml", "/root/tag[@id='2']");
    printf("%s\n", result ? result : ""); free(result);

    result = executeXPath("temp.xml", "/root/tag[@id='3']");
    printf("%s\n", result ? result : ""); free(result);

    result = executeXPath("temp.xml", "/root/tag");
    printf("%s\n", result ? result : ""); free(result);

    result = executeXPath("temp.xml", "/root");
    printf("%s\n", result ? result : ""); free(result);


    remove("temp.xml");
    return 0;
}